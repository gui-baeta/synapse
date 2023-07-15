#!/usr/bin/env python3

from util.throughput import Throughput
from util.hosts.controller import Controller
from util.hosts.switch import Switch
from util.hosts.pktgen import Pktgen

from pathlib import Path
from collections import defaultdict

from rich.console import Console
from rich.progress import Progress

DEFAULT_THROUGHPUT_MID_CHURN = 50_000 # 50 Gbps
DEFAULT_NUM_CHURN_STEPS      = 10

class Churn(Throughput):
    def __init__(
        self,
        name: str,
        iterations: int,
        save_name: Path,
        switch: Switch,
        controller: Controller,
        pktgen: Pktgen,
        nb_churn_steps: int = DEFAULT_NUM_CHURN_STEPS,
        console: Console = Console()
    ) -> None:
        super().__init__(
            name=name,
            iterations=iterations,
            save_name=save_name,
            switch=switch,
            controller=controller,
            pktgen=pktgen,
            console=console,
        )
    
        assert nb_churn_steps % 2 == 0
        self.nb_churn_steps = nb_churn_steps

    def _sync(self):
        header = f"iteration,churn (fpm),throughput (bps),throughput (pps)\n"

        self.experiment_tracker = defaultdict(int)

        # If file exists, continue where we left off.
        if self.save_name.exists():
            with open(self.save_name) as f:
                read_header = f.readline()
                assert header == read_header
                for row in f.readlines():
                    cols = row.split(",")
                    it = int(cols[0])
                    self.experiment_tracker[it] += 1
        else:
            with open(self.save_name, "w") as f:
                f.write(header)
    
    def _find_half_perf_churn(self, max_churn: int):
        # Let's find out the maximum churn we can handle under low rate.

        churn = 60
        rate  = DEFAULT_THROUGHPUT_MID_CHURN

        while True:
            if self.pktgen.log_file:
                self.pktgen.log_file.write(
                    f"Trying to find half perf churn: {churn:,} fpm\n"
                )

            throughput_bps, _ = self._find_stable_throughput(
                churn=churn,
                steps=1,
                max_rate=rate,
            )

            # Throughput equals 0 if it wasn't stable.
            if throughput_bps == 0 or churn == max_churn:
                break
            
            churn = min(churn * 2, max_churn)
        
        self.pktgen.log_file.write(f"Half perf churn: {churn:,} fpm\n")

        return churn

    def run(self, step_progress: Progress, current_iter: int) -> None:
        task_id = step_progress.add_task(self.name, total=self.nb_churn_steps)

        # Check if we already have everything before running all the programs.
        completed = True
        for i in range(self.nb_churn_steps):
            if self.experiment_tracker[i] <= current_iter:
                completed = False
                break
        if completed:
            return

        self.switch.install()
        
        self.controller.launch()
        self.pktgen.launch()

        max_churn = self.pktgen.wait_ready()
        self.controller.wait_ready()

        churns = []

        for i in range(self.nb_churn_steps):
            if self.experiment_tracker[i] > current_iter:
                self.console.log(f"[orange1]Skipping: iteration {i}")
                step_progress.update(task_id, advance=1)
                continue

            if len(churns) == 0:
                step_progress.update(task_id, description=f"Finding half perf churn...")

                half_perf_churn   = self._find_half_perf_churn(max_churn)
                steps_bellow_half = self.nb_churn_steps * 3/4
                churns_steps      = half_perf_churn / steps_bellow_half
                churns            = [ int(i * churns_steps) for i in range(self.nb_churn_steps) ]

            churn = churns[i]

            if self.pktgen.log_file:
                self.pktgen.log_file.write(f"Trying churn {churn:,}\n")

            step_progress.update(
                task_id,
                description=f"{churn:,} fpm (half perf churn {half_perf_churn:,} fpm) ({i+1}/{len(churns)})"
            )

            throughput_bps, throughput_pps = self._find_stable_throughput(
                churn=churn,
                steps=self.throughput_search_steps,
                max_rate=self.max_throughput_mbps,
            )

            with open(self.save_name, "a") as f:
                f.write(f"{i},{churn},{throughput_bps},{throughput_pps}\n")

            step_progress.update(task_id, advance=1)

        step_progress.update(task_id, visible=False)

        self.pktgen.close()
        self.controller.stop()
