#!/usr/bin/env python3

import sys
import re
import itertools
import time

from pathlib import Path
from typing import Any, TextIO, Union

from rich.console import Console

from netexp.helpers import LocalHost, RemoteHost, get_host_from_hostname
from netexp.pktgen import Pktgen
from netexp.pktgen.dpdk import DpdkConfig, DpdkPktgen

MAX_ACCEPTABLE_LOSS = 0.001        # Must be in [0, 1).
DEFAULT_PRECISION   = 100_000_000  # in bps (100 Mbps).

CONTROLLER_CMD_ENV = 'LD_LIBRARY_PATH=“/usr/local/lib/:$SDE_INSTALL/install/lib/”'
CONTROLLER_FLAGS   = "--hw --bench"

class Controller:
    """
    Config keys:
        timeout_ms: flow timeout time in miliseconds
    """
    config_keys = ["timeout_ms"] # Add any new config keys here.

    def __init__(
        self,
        hostname: str,
        controller_source: Path,
        dataplane_source: Path,
        config: dict[str, Any],
        dataplane_build_vars: dict[str, Any] = {},
        log_file: Union[bool, TextIO] = False,
    ) -> None:
        self.log_file = log_file
        self.config = config
        self._hostname = hostname
        self.controller_cmd = None
        
        self.controller_source = controller_source
        self.controller_path = self.config["paths"]["controller_path"]
        self.controller_builder = self.config["paths"]["controller_build_script"]

        self.dataplane_source = dataplane_source
        self.dataplane_path = self.config["paths"]["dataplane_path"]
        self.dataplane_builder = self.config["paths"]["dataplane_build_script"]

        self.dataplane_build_vars = dataplane_build_vars

        self.sde_install = self.config["paths"]["sde_install"]

        self.config = config

    def __compile(self) -> None:
        # TODO(sadok): Run SyNAPSE to produce source codes for the controller
        # and the switch.

        controller_comp_cmd = f"{self.controller_env} {self.controller_builder} {self.controller_source}"
        cmd = self.host.run_command(
            controller_comp_cmd,
            dir=self.controller_path,
            print_command=self.log_file,
        )
        cmd.watch(stdout=self.log_file, stderr=self.log_file)

        p4_comp_cmd = f"{self.dataplane_builder} {self.dataplane_source}"

        for var in self.dataplane_build_vars.keys():
            value = self.dataplane_build_vars[var]
            p4_comp_cmd += f" -D{var}={value}"

        cmd = self.host.run_command(
            p4_comp_cmd,
            dir=self.dataplane_path,
            print_command=self.log_file,
        )
        cmd.watch(stdout=self.log_file, stderr=self.log_file)

        self.controller_cmd = None

    def start(self, config: dict[str, Any]) -> None:
        # Config must contain all the required keys and nothing else.
        if set(config.keys()) != set(self.config_keys):
            raise ValueError(f"Required config keys: {self.config_keys}")
        
        timeout_ms = config["timeout_ms"]

        if timeout_ms < 10:
            raise Exception(f"Timeout value must be >= 10ms (is {timeout_ms} ms)")
        
        self.__compile()

        # The build script generates an executable with the same name as the source file,
        # minus the extension.
        self.controller_exe = self.controller_source.stem

        cmd = f"{self.controller_env} ./{self.controller_exe} {timeout_ms} --hw"

        self.controller_cmd = self.host.run_command(
            cmd,
            dir=self.controller_path,
            print_command=self.log_file,
        )

    def wait_ready(self) -> None:
        # Wait for the controller to be ready.
        # It prints the message "Controller is ready." when it's ready.

        if self.controller_cmd is None:
            raise RuntimeError("Controller not started")

        self.controller_cmd.watch(
            stop_pattern="Controller is ready",
            stdout=self.log_file,
            stderr=self.log_file,
        )

    def stop(self) -> None:
        if self.controller_cmd is None:
            return

        # Kill all instances
        cmd = f"killall {self.controller_exe}"

        self.host.run_command(
            cmd,
            print_command=self.log_file,
        )

        self.controller_cmd.watch(stdout=self.log_file, stderr=self.log_file)

        self.controller_cmd = None
        self.controller_exe = None
    
    def __del__(self):
        self.stop()
    
    @classmethod
    def get_config_str(cls, config: dict[str, Any]) -> str:
        # Config must contain all the required keys and nothing else.
        if set(config.keys()) != set(cls.config_keys):
            raise ValueError(f"Required config keys: {cls.config_keys}")
        
        return ",".join(str(config[key]) for key in cls.config_keys)

    @classmethod
    def get_config_header(cls) -> str:
        return ",".join(cls.config_keys)

    @property
    def host(self) -> Union[LocalHost, RemoteHost]:
        if not hasattr(self, '_host') or self._host is None:
            self._host = get_host_from_hostname(self.hostname)
        return self._host

    @property
    def hostname(self) -> str:
        return self._hostname

    @property
    def controller_env(self) -> str:
        if hasattr(self, '_controller_env'):
            return self._controller_env
        
        env_vars_dict = {
            "SDE_INSTALL": [ self.sde_install ],
            "LD_LIBRARY_PATH": [
                "/usr/local/lib/",
                f"{self.sde_install}/lib/"
            ],
        }

        all_env_list = [ f"{k}={':'.join(env_vars_dict[k])}" for k in env_vars_dict.keys() ]
        self._controller_env = ' '.join(all_env_list)

        return self._controller_env

    def zero_loss_throughput(
        self,
        pktgen: Pktgen,
        max_throughput: int = 100_000_000_000,
        precision: int = DEFAULT_PRECISION,
        target_duration: int = 5,
        max_loss: float = MAX_ACCEPTABLE_LOSS,
    ) -> tuple[int,int]:
        """Find zero-loss throughput using a binary search.

        This assumes that the DUT is connected to the packet generator and the
        controller's next state is `BENCH`. The DUT should try to send back all
        packets that it receives and should not introduce new ones. The DUT is
        allowed to drop packets if it cannot keep up with the input throughput.

        Args:
            pktgen: Packet generator.
            max_throughput: Maximum throughout to try (in bps).
            precision: Throughput precision (in bps).
            target_duration: Target experiment duration (in seconds). The
                number of packets to be sent will be adjusted base on this and
                the current attempted throughput.
            max_loss: Maximum acceptable loss rate, must be in [0, 1).
            cleanup: Function to call to clean up the DUT after every run.

        Returns:
            The zero loss throughput found (in bps and pps).
        """

        log_file = None

        if pktgen.log_file:
            log_file = open(pktgen.log_file, "a")
        
        if not (0 <= max_loss < 1):
            raise ValueError("max_loss must be in [0, 1).")

        self.wait_ready()

        capacity_lower = 0    # Lower bound.
        capacity_upper = 100  # Upper bound.
        capacity_precision = 100 * precision / max_throughput

        real_throughput_bps_winner = 0
        real_throughput_pps_winner = 0

        # We start from the capacity (%).
        current_capacity = capacity_upper

        # We iteratively refine the bounds until the difference between them is
        # less than the specified precision.
        while (capacity_upper - capacity_lower) > capacity_precision:
            if log_file:
                log_file.write(f"Trying {current_capacity}% capacity\n")

            warmup_time_seconds = 5
            warmup_rate_capacity = 0.01

            pktgen.start(warmup_rate_capacity)
            time.sleep(warmup_time_seconds)
            pktgen.clean_stats()
            pktgen.set_rate(current_capacity)
            time.sleep(target_duration)
            pktgen.stop()

            nb_rx_pkts = pktgen.get_nb_rx_pkts()
            nb_rx_bytes = pktgen.get_nb_rx_bytes()

            nb_tx_pkts = pktgen.get_nb_tx_pkts()
            nb_tx_bytes = pktgen.get_nb_tx_bytes()

            real_throughput_tx_bps = int((nb_tx_bytes + 20.0) * 8 / target_duration)
            real_throughput_tx_pps = int(nb_tx_pkts / target_duration)

            real_throughput_rx_bps = int((nb_rx_bytes + 20.0) * 8 / target_duration)
            real_throughput_rx_pps = int(nb_rx_pkts / target_duration)

            # Calculating loss with bytes instead of packets, as
            # packet counting seems unreliable...
            loss = 1 - nb_rx_bytes / nb_tx_bytes

            if log_file:
                tx_Gbps = real_throughput_tx_bps / 1e9
                tx_Mpps = real_throughput_tx_pps / 1e6

                rx_Gbps = real_throughput_rx_bps / 1e9
                rx_Mpps = real_throughput_rx_pps / 1e6

                log_file.write(f"TX {tx_Mpps:.2f} Mpps {tx_Gbps:.2f} Gbps\n")
                log_file.write(f"RX {rx_Mpps:.2f} Mpps {rx_Gbps:.2f} Gbps\n")
                log_file.write(f"Lost {loss*100:.2f}% of packets\n")
                log_file.flush()

            if loss > max_loss:
                capacity_upper = current_capacity
            else:
                capacity_lower = current_capacity

                real_throughput_bps_winner = real_throughput_tx_bps
                real_throughput_pps_winner = real_throughput_tx_pps

            current_capacity = (capacity_upper + capacity_lower) / 2

        # Found a rate.
        return real_throughput_bps_winner, real_throughput_pps_winner

