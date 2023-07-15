import re
import itertools

from pathlib import Path
from typing import Optional, Union

from .remote import RemoteHost
from .dpdk_config import DpdkConfig

MIN_NUM_TX_CORES = 2

class Pktgen():
    def __init__(
        self,
        hostname: str,
        rx_pcie_dev: str,
        tx_pcie_dev: str,
        nb_tx_cores: int,
        nb_flows: int,
        pkt_size: int = 64,
        exp_time_us: int = 0,
        crc_unique_flows: bool = False,
        crc_bits: int = 16,
        pktgen_exe: Union[str, Path] = "pktgen",
        log_file: Optional[str] = None,
    ) -> None:
        self.host = RemoteHost(hostname)
        self.rx_pcie_dev = rx_pcie_dev
        self.tx_pcie_dev = tx_pcie_dev
        self.nb_tx_cores = nb_tx_cores
        self.nb_flows = nb_flows
        self.pkt_size = pkt_size
        self.exp_time_us = exp_time_us
        self.crc_unique_flows = crc_unique_flows
        self.crc_bits = crc_bits
        self.pktgen_exe = Path(pktgen_exe)
        self.log_file = open(log_file, "a") if log_file else False

        self.pktgen_active = False

        if self.nb_tx_cores < MIN_NUM_TX_CORES:
            raise Exception(f"Number of TX cores must be >= {MIN_NUM_TX_CORES} (is {self.nb_tx_cores})")

    def __run_commands(
            self,
            cmds: Union[str, list[str]],
            timeout: float = 0.5,
            wait: bool = True
    ) -> str:
        assert self.pktgen_active
        console_pattern = "\r\nPktgen:/> " if wait else None
        return self.pktgen.run_console_commands(
            cmds,
            timeout=timeout,
            console_pattern=console_pattern,
        )

    def launch(self) -> None:
        assert not self.pktgen_active

        # This is kind of lazy, and not sure if even correct, but let's
        # grab the last digit from he PCIe ID and use it as the port ID.
        tx_port = int(self.tx_pcie_dev.split('.')[-1])
        rx_port = int(self.rx_pcie_dev.split('.')[-1])

        pktgen_options_list = [
            f"--total-flows {self.nb_flows}",
            f"--pkt-size {self.pkt_size}",
            f"--tx {tx_port}",
            f"--rx {rx_port}",
            f"--tx-cores {self.nb_tx_cores}",
            f"--exp-time {self.exp_time_us}"
        ]

        if self.crc_unique_flows:
            pktgen_options_list.append(f"--crc-unique-flows")
            pktgen_options_list.append(f"--crc-bits {self.crc_bits}")
        
        pktgen_options = ' '.join(pktgen_options_list)

        remote_cmd = f"sudo {str(self.pktgen_exe)} {self.dpdk_config} -- {pktgen_options}"
        self.pktgen = self.host.run_command(remote_cmd, pty=True, log_file=self.log_file)
        self.pktgen_active = True
        self.ready = False

        self.remote_cmd = remote_cmd
        self.target_pkt_tx = 0
    
    def wait_ready(self) -> int:
        assert self.pktgen_active

        # Wait to see if we actually managed to run pktgen successfuly.
        # Typically we fail here if we forgot to bind ports to DPDK,
        # or allocate hugepages.
        if self.pktgen.exit_status_ready() and self.pktgen.recv_exit_status() != 0:
            self.pktgen_active = False
            raise Exception("Cannot run pktgen")
        
        output = self.pktgen.watch(stop_pattern="\r\nPktgen>")
        self.ready = True

        lines = output.split("\r\n")
        
        while lines:
            if lines[0] == "----- Config -----":
                break
            lines = lines[1:]
        
        for line in lines:
            match = re.search(r"\s*Max churn:\s*(\d+) fpm", line)
            
            if not match:
                continue

            max_churn = int(match.group(1))
            return max_churn

        raise Exception("Unable to retrieve max churn data from output")

    def start(self) -> None:
        assert self.pktgen_active

        if not self.ready:
            self.wait_ready()

        self.__run_commands("start")
    
    def set_rate(self, rate_mbps: int) -> None:
        assert rate_mbps > 0
        self.__run_commands(f"rate {rate_mbps}")
    
    def set_churn(self, churn_fpm: int) -> None:
        assert churn_fpm >= 0
        self.__run_commands(f"churn {churn_fpm}")

    def stop(self) -> None:
        assert self.pktgen_active
        self.__run_commands("stop")

    def reset_stats(self) -> None:
        assert self.pktgen_active
        self.__run_commands("reset")

    def close(self) -> None:
        assert self.pktgen_active
        self.__run_commands("quit", wait=False)
        self.pktgen_active = False

    def get_stats(self) -> tuple[int, int]:
        assert self.pktgen_active
        output = self.__run_commands("stats")
        lines = output.split("\r\n")
        
        while lines:
            if lines[0] == "~~~~~~ Pktgen ~~~~~~":
                break
            lines = lines[1:]
        
        assert lines

        tx_line = lines[1]
        rx_line = lines[2]

        tx_result = re.search(r"\s+TX:\s+(\d+)", tx_line)
        rx_result = re.search(r"\s+RX:\s+(\d+)", rx_line)

        assert tx_result
        assert rx_result

        tx = int(tx_result.group(1))
        rx = int(rx_result.group(1))

        return tx, rx

    def enter_interactive(self) -> None:
        self.pktgen.posix_shell()

    @property
    def dpdk_config(self):
        if hasattr(self, '_dpdk_config'):
            return self._dpdk_config

        self.host.validate_pcie_dev(self.rx_pcie_dev, log_file=self.log_file)
        self.host.validate_pcie_dev(self.tx_pcie_dev, log_file=self.log_file)

        all_cores = self.host.get_all_cpus(log_file=self.log_file)

        all_cores = set(
            self.host.get_pcie_dev_cpus(self.tx_pcie_dev, log_file=self.log_file)
        )

        # Needs an extra core for the main thread.
        if len(all_cores) < self.nb_tx_cores + 1:
            raise Exception(
                f"Cannot find {self.nb_tx_cores + 1} cores"
            )

        tx_cores = list(itertools.islice(all_cores, self.nb_tx_cores + 1))

        dpdk_config = DpdkConfig(
            cores=tx_cores,
            proc_type="auto",
            pci_allow_list=[self.rx_pcie_dev, self.tx_pcie_dev],
        )

        self._dpdk_config = dpdk_config
        return self._dpdk_config
    
    def __del__(self) -> None:
        if self.pktgen_active:
            self.close()
