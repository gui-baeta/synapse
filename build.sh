#!/bin/bash

set -euo pipefail

SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" &> /dev/null && pwd)

# Note that opam needs bash, not just sh
# Also it uses undefined variables so let's set them now otherwise it'll fail due to strict mode
if [ -z ${PERL5LIB+x} ]; then
  export PERL5LIB=''
fi
if [ -z ${MANPATH+x} ]; then
  export MANPATH=''
fi
if [ -z ${PROMPT_COMMAND+x} ]; then
  export PROMPT_COMMAND=''
fi

# Detect the running operating system
# stdout: 'windows', 'docker' or 'linux'
detect_os() {
	# Detect WSL
	case $(uname -r) in
		*Microsoft*)
			echo 'windows'
			return 0
			;;
	esac

	# Use generic "linux" tag for the rest.
	# XXX: Support some more distributions ?
	echo 'linux'
	return 0
}

# Constants
DEPS_DIR="$SCRIPT_DIR/deps"
PATHSFILE="$SCRIPT_DIR/paths.sh"
KERNEL_VER=$(uname -r | sed 's/-Microsoft//')
OS="$(detect_os)"
BUILDING_CORES=4

# Versions
OCAML_RELEASE='4.06.0'
GCC_VERSION='10'

# Dependencies
DPDK_DIR="$DEPS_DIR/dpdk"
KLEE_DIR="$DEPS_DIR/klee"
KLEE_UCLIBC_DIR="$DEPS_DIR/klee-uclibc"
LLVM_DIR="$DEPS_DIR/llvm"
Z3_DIR="$DEPS_DIR/z3"

# Checks if a variable is set in a file. If it is not in the file, add it with
# given value, otherwise change the value to match the current one.
# $1 : the name of the variable
# $2 : the value to set
add_var_to_paths_file() {
	if grep "^export $1" "$PATHSFILE" >/dev/null;
	then
		# Using sed directly to change the value would be dangerous as
		# we would need to correctly escape the value, which is hard.
		sed -i "/^export $1/d" "$PATHSFILE"
	fi
	echo "export ${1}=${2}" >> "$PATHSFILE"
}

# Same as line, but without the unicity checks.
# $1 : the name of the file
# $2 : the name of the variable
# $3 : the value to set
add_var_to_paths_file_multiline() {
	if ! grep "^export ${1}=${2}" "$PATHSFILE" >/dev/null;
	then
		echo "export ${1}=${2}" >> "$PATHSFILE"
	fi
}

# Install arguments using system's package manager.
# XXX: Make the package manager depend on "$OS".
# shellcheck disable=SC2086
package_install() {
	# Concatenate arguments into a list
	old_ifs="$IFS"
	IFS=' '
	packages="$*"
	IFS="$old_ifs"

	sudo apt-get install -yqq $packages
}

# Update list of available packages.
# XXX: Make the package manager depend on "$OS".
package_sync() {
	sudo apt-get update -qq
}

source_paths_in_profile() {
	if ! grep "^source $PATHSFILE" ~/.profile >/dev/null;
	then
		echo "source $PATHSFILE" >> ~/.profile
	fi
}

create_paths_file() {
	rm -f "$PATHSFILE" > /dev/null 2>&1 || true
	touch "$PATHSFILE"
}

setup_python_venv() {
	cd "$SCRIPT_DIR"
	python3 -m venv env
	source ./env/bin/activate
}

set_gcc_version() {
	package_install gcc-$GCC_VERSION g++-$GCC_VERSION

	sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-$GCC_VERSION 100
	sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-$GCC_VERSION 100

	sudo update-alternatives --set g++ /usr/bin/g++-$GCC_VERSION
	sudo update-alternatives --set gcc /usr/bin/gcc-$GCC_VERSION

	sudo update-alternatives --install /usr/bin/cc cc /usr/bin/gcc 100
	sudo update-alternatives --set cc /usr/bin/gcc

	sudo update-alternatives --install /usr/bin/c++ c++ /usr/bin/g++ 100
	sudo update-alternatives --set c++ /usr/bin/g++
}

