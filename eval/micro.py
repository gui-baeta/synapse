#!/usr/bin/env python3

import click
import asyncio
import sys
import os
import math

from pathlib import Path
from typing import Any, TextIO

from rich.console import Console

from util.set_constants import set_constants
from util.hosts import load_controller, load_pktgen
from util.experiment import Experiment, ExperimentTracker
from util.throughput import ThroughputExperiment
from util.pcap_churn import (
    get_churn_config,
    generate_churn_pcap
)

from netexp.helpers import upload_file

MICRO_SOURCES_DIR = Path(os.path.abspath(os.path.dirname(__file__))) / Path("micro")
DATA_STRUCTURES_SOURCES_DIR = MICRO_SOURCES_DIR / Path("data-structures")

console = Console()

if sys.version_info < (3, 9, 0):
    raise RuntimeError("Python 3.9 or a more recent version is required.")

def get_closest_power_of_two(value):
    p = 0
    
    while (1 << (p + 1)) < value:
        p += 1
    
    delta_lo = value - (1 << p)
    delta_hi = (1 << (p + 1)) - value

    return (1 << p) if delta_lo < delta_hi else (1 << (p + 1))

def fix_churn(
    timeout_ms: int,
    rate_gbps: int,
    cache_occupancy: float,
    churn: int,
) -> tuple[int, int, float]:
    ACCEPTABLE_ERROR = 0.01
    CHURN_PRECISION = 1
    CHURN_INC_STEP = 0.1 # 10%

    best_churn: int = churn
    best_cache_size: int = 0
    best_delta: float = 100 # %

    churns_tried = set()

    while True:
        report = get_churn_config(
            timeout_ms * 1000,
            rate_gbps,
            churn,
        )

        churn = report["churn"]
        total_flows = report["total_flows"]

        # We're in a loop... Get out!
        if churn in churns_tried:
            break
    
        churns_tried.add(churn)
        
        cached_flows = cache_occupancy * total_flows
        cache_size = get_closest_power_of_two(cached_flows) if cached_flows > 0 else 0

        real_occupancy = cache_size / total_flows
        occupancy_delta = real_occupancy - cache_occupancy

        # print(f"[*] churn {churn} flows {total_flows} occ {cache_occupancy*100:.2f}% cached {cached_flows} "
        #         f"cache {cache_size} occ {real_occupancy*100:.2f} ({occupancy_delta*100:.2f}%)")
        
        if abs(occupancy_delta) <= ACCEPTABLE_ERROR:
            return churn, cache_size, occupancy_delta
    
        if abs(occupancy_delta) < abs(best_delta):
            best_delta = occupancy_delta
            best_churn = churn
    
        sign = (occupancy_delta / abs(occupancy_delta))
        new_churn = int(churn * (1 + sign * CHURN_INC_STEP))

        # Not enough precision!
        if abs(new_churn - churn) < CHURN_PRECISION:
            break
        
        churn = new_churn

    return best_churn, best_cache_size, best_delta

def get_cached_tables_config(
    timeout_ms: int,
    rate_gbps: int,
) -> list[tuple[int,int,float,float]]:
    churn_values = [10_000, 100_000, 1_000_000]
    cache_occupancy_bounds = [0, 0.25, 0.5, 0.75, 1]
    config = []

    for churn in churn_values:
        for occupancy in cache_occupancy_bounds:
            new_churn, cache_size, occupancy_delta = fix_churn(timeout_ms, rate_gbps, occupancy, churn)
            config.append((new_churn, cache_size, occupancy, occupancy_delta))
            print(f"Churn {churn:,} -> {new_churn:,} cache {cache_size:,} occ {occupancy*100:.2f} ({occupancy_delta*100:.2f})")
    print()
    return config