def validate_pcie_dev(
    host: Union[LocalHost, RemoteHost],
    pcie_dev: str,
    log_file: Union[bool, TextIO] = False,
) -> None:
    cmd = "lspci -mm"

    cmd = host.run_command(cmd, print_command=log_file)
    info = cmd.watch()

    info = info.split("\n")

    for line in info:
        line = line.split(" ")
        device = line[0]

        if device in pcie_dev:
            return

    print(f'Invalid PCIe device "{pcie_dev}"', file=sys.stderr)
    exit(1)


def get_device_numa_node(
    host: Union[LocalHost, RemoteHost],
    pcie_dev: str,
    log_file: Union[bool, TextIO] = False,
) -> int:
    cmd = f"lspci -s {pcie_dev} -vv"
    cmd = host.run_command(cmd, print_command=log_file)
    info = cmd.watch()

    result = re.search(r"NUMA node: (\d+)", info)

    if not result:
        return 0

    assert result
    return int(result.group(1))


def get_all_cpus(
    host: Union[LocalHost, RemoteHost], log_file: Union[bool, TextIO] = False
) -> list[int]:
    cmd = "lscpu"
    cmd = host.run_command(cmd, print_command=log_file)
    info = cmd.watch()

    result = re.search(r"CPU\(s\):\D+(\d+)", info)

    assert result
    total_cpus = int(result.group(1))

    return [x for x in range(total_cpus)]