installation_setup() {
	create_paths_file
	source_paths_in_profile
	setup_python_venv
	set_gcc_version
}

# Checks if a variable is set in a file. If it is not in the file, add it with
# given value, otherwise change the value to match the current one.
# $1 : the name of the variable
# $2 : the value to set
add_var_to_paths_file()
{
	if grep "^export $1" "$PATHSFILE" >/dev/null;
	then
		# Using sed directly to change the value would be dangerous as
		# we would need to correctly escape the value, which is hard.
		sed -i "/^export $1/d" "$PATHSFILE"
	fi
	echo "export ${1}=${2}" >> "$PATHSFILE"
}

# Same as line, but without the unicity checks.
# $1 : the name of the variable
# $2 : the value to set
add_multiline_var_to_paths_file()
{
	if ! grep "^export ${1}=${2}" "$PATHSFILE" >/dev/null;
	then
		echo "export ${1}=${2}" >> "$PATHSFILE"
	fi
}

source_install_dpdk() {
	echo "Installing DPDK..."

	# Install kernel headers
	case "$OS" in
		'microsoft')
			package_install "linux-headers-$KERNEL_VER-generic"

			# Fix the kernel dir, since the WSL doesn't have an actual Linux kernel.
			export RTE_KERNELDIR="/usr/src/linux-headers-$KERNEL_VER-generic/"
			;;
		'linux')
			package_install linux-headers-generic
			;;
	esac

	# Install other dependencies
	package_install \
		gperf \
		libgoogle-perftools-dev \
		libpcap-dev \
		meson \
		pkg-config

	TARGET=x86_64-native-linuxapp-gcc
	DPDK_BUILD_DIR="$DPDK_DIR/$TARGET"

	# Ensure environment is correct.
	add_var_to_paths_file 'RTE_TARGET' "$TARGET"
	add_var_to_paths_file 'RTE_SDK' "$DPDK_DIR"
	add_multiline_var_to_paths_file 'PKG_CONFIG_PATH' "$DPDK_BUILD_DIR/lib/x86_64-linux-gnu/pkgconfig/"

	# shellcheck source=../paths.sh
	. "$PATHSFILE"

	pushd "$DPDK_DIR"
		# Compile
		meson setup "$TARGET" --prefix="$DPDK_BUILD_DIR"

		pushd "$DPDK_BUILD_DIR"
			ninja
			ninja install
		popd
	popd

	echo "Done."
}

source_install_z3() {
	echo "Installing Z3..."

	pushd "$Z3_DIR"
		python3 scripts/mk_make.py -p "$Z3_DIR/build"
		cd build
		make -kj$BUILDING_CORES || make
		make install

		add_var_to_paths_file 'Z3_DIR' "$Z3_DIR"
	popd

	echo "Done."
}

source_install_llvm() {
	echo "Installing LLVM..."
	
	package_install bison flex zlib1g-dev libncurses5-dev libpcap-dev python-is-python3

	add_multiline_var_to_paths_file 'PATH' "$LLVM_DIR/Release/bin:\$PATH"
	# shellcheck source=../paths.sh
	. "$PATHSFILE"

	pushd "$LLVM_DIR"
		CXXFLAGS="-D_GLIBCXX_USE_CXX11_ABI=0" \
		    CC=c-compiler CXX=c++-compiler \
				./configure \
					--enable-optimized \
					--disable-assertions \
					--enable-targets=host \
					--with-python='/usr/bin/python'

		# Painfully slow, but allowing the compilation to use many cores
		# consumes a lot of memory, and crashes some systems.
		REQUIRES_RTTI=1 make -j$BUILDING_CORES
	popd

	echo "Done."
}

