#!/usr/bin/env python3

import math
import sys
import re
import itertools
import statistics

from pathlib import Path
from typing import Any, Callable, Optional, Union

import matplotlib as mpl
import matplotlib.pyplot as plt

import click
import numpy as np

from pubplot import Document

if sys.version_info < (3, 9, 0):
    raise RuntimeError("Python 3.9 or a more recent version is required.")

SYSTEM_NAME = "SyNAPSE"

NFs = {
    "proxy": "Proxy",
    "nat": "NAT",
    "cl": "CL",
    "psd": "PSD",
    "fw": "FW",
    "lb": "LB",
    "hhh": "HHH",
}

HEURISTICS = {
    "max_tpt": "Max. Tpt.",
    "max_cpt": "Max. Comp.",
    "min_cpu": "Min. CPU",
}

acm_acmsmall = {
    'documentclass': 'acmart',
    'document_options': 'acmsmall'
}

inches_per_pt = 1.0 / 72.27
golden_ratio = (1.0 + math.sqrt(5.0)) / 2.0
doc = Document(acm_acmsmall)
width = float(doc.columnwidth)
height = width / golden_ratio
width = width * inches_per_pt
height = height * inches_per_pt * 0.8
figsize = (width, height)

width_third = doc.textwidth / 3
height_third = width_third / golden_ratio
width_third = width_third * inches_per_pt
height_third = height_third * inches_per_pt
figsize_third = (width_third, height_third)

tight_layout_pad = 0.21
linewidth = 0.75
elinewidth = 0.5
capsize = 1
markersize = 2
capthick = 0.5

# This is "colorBlindness::PairedColor12Steps" from R.
# Check others here: https://r-charts.com/color-palettes/#discrete
palette = [
    '#19B2FF',
    '#2ca02c',  # "#32FF00",  # I hate this green, so I changed it... It may
                # not be as color-blind friendly as it was originally but since
                # we also use patterns, it should be fine.
    '#FF7F00',
    '#654CFF',
    '#E51932',
    '#FFBF7F',
    '#FFFF99',
    '#B2FF8C',
    '#A5EDFF',
    '#CCBFFF'
]

hatch_list = ['////////', '-----', '+++++++', '|||||||']

markers_list = ['.', 'o', 'v', 's']

linestyle = [
    (0, (1, 0)),
    (0, (4, 1)),
    (0, (2, 0.5)),
    (0, (1, 0.5)),
    (0, (0.5, 0.5)),
    (0, (4, 0.5, 0.5, 0.5)),
    (0, (3, 1, 1, 1)),
    (0, (8, 1)),
    (0, (3, 1, 1, 1, 1, 1)),
    (0, (3, 1, 1, 1, 1, 1, 1, 1)),
]

prop_cycle = mpl.cycler(color=palette) + mpl.cycler(linestyle=linestyle)

style = {
    # Line styles.
    'axes.prop_cycle': prop_cycle,

    # Grid.
    'grid.linewidth': 0.2,
    'grid.alpha': 0.4,
    'axes.grid': True,
    'axes.axisbelow': True,

    'axes.linewidth': 0.2,

    # Ticks.
    'xtick.major.width': 0.2,
    'ytick.major.width': 0.2,
    'xtick.minor.width': 0.2,
    'ytick.minor.width': 0.2,

    # Font.
    # You can use any of the predefined LaTeX font sizes here as well as
    # "caption", to match the caption size.
    'font.family': 'serif',
    'font.size': doc.footnotesize,
    'axes.titlesize': doc.footnotesize,
    'axes.labelsize': doc.small,
    "figure.labelsize": doc.footnotesize,
    'legend.fontsize': doc.scriptsize,
    'xtick.labelsize': doc.footnotesize,
    'ytick.labelsize': doc.footnotesize,

    'patch.linewidth': 0.2,

    'figure.dpi': 1000,

    'text.usetex': True,

    "text.latex.preamble": """
        \\usepackage[tt=false,type1=true]{libertine}
        \\usepackage[varqu]{zi4}
        \\usepackage[libertine]{newtxmath}
    """,
}


# Apply style globally.
for k, v in style.items():
    mpl.rcParams[k] = v

def get_data(data_dir: Path, pattern: str, keys: list[tuple[str, type]]) -> list[dict]:
    data = []

    for file in data_dir.iterdir():
        match = re.search(pattern, file.stem)
        assert match

        file_data = {
            "config": {},
            "labels": [],
            "values": [],
        }

        for i, key in enumerate(keys):
            name, type = key
            file_data["config"][name] = type(match.group(i+1))
        
        with open(str(file), 'r') as f:
            lines = f.readlines()
            lines = [ l.rstrip().split(',') for l in lines ]
            
            header = lines[0]
            rows   = lines[1:]

            values = []

            for row in rows:
                cols = [ int(c) if '.' not in c else float(c) for c in row ]
                values.append(cols)

            file_data["labels"] = header
            file_data["values"] = values
        
        data.append(file_data)

    return data

def aggregate_values(values: list[list[Union[int, float]]],
                     x_elem: int,
                     y_elem: int) -> list[list[Union[int, float]]]:
    new_values = []

    # Let's calculate the errors.
    # Group data by the first column (the iteration number)    
    values_grouped = [ list(v[1]) for v in itertools.groupby(values, key=lambda x: x[0]) ]

    for vv in values_grouped:
        x_values = [ v[x_elem] for v in vv ]
        y_values = [ v[y_elem] for v in vv ]

        # Assert that they have the same x value
        assert len(set(x_values)) == 1

        x = x_values[0]
        y = y_values[0]
        yerr = 0

        if len(y_values) > 1:
            y = statistics.mean(y_values)
            yerr = statistics.stdev(y_values)
        
        new_values.append([x, y, yerr])

    return new_values

