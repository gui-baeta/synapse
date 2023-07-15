#!/usr/bin/env python3

import sys
import click
import tomli
import math

from pathlib import Path

from rich.console import Console

from util.hosts.pktgen import Pktgen
from util.hosts.switch import Switch
from util.hosts.controller import Controller
from util.experiment import Experiment, ExperimentTracker
from util.throughput import Throughput
from util.churn import Churn

if sys.version_info < (3, 9, 0):
    raise RuntimeError("Python 3.9 or a more recent version is required.")

console = Console()

def get_closest_power_of_two(value):
    p = 0
    
    while (1 << (p + 1)) < value:
        p += 1
    
    delta_lo = value - (1 << p)
    delta_hi = (1 << (p + 1)) - value

    return (1 << p) if delta_lo < delta_hi else (1 << (p + 1))

def get_cached_tables_churn_experiments(config: list, data_dir: Path) -> list[Experiment]:
    experiments = []

    iterations         = 1
    cache_size         = 1024
    pkt_size           = 64
    expiration_time_ms = 10
    rel_cached_flows   = [ 0, 0.25, 0.50, 0.75, 1 ]

    cache_bit_width = int(math.log(cache_size, 2))

    # Cache size must be a power of 2
    assert cache_size > 1 and ((cache_size - 1) & cache_size) == 0

    for rel_cached in rel_cached_flows:
        nb_flows = int(cache_size / rel_cached) if rel_cached > 0 else cache_size

        exp_name   = f"cached-tables-{int(rel_cached*100)}%-churn"
        data_fname = f"micro_cached_tables_cached_{int(rel_cached*100)}_churn.csv"

        switch_src     = "cached-tables.p4"  if rel_cached > 0 else "tables.p4"
        controller_src = "cached-tables.cpp" if rel_cached > 0 else "tables.cpp"

        pktgen = Pktgen(
            hostname=config["hosts"]["pktgen"],
            rx_pcie_dev=config["devices"]["pktgen"]["rx_dev"],
            tx_pcie_dev=config["devices"]["pktgen"]["tx_dev"],
            nb_tx_cores=config["devices"]["pktgen"]["nb_tx_cores"],
            nb_flows=nb_flows,
            pkt_size=pkt_size,
            exp_time_us=expiration_time_ms * 1000,
            crc_unique_flows=(nb_flows <= cache_size),
            crc_bits=cache_bit_width,
            pktgen_exe=Path(config["paths"]["pktgen"]),
            log_file=config["logs"]["pktgen"],
        )

        switch = Switch(
            hostname=config["hosts"]["switch"],
            src=Path(config["paths"]["dataplane"]) / Path(switch_src),
            compiler=config["paths"]["dataplane_build_script"],
            build_vars={
                "REGISTER_INDEX_WIDTH": cache_bit_width,
            },
            log_file=config["logs"]["controller"],
        )

        controller = Controller(
            hostname=config["hosts"]["controller"],
            src=Path(config["paths"]["dataplane"]) / Path(controller_src),
            builder=config["paths"]["controller_build_script"],
            sde_install=config["paths"]["sde_install"],
            timeout_ms=expiration_time_ms,
            log_file=config["logs"]["controller"],
        )

        churn = Churn(
            name=exp_name,
            iterations=iterations,
            save_name=data_dir / Path(data_fname),
            switch=switch,
            controller=controller,
            pktgen=pktgen,
            console=console,
        )

        experiments.append(churn)

    return experiments

def get_micro_experiments(config: dict, data_dir: Path) -> list[Experiment]:
    experiments = []
    experiments += get_cached_tables_churn_experiments(config, data_dir)
    return experiments

@click.command()
@click.argument("data_dir")
@click.option(
    "--filter",
    "-f",
    multiple=True,
    help="Filter experiments by name. Multiple filters are treated as OR.",
)
@click.option(
    "--config-file",
    "-c",
    type=click.Path(exists=True),
    default="experiment_config.toml",
    show_default=True,
    help="Path to config file.",
)
def main(
    data_dir,
    filter,
    config_file,
):
    data_dir = Path(data_dir)
    data_dir.mkdir(parents=True, exist_ok=True)

    with open(config_file, "rb") as f:
        config = tomli.load(f)
    
    experiments = get_micro_experiments(config, data_dir)
    exp_tracker = ExperimentTracker()

    for exp in experiments:
        if filter:
            for f in filter:
                if f in exp.name:
                    break
            else:
                continue

        exp_tracker.add_experiment(exp)

    exp_tracker.run_experiments()


if __name__ == "__main__":
    main()