async def get_cached_tables_experiments(
    data_dir: Path,
    iterations: int,
    controller_log_file: TextIO,
    pktgen_log_file: TextIO,
    config: dict[str, Any],
) -> list[Experiment]:
    experiments: list[Experiment] = []

    config["devices"]["controller"]["timeout"] = 100
    timeout_ms = config["devices"]["controller"]["timeout"]
    line_rate_gbps = config["devices"]["pktgen"]["tx_line_rate"]

    cached_tables_config = get_cached_tables_config(timeout_ms, line_rate_gbps)

    print()
    for c in sorted(cached_tables_config, key=lambda k: k[2]):
        print("  ", c)
    print()

    pcap_tasks = {}
    controllers_tasks = {}

    load_pktgen_task = asyncio.create_task(
        load_pktgen(pktgen_log_file, config, console)
    )

    for c in cached_tables_config:
        churn, cache_size, _, _ = c

        if churn not in pcap_tasks.keys():
            pcap_task = asyncio.create_task(
                generate_churn_pcap(churn, timeout_ms * 1000)
            )
            pcap_tasks[churn] = pcap_task

        dataplane_build_vars = {}

        if cache_size not in controllers_tasks.keys():
            if cache_size == 0:
                controller_src = DATA_STRUCTURES_SOURCES_DIR / Path("tables") / Path("tables.cpp")
                dataplane_src = DATA_STRUCTURES_SOURCES_DIR / Path("tables") / Path("tables.p4")
            else:
                controller_src = DATA_STRUCTURES_SOURCES_DIR / Path("cached-tables") / Path("cached-tables.cpp")
                dataplane_src = DATA_STRUCTURES_SOURCES_DIR / Path("cached-tables") / Path("cached-tables.p4")

                dataplane_build_vars["REGISTER_INDEX_WIDTH"] = int(math.log(cache_size,2))
            
            remote_controller_src = Path(config["paths"]["controller_path"]) / Path(controller_src.name)
            remote_dataplane_src = Path(config["paths"]["dataplane_path"]) / Path(dataplane_src.name)

            upload_file(
                config["hosts"]["controller"],
                str(controller_src),
                str(remote_controller_src),
                controller_log_file,
                overwrite=True,
            )

            upload_file(
                config["hosts"]["controller"],
                str(dataplane_src),
                str(remote_dataplane_src),
                controller_log_file,
                overwrite=True,
            )

            load_controller_task = asyncio.create_task(
                load_controller(
                    controller_log_file,
                    remote_controller_src,
                    remote_dataplane_src,
                    config,
                    console,
                    dataplane_build_vars,
                )
            )
            controllers_tasks[cache_size] = load_controller_task
    
    experiments: list[Experiment] = []
    
    remote_pcaps = {}

    pktgen = await load_pktgen_task

    for churn in pcap_tasks.keys():
        pcap_task = pcap_tasks[churn]
        local_pcap_path, _ = await pcap_task
        remote_pcap_path = Path(config["paths"]["pktgen_pcaps_path"]) / Path(local_pcap_path.name)

        upload_file(
            config["hosts"]["pktgen"],
            str(local_pcap_path),
            str(remote_pcap_path),
            pktgen_log_file,
            overwrite=False,
        )

        remote_pcaps[churn] = remote_pcap_path

    for cache_size in controllers_tasks.keys():
        relevant_configs = list(filter(lambda f: f[1] == cache_size, cached_tables_config))

        for r in relevant_configs:
            churn = r[0]
            occupancy = r[1]

            pcap = remote_pcaps[churn]
            controller_task = controllers_tasks[cache_size]

            controller = await controller_task

            name = f"cached-tables cache occupancy {occupancy} churn {churn} throughput"
            filename = f"micro_cache_occ_{occupancy}_churn_{churn}_throughput"

            experiments.append(
                ThroughputExperiment(
                    name,
                    iterations=iterations,
                    save_name=data_dir / Path(f"{filename}.csv"),
                    dut=controller,
                    pktgen=pktgen,
                    pcaps=[pcap],
                    dut_configs=[
                        {
                            "timeout_ms": timeout_ms,
                        }
                    ],
                    const_configs={
                        "occupancy": occupancy,
                    }
                ),
            )

    return experiments