source_install_klee_uclibc() {
	echo "Installing KLEE uclibc..."

	pushd "$KLEE_UCLIBC_DIR"
		# If there is a single version of GCC and it's a single digit, as in e.g. GCC 9 on Ubuntu 20.04,
		# our clang won't detect it because it expects a version in the format x.y.z with all components
		# so let's create a symlink
		# 0 -> nothing, 2 -> a single dot (because there is also \0)
		GCC_VER=$(ls -1 /usr/lib/gcc/x86_64-linux-gnu/ | sort -V | tail -n 1)
		
		if [ $(echo $GCC_VER | grep -Fo . | wc -c) -eq 0 ]; then
			sudo ln -s "/usr/lib/gcc/x86_64-linux-gnu/$GCC_VER" "/usr/lib/gcc/x86_64-linux-gnu/$GCC_VER.0.0" ;
		fi

		if [ $(echo $GCC_VER | grep -Fo . | wc -c) -eq 2 ]; then
			sudo ln -s "/usr/lib/gcc/x86_64-linux-gnu/$GCC_VER" "/usr/lib/gcc/x86_64-linux-gnu/$GCC_VER.0" ;
		fi

		./configure \
			--make-llvm-lib \
			--with-llvm-config="$LLVM_DIR/Release/bin/llvm-config" \
			--with-cc="$LLVM_DIR/Release/bin/clang"

		cp "$SCRIPT_DIR/setup/klee-uclibc.config" '.config'
		
		make -kj$BUILDING_CORES
	popd

	echo "Done."
}

source_install_klee() {
	echo "Installing KLEE..."

	add_var_to_paths_file 'KLEE_DIR' "$KLEE_DIR"
	add_var_to_paths_file 'KLEE_INCLUDE' "$KLEE_DIR/include"
	add_var_to_paths_file 'KLEE_BUILD_PATH' "$KLEE_DIR/Release"

	add_multiline_var_to_paths_file 'PATH' "$KLEE_DIR/Release/bin:\$PATH"

	# shellcheck source=../paths.sh
	. "$PATHSFILE"

	pushd "$KLEE_DIR"
		./build.sh
	popd

	echo "Done."
}

bin_install_ocaml() {
	echo "Installing OCaml..."

	# we depend on an OCaml package that needs libgmp-dev
	package_install opam m4 libgmp-dev

	opam init --disable-sandboxing -y
	eval "$(opam config env)"
	# Opam 1.x doesn't have "create", later versions require it but only the first time
	if opam --version | grep '^1.' >/dev/null ; then
		opam switch $OCAML_RELEASE
	else
		opam switch list
		if ! opam switch list 2>&1 | grep -Fq 4.06 ; then
			opam switch create $OCAML_RELEASE
		fi
	fi

	add_multiline_var_to_paths_file 'PATH' "$HOME/.opam/system/bin:\$PATH"
    # `|| :` at the end of the following command ensures that in the event the
    # init.sh script fails, the shell will not exit. opam suggests we do this.
	echo ". $HOME/.opam/opam-init/init.sh || :" >> "$PATHSFILE"
	. "$PATHSFILE"

	# Codegenerator dependencies.
	opam install goblint-cil core -y
	opam install ocamlfind num -y
	opam install ocamlfind sexplib menhir -y

	echo "Done."
}

# Environment
package_sync

# Common dependencies
package_install \
	build-essential \
	curl \
	wget \
	git \
	wget \
	libgoogle-perftools-dev \
	python3 \
	python3-pip \
	python3-venv \
	parallel \
	gcc-multilib \
	graphviz \
	libpcap-dev \
	libnuma-dev \
	cmake \
	ca-certificates \
	software-properties-common \
	patch \
	cloc \
	time

# Environment after packages are installed
installation_setup

pip3 install numpy
pip3 install scapy
pip3 install wheel

# Install things
source_install_dpdk
source_install_z3
source_install_llvm
source_install_klee_uclibc
source_install_klee
bin_install_ocaml