def get_numa_node_cpus(
    host: Union[LocalHost, RemoteHost],
    node: int,
    log_file: Union[bool, TextIO] = False,
):
    cmd = "lscpu"
    cmd = host.run_command(cmd, print_command=log_file)
    info = cmd.watch()
    info = [line for line in info.split("\n") if "NUMA" in line]

    assert len(info) > 0
    total_nodes_match = re.search(r"\D+(\d+)", info[0])

    assert total_nodes_match
    total_nodes = int(total_nodes_match.group(1))

    if node > total_nodes:
        print(
            f"Requested NUMA node ({node}) >= available nodes ({total_nodes})",
            file=sys.stderr,
        )
        exit(1)

    if total_nodes == 1:
        return get_all_cpus(host, log_file=log_file)

    assert len(info) == total_nodes + 1
    node_info = info[node + 1]

    if "-" in node_info:
        cpus_match = re.search(r"\D+(\d+)\-(\d+)$", node_info)
        assert cpus_match

        min_cpu = int(cpus_match.group(1))
        max_cpu = int(cpus_match.group(2))

        return [cpu for cpu in range(min_cpu, max_cpu + 1)]

    cpus_match = re.search(r"\D+([\d,]+)$", node_info)
    assert cpus_match
    return [int(i) for i in cpus_match.groups(0)[0].split(",")]


def get_pcie_dev_cpus(
    host: Union[LocalHost, RemoteHost],
    pcie_dev: str,
    log_file: Union[bool, TextIO] = False,
) -> list[int]:
    numa = get_device_numa_node(host, pcie_dev, log_file=log_file)
    cpus = get_numa_node_cpus(host, numa, log_file=log_file)
    if log_file is True:
        log_file = sys.stdout

    if log_file:
        log_file.write(f"PCIe={pcie_dev} NUMA={numa} CPUs={cpus}\n")

    return cpus

