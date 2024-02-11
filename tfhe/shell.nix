# shell.nix

{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = [ pkgs.nixfmt pkgs.vim pkgs.cargo pkgs.zola pkgs.yarn pkgs.nodejs ];
  shellHook = ''
	alias clion=/var/home/guibaeta/distrobox/apps/.local/share/JetBrains/Toolbox/apps/clion/bin/clion.sh
  	alias webstorm=/var/home/guibaeta/distrobox/apps/.local/share/JetBrains/Toolbox/apps/webstorm/bin/webstorm.sh
  '';
}