def bar_subplot(ax,
                xlabel: str,
                ylabel: str,
                data: list[dict],
                xtick_labels: Optional[list] = None,
                width_scale: float = 0.7,
                set_palette: Optional[list[str]] = None,
                set_hatch_list: Optional[list[str]] = None,
                **kwargs) -> None:
    x = None
    nb_catgs = len(data)
    bar_width = width_scale/nb_catgs  # The width of the bars.
    offset = bar_width * (1 - nb_catgs) / 2

    if set_palette is None:
        set_palette = palette

    if set_hatch_list is None:
        set_hatch_list = hatch_list

    for d, color, hatch in zip(data, itertools.cycle(set_palette), itertools.cycle(set_hatch_list)):
        if x is None:
            x = np.arange(len(d['values']))  # The xtick_labels locations.

        # Default options.
        options = {
            "fill": False,
            "hatch": hatch,
            "edgecolor": color,
            "error_kw": dict(elinewidth=elinewidth, capsize=capsize,
                             capthick=capthick),
        }
        options.update(kwargs)

        ax.bar(x + offset, d["values"], bar_width, yerr=d["errors"],
               label=d["label"], **options)
        offset += bar_width

    if xlabel is not None:
        ax.set_xlabel(xlabel)
    if ylabel is not None:
        ax.set_ylabel(ylabel)

    if xtick_labels is None:
        ax.set_xticks([])
    else:
        ax.set_xticks(x)
        ax.set_xticklabels(xtick_labels)

    ax.tick_params(axis='both', length=0)
    ax.grid(visible=False, axis='x')

def plot_subplot(ax,
                 xlabel: str,
                 ylabel: str,
                 data: list[dict],
                 set_palette: Optional[list[str]] = None,
                 set_markers_list: Optional[list[str]] = None,
                 **kwargs) -> None:
    if set_palette is None:
        set_palette = palette

    if set_markers_list is None:
        set_markers_list = markers_list

    for d, color, marker in zip(data, itertools.cycle(set_palette), itertools.cycle(markers_list)):
        # Default options.
        options = {
            "marker": marker,
            "markersize": markersize,
            "markerfacecolor": color,
            "linewidth": linewidth,
            "capsize": capsize,
            "capthick": capthick,
        }
        options.update(kwargs)

        ax.errorbar(
            d["x"],
            d["y"],
            yerr=d["yerr"],
            label=d["label"],
            **options
        )

    if xlabel is not None:
        ax.set_xlabel(xlabel)
    if ylabel is not None:
        ax.set_ylabel(ylabel)

    ax.tick_params(axis='both', length=0)
    ax.grid(visible=False, axis='x')

def plot_micro_cached_tables_churn(data_dir: Path,
                                   dest_dir: Path,
                                   opts: dict[str, Any]) -> None:
    fig_name = "cached_tables_churn"
    xlabel = "Churn (fpm)"
    ylabel = "Throughput (Mpps)"

    data_fname_pattern = r"micro_cached_tables_cached_(\d+)_churn"
    data_fname_keys = [ ("cached", int) ]

    data = []

    files_data = get_data(data_dir, data_fname_pattern, data_fname_keys)
    files_data = sorted(files_data, key=lambda x: x["config"]["cached"])

    for file_data in files_data:
        x_elem = 1 # churn column
        y_elem = 3 # throughput (pps) column
    
        config = file_data["config"]
        values = file_data["values"]
        values = aggregate_values(values, x_elem, y_elem)

        assert "cached" in config.keys()
        cached = config["cached"]

        x    = [ v[0] for v in values ]
        y    = [ v[1] / 1e6 for v in values ]
        yerr = [ v[2] / 1e6 for v in values ]

        data.append({
            "label": f"{cached}\%",
            "x": x,
            "y": y,
            "yerr": yerr,
        })

    set_figsize = (width / 2, height / 2)

    fig, ax = plt.subplots()

    plot_subplot(ax, xlabel, ylabel, data)

    ax.legend(loc='lower right')

    ax.set_xscale("symlog")
    ax.set_ylim(0, 150)

    fig.set_size_inches(*set_figsize)
    fig.tight_layout(pad=0.1)

    plt.savefig(dest_dir / f"{fig_name}.pdf")

    if opts.get("save_png", False):
        plt.savefig(dest_dir / f"{fig_name}.png")

@click.command()
@click.argument("data_dir")
@click.argument("plot_dir")
@click.option("--pick", help="Plot only the specified plot")
@click.option("--png", is_flag=True, help="Also save plots as PNG")
def main(data_dir, plot_dir, pick, png):
    data_dir = Path(data_dir)
    plot_dir = Path(plot_dir)

    plot_dir.mkdir(parents=True, exist_ok=True)

    opts = {"save_png": png}

    plots: list[Callable[[Path, Path, dict], None]] = []
    if pick is None:
        plots = [
            plot_micro_cached_tables_churn,
        ]
    else:
        function_name = f"plot_{pick}"
        if function_name not in globals():
            raise RuntimeError(f'Can\'t plot "{pick}"')
        plots = [globals()[function_name]]

    for plot in plots:
        plot(data_dir, plot_dir, opts)


if __name__ == "__main__":
    main()
