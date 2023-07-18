import sys
import re
import subprocess

from abc import ABC, abstractmethod
from typing import TextIO, Union
from pathlib import Path

from .commands.command import Command

class Host(ABC):
    def __init__(self):
        super().__init__()

    @abstractmethod
    def run_command(self, *args, **kwargs) -> Command:
        pass

    def remote_file_exists(
        self,
        host: str,
        remote_path: Path,
    ) -> bool: 
        cp = subprocess.run(
            [ "ssh", host, "test", "-f", str(remote_path) ],
            stdout=sys.stdout,
            stderr=sys.stdout,
        )

        return cp.returncode == 0

    def upload_file(
        self,
        host: str,
        local_path: Path,
        remote_path: Path,
        overwrite: bool = True,
    ) -> None:
        if not overwrite and self.remote_file_exists(remote_path):
            return

        cp = subprocess.run(
            [ "scp", "-r", str(local_path), f"{host}:{str(remote_path)}" ],
            stdout=subprocess.DEVNULL,
            stderr=subprocess.DEVNULL,
        )

        cp.check_returncode()

    def validate_pcie_dev(
        self,
        pcie_dev: str,
        log_file: Union[bool, TextIO] = False,
    ) -> None:
        cmd = "lspci -mm"

        cmd = self.run_command(cmd, log_file=log_file)
        info = cmd.watch()

        info = info.split("\n")

        for line in info:
            line = line.split(" ")
            device = line[0]

            if device in pcie_dev:
                return

        if log_file is True:
            log_file = sys.stderr
            
        print(f'Invalid PCIe device "{pcie_dev}"', file=log_file)
        exit(1)

    def get_device_numa_node(
        self,
        pcie_dev: str,
        log_file: Union[bool, TextIO] = False,
    ) -> int:
        cmd = f"lspci -s {pcie_dev} -vv"
        cmd = self.run_command(cmd, log_file=log_file)
        info = cmd.watch()

        result = re.search(r"NUMA node: (\d+)", info)

        if not result:
            return 0

        assert result
        return int(result.group(1))

    def get_all_cpus(
        self,
        log_file: Union[bool, TextIO] = False
    ) -> list[int]:
        cmd = "lscpu"
        cmd = self.run_command(cmd, log_file=log_file)
        info = cmd.watch()

        result = re.search(r"CPU\(s\):\D+(\d+)", info)

        assert result
        total_cpus = int(result.group(1))

        return [ x for x in range(total_cpus) ]

    def get_numa_node_cpus(
        self,
        node: int,
        log_file: Union[bool, TextIO] = False,
    ):
        cmd = "lscpu"
        cmd = self.run_command(cmd, log_file=log_file)
        info = cmd.watch()
        info = [ line for line in info.split("\n") if "NUMA" in line ]

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
            return self.get_all_cpus(log_file=log_file)

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
        self,
        pcie_dev: str,
        log_file: Union[bool, TextIO] = False,
    ) -> list[int]:
        numa = self.get_device_numa_node(pcie_dev, log_file=log_file)
        cpus = self.get_numa_node_cpus(numa, log_file=log_file)
        if log_file is True:
            log_file = sys.stdout

        if log_file:
            log_file.write(f"PCIe={pcie_dev} NUMA={numa} CPUs={cpus}\n")

        return cpus