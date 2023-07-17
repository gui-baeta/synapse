#!/usr/bin/env python3

import time

from util.experiment import Experiment
from util.hosts.controller import Controller
from util.hosts.switch import Switch
from util.hosts.pktgen import Pktgen

from pathlib import Path

from rich.console import Console
from rich.progress import Progress

DEFAULT_MAX_THROUGHPUT          = 100_000 # 100 Gbps
DEFAULT_THROUGHPUT_SEARCH_STEPS = 10
DEFAULT_DURATION                = 5       # Seconds
DEFAULT_MAX_ACCEPTABLE_LOSS     = 0.001   # 0.1%
DEFAULT_WARMUP_TIME             = 5       # 5 seconds
DEFAULT_WARMUP_RATE             = 1       # 1 Mbps
DEFAULT_REST_TIME               = 2       # 2 seconds
DEFAULT_CHURN                   = 0       # No churn

class Throughput(Experiment):
    def __init__(
        self,
        name: str,
        iterations: int,
        save_name: Path,
        switch: Switch,
        controller: Controller,
        pktgen: Pktgen,
        churn: int = DEFAULT_CHURN,
        max_throughput_mbps: int = DEFAULT_MAX_THROUGHPUT,
        target_duration: int = DEFAULT_DURATION,
        throughput_search_steps: int = DEFAULT_THROUGHPUT_SEARCH_STEPS,
        max_loss: float = DEFAULT_MAX_ACCEPTABLE_LOSS,
        console: Console = Console()
    ) -> None:
        super().__init__(name, iterations)
        self.save_name = save_name
        self.switch = switch
        self.controller = controller
        self.pktgen = pktgen
        self.churn = churn
        self.max_throughput_mbps = max_throughput_mbps
        self.target_duration = target_duration
        self.throughput_search_steps = throughput_search_steps
        self.max_loss = max_loss
        self.console = console

        self._sync()

    def _sync(self):
        header = f"throughput (bps),throughput (pps)\n"

        self.experiment_tracker = 0

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
    
    def _find_stable_throughput(
        self,
        churn: int = DEFAULT_CHURN,
        steps: int = DEFAULT_THROUGHPUT_SEARCH_STEPS,
        max_rate: int = DEFAULT_MAX_THROUGHPUT,
    ) -> tuple[int,int]:
        log_file = self.pktgen.log_file
        pkt_size = self.pktgen.pkt_size
        
        if not (0 <= self.max_loss < 1):
            raise ValueError("max_loss must be in [0, 1).")

        rate_lower = 0         # Lower bound.
        rate_upper = max_rate  # Upper bound.

        real_throughput_bps_winner = 0
        real_throughput_pps_winner = 0

        current_rate = rate_upper

        # Setting the churn value
        self.pktgen.set_churn(churn)

        # Setting warmup duration
        self.pktgen.set_warmup_duration(DEFAULT_WARMUP_TIME)

        # We iteratively refine the bounds until the difference between them is
        # less than the specified precision.
        for i in range(steps):
            if log_file:
                log_file.write(f"[{i+1}/{steps}] Trying rate {current_rate:,} Mbps\n")

            nb_tx_pkts = 0
            nb_rx_pkts = 0

            while nb_tx_pkts == 0:
                self.pktgen.reset_stats()
                self.pktgen.set_rate(current_rate)
                
                # Run pktgen with warmup
                self.pktgen.run(self.target_duration)
                self.pktgen.wait_ready()
                
                # Let the flows expire.
                time.sleep(DEFAULT_REST_TIME)

                nb_tx_pkts, nb_rx_pkts = self.pktgen.get_stats()

                if nb_tx_pkts == 0:
                    log_file.write(f"No packets flowing, repeating run\n")

            nb_tx_bits = nb_tx_pkts * (pkt_size + 20) * 8
            nb_rx_bits = nb_rx_pkts * (pkt_size + 20) * 8

            real_throughput_tx_bps = int(nb_tx_bits / self.target_duration)
            real_throughput_tx_pps = int(nb_tx_pkts / self.target_duration)

            real_throughput_rx_bps = int(nb_rx_bits / self.target_duration)
            real_throughput_rx_pps = int(nb_rx_pkts / self.target_duration)

            loss = 1 - nb_rx_pkts / nb_tx_pkts

            if log_file:
                tx_Gbps = real_throughput_tx_bps / 1e9
                tx_Mpps = real_throughput_tx_pps / 1e6

                rx_Gbps = real_throughput_rx_bps / 1e9
                rx_Mpps = real_throughput_rx_pps / 1e6

                log_file.write("\n")
                log_file.write(f"TX {tx_Mpps:.2f} Mpps {tx_Gbps:.2f} Gbps\n")
                log_file.write(f"RX {rx_Mpps:.2f} Mpps {rx_Gbps:.2f} Gbps\n")
                log_file.write(f"Lost {loss*100:.2f}% of packets\n")
                log_file.flush()

            if loss > self.max_loss:
                rate_upper = current_rate
            else:
                if current_rate == rate_upper:
                    return real_throughput_tx_bps, real_throughput_tx_pps

                rate_lower = current_rate

                real_throughput_bps_winner = real_throughput_tx_bps
                real_throughput_pps_winner = real_throughput_tx_pps

            current_rate = int((rate_upper + rate_lower) / 2)

        # Found a rate.
        return real_throughput_bps_winner, real_throughput_pps_winner

    def run(self, step_progress: Progress, current_iter: int) -> None:
        self.switch.install()
        
        self.controller.launch()
        self.pktgen.launch()

        self.pktgen.wait_launch()
        self.controller.wait_ready()

        task_id = step_progress.add_task(self.name, total=1)

        if self.experiment_tracker > current_iter:
            self.console.log(f"[orange1]Skipping: {current_iter}")
            step_progress.update(task_id, advance=1)
            return

        step_progress.update(task_id, description=f"({current_iter})")

        throughput_bps, throughput_pps = self._find_stable_throughput(
            churn=self.churn,
            steps=self.throughput_search_steps,
            max_rate=self.max_throughput_mbps,
        )

        with open(self.save_name, "a") as f:
            f.write(f"{throughput_bps},{throughput_pps}\n")

        step_progress.update(task_id, advance=1)
        step_progress.update(task_id, visible=False)

        self.pktgen.close()
        self.controller.stop()
