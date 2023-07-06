#!/usr/bin/env python3

import itertools

from util.experiment import Experiment
from util.hosts import Controller

from netexp.pktgen.dpdk import DpdkPktgen

from pathlib import Path
from collections import defaultdict
from typing import Any

from rich.console import Console
from rich.progress import Progress

DEFAULT_PRECISION = 100_000_000  # in bps (100 Mbps).

class ThroughputExperiment(Experiment):
    def __init__(
        self,
        name: str,
        iterations: int,
        save_name: Path,
        dut: Controller,
        pktgen: DpdkPktgen,
        pcaps: list[Path],
        dut_configs: list[dict[str, Any]],
        const_configs: dict[str, Any] = {},
        precision: int = DEFAULT_PRECISION,
        console: Console = Console()
    ) -> None:
        super().__init__(name, iterations)
        self.save_name = save_name
        self.dut = dut
        self.pktgen = pktgen
        self.pcaps = pcaps
        self.dut_configs = dut_configs
        self.precision = precision
        self.console = console
        self.const_configs = const_configs

        config_header = self.dut.get_config_header()

        if len(const_configs.keys()):
            const_configs_header = ",".join(const_configs.keys())
            const_configs_header += ","
        else:
            const_configs_header = ""

        header = f"{const_configs_header}pcaps,{config_header},throughput (bps),throughput (pps)\n"

        self.experiment_tracker = defaultdict(int)

        # If file exists, continue where we left off.
        if self.save_name.exists():
            with open(self.save_name) as f:
                read_header = f.readline()
                assert header == read_header
                for row in f.readlines():
                    # pps
                    end = row.rfind(",")
                    row = row[:end]

                    # bps
                    end = row.rfind(",")
                    row = row[:end]

                    self.experiment_tracker[row] += 1
        else:
            with open(self.save_name, "w") as f:
                f.write(header)
        
    def run(self, step_progress: Progress, current_iter: int) -> None:
        experiments = list(
            itertools.product(
                self.pcaps,
                self.dut_configs,
            )
        )

        task_id = step_progress.add_task(self.name, total=len(experiments))

        for pcap, dut_config in experiments:
            exp_str = ""
            
            if len(self.const_configs.keys()):
                const_config_str = ",".join(str(self.const_configs[key]) for key in self.const_configs.keys())
                exp_str += f"{const_config_str},"

            config_str = self.dut.get_config_str(dut_config)
            exp_str += f"{pcap.name},{config_str}"

            if self.experiment_tracker[exp_str] > current_iter:
                self.console.log(f"[orange1]Skipping: {exp_str}")
                step_progress.update(task_id, advance=1)
                continue

            step_progress.update(task_id, description=f"({exp_str})")
            
            self.pktgen.set_pcap(str(pcap))

            self.dut.start(dut_config)

            throughput_bps, throughput_pps  = self.dut.zero_loss_throughput(
                self.pktgen, precision=self.precision
            )

            self.dut.stop()

            with open(self.save_name, "a") as f:
                f.write(f"{exp_str},{throughput_bps},{throughput_pps}\n")

            step_progress.update(task_id, advance=1)

        step_progress.update(task_id, visible=False)