async def load_pktgen(
    pktgen_log_file: TextIO,
    config: dict[str, Any],
    console: Console,
) -> DpdkPktgen:
    with console.status("Loading Pktgen NIC"):
        rx_pcie_device = config["devices"]["pktgen"]["rx_dev"]
        tx_pcie_device = config["devices"]["pktgen"]["tx_dev"]

        nb_rx_cores = config["devices"]["pktgen"]["nb_rx_cores"]
        nb_tx_cores = config["devices"]["pktgen"]["nb_tx_cores"]

        max_throughput = config["devices"]["pktgen"]["tx_line_rate"]

        rx_port_nb = 0
        tx_port_nb = 1
        pcie_devices = [rx_pcie_device, tx_pcie_device]

        hostname = config["hosts"]["pktgen"]
        host = get_host_from_hostname(hostname)

        validate_pcie_dev(host, rx_pcie_device, log_file=pktgen_log_file)
        validate_pcie_dev(host, tx_pcie_device, log_file=pktgen_log_file)

        all_cores = get_all_cpus(host, log_file=pktgen_log_file)
        rx_core_candidates = set(
            get_pcie_dev_cpus(host, rx_pcie_device, log_file=pktgen_log_file)
        )
        tx_core_candidates = set(
            get_pcie_dev_cpus(host, tx_pcie_device, log_file=pktgen_log_file)
        )

        if len(rx_core_candidates) < nb_rx_cores + 1:
            raise Exception(
                f"Cannot find {nb_rx_cores + 1} cores for rx on {hostname}"
            )

        # Needs an extra core for the main thread.
        if len(all_cores) < (nb_rx_cores + nb_tx_cores + 2):
            raise Exception(f"Cannot find enough cores on {hostname}")

        rx_cores = list(itertools.islice(rx_core_candidates, nb_rx_cores + 1))

        # Let's use the first one for tx
        rx_tx_core = rx_cores[0]
        rx_rx_cores = rx_cores[1:]

        # Remove rx cores from the set of possible tx cores.
        tx_core_candidates -= set(rx_cores)

        if len(tx_core_candidates) < nb_tx_cores + 1:
            raise Exception(
                f"Cannot find {nb_tx_cores + 1} cores for tx on {hostname}"
            )

        tx_cores = list(itertools.islice(tx_core_candidates, nb_tx_cores + 1))

        tx_rx_core = tx_cores[0]
        tx_tx_cores = tx_cores[1:]

        remaining_cores = list(set(all_cores) - set(rx_cores) - set(tx_cores))
        main_core  = remaining_cores[0]

        rx_cores_str = "/".join(str(c) for c in rx_rx_cores)
        tx_cores_str = "/".join(str(c) for c in tx_tx_cores)

        rx_map = f"[{rx_cores_str}:{rx_tx_core}].{rx_port_nb}"
        tx_map = f"[{tx_rx_core}:{tx_cores_str}].{tx_port_nb}"

        port_map = f"{rx_map},{tx_map}"

        dpdk_config = DpdkConfig(
            cores=[main_core, rx_tx_core, tx_rx_core] + rx_cores + tx_cores,
            mem_channels=config["extra"]["dpdk_mem_channels"],
            proc_type="auto",
            pci_allow_list=pcie_devices,
        )
        
        pktgen = DpdkPktgen(
            hostname,
            dpdk_config,
            port_map,
            max_throughput,
            rx_port=rx_port_nb,
            tx_port=tx_port_nb,
            promiscuous=True,
            numa_support=True,
            log_file=pktgen_log_file.name,
        )

    console.log("[green]Done loading Pktgen")
    return pktgen


async def load_controller(
    controller_log_file: TextIO,
    controller_source: Path,
    dataplane_source: Path,
    config: dict[str, Any],
    console: Console,
    dataplane_build_vars: dict[str, Any] = {},
) -> Controller:
    with console.status("Loading Controller"):
        controller_hostname = config["hosts"]["controller"]

        controller = Controller(
            controller_hostname,
            controller_source,
            dataplane_source,
            config,
            dataplane_build_vars,
            controller_log_file,
        )

    console.log(f"[green]Done loading Controller for {dataplane_source.name}")
    return controller