async def get_micro_experiments(
    data_dir: Path,
    iterations: int,
    controller_log_file: TextIO,
    pktgen_log_file: TextIO,
    config: dict[str, Any],
) -> list[Experiment]:
    cache_sizes = [ 0, 512, 1024, 2048, 4096 ]
    churn_values = [1_000, 10_000, 100_000, 1_000_000]

    controllers_tasks = {}

    load_pktgen_task = asyncio.create_task(
        load_pktgen(pktgen_log_file, config, console)
    )

    for cache_size in cache_sizes:
        dataplane_build_vars = {}

        if cache_size == 0:
            controller_src = DATA_STRUCTURES_SOURCES_DIR / Path("tables") / Path("tables.cpp")
            dataplane_src = DATA_STRUCTURES_SOURCES_DIR / Path("tables") / Path("tables.p4")
        else:
            controller_src = DATA_STRUCTURES_SOURCES_DIR / Path("cached-tables") / Path("cached-tables.cpp")
            dataplane_src = DATA_STRUCTURES_SOURCES_DIR / Path("cached-tables") / Path("cached-tables.p4")

            dataplane_build_vars["REGISTER_INDEX_WIDTH"] = int(math.log(cache_size,2))
            assert 2 ** int(math.log(cache_size,2)) == cache_size
            
        controllers_tasks[cache_size] = {}

        config["timeout_ms"] = config["devices"]["controller"]["timeout"]

        remote_controller_src = Path(config["paths"]["controller_path"]) / Path(controller_src.name)
        remote_dataplane_src = Path(config["paths"]["dataplane_path"]) / Path(dataplane_src.name)

        upload_file(
            config["hosts"]["controller"],
            str(controller_src),
            str(remote_controller_src),
            controller_log_file,
            overwrite=True,
        )

        upload_file(
            config["hosts"]["controller"],
            str(dataplane_src),
            str(remote_dataplane_src),
            controller_log_file,
            overwrite=True,
        )

        load_controller_task = asyncio.create_task(
            load_controller(
                controller_log_file,
                remote_controller_src,
                remote_dataplane_src,
                config,
                console,
                dataplane_build_vars,
            )
        )
        controllers_tasks[cache_size] = load_controller_task

    pcap_tasks = []
    remote_pcaps = []

    timeout_ms = config["devices"]["controller"]["timeout"]

    for churn_value in churn_values:
        task = asyncio.create_task(
            generate_churn_pcap(churn_value, timeout_ms * 1000)
        )
        pcap_tasks.append(task)

    pktgen = await load_pktgen_task

    for pcap_task in pcap_tasks:
        local_pcap_path, _ = await pcap_task
        remote_pcap_path = Path(config["paths"]["pktgen_pcaps_path"]) / Path(local_pcap_path.name)

        upload_file(
            config["hosts"]["pktgen"],
            str(local_pcap_path),
            str(remote_pcap_path),
            pktgen_log_file,
            overwrite=False,
        )

        remote_pcaps.append(remote_pcap_path)

    experiments: list[Experiment] = []

    for cache_size in controllers_tasks.keys():
        controller_task = controllers_tasks[cache_size]
        controller = await controller_task

        name = f"cached table size={cache_size} throughput"
        filename = f"micro_cached_table_size_{cache_size}_throughput"

        experiments.append(
            ThroughputExperiment(
                name,
                iterations=iterations,
                save_name=data_dir / Path(f"{filename}.csv"),
                dut=controller,
                pktgen=pktgen,
                pcaps=remote_pcaps,
                dut_configs=[
                    {
                        "timeout_ms": timeout_ms,
                    }
                ],
            ),
        )

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
    "--iters",
    "-i",
    type=int,
    default=1,
    show_default=True,
    help="Number of iterations to run each experiment.",
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
    iters,
    config_file,
):
    data_dir = Path(data_dir)
    data_dir.mkdir(parents=True, exist_ok=True)

    config = set_constants(config_file)

    controller_log_file = open(config["logs"]["controller_log"], "a", encoding="utf-8")
    pktgen_log_file = open(config["logs"]["pktgen_log"], "a", encoding="utf-8")

    # experiments = asyncio.run(
    #     get_cached_tables_experiments(
    #         data_dir,
    #         iters,
    #         controller_log_file,
    #         pktgen_log_file,
    #         config,
    #     )
    # )

    experiments = asyncio.run(
        get_micro_experiments(
            data_dir,
            iters,
            controller_log_file,
            pktgen_log_file,
            config,
        )
    )

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
