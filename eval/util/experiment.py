from rich.console import Group
from rich.live import Live
from rich.progress import (
    BarColumn,
    Progress,
    TextColumn,
    TimeElapsedColumn,
    TimeRemainingColumn,
)

class Experiment:
    def __init__(self, name: str, iterations: int) -> None:
        self.name = name
        self.iterations = iterations

    def run(self, step_progress: Progress, current_iter: int) -> None:
        raise NotImplementedError

    def run_many(self, progress: Progress, step_progress: Progress) -> None:
        task_id = progress.add_task("", total=self.iterations, name=self.name)
        for iter in range(self.iterations):
            self.run(step_progress, iter)
            progress.update(task_id, advance=1)

        progress.update(task_id, description="[bold green] done!")

class ExperimentTracker:
    def __init__(self) -> None:
        self.overall_progress = Progress(
            TimeElapsedColumn(),
            BarColumn(),
            TimeRemainingColumn(),
            TextColumn("{task.description}"),
        )
        self.experiment_iters_progress = Progress(
            TextColumn("  "),
            TextColumn(
                "[bold blue]{task.fields[name]}: " "{task.percentage:.0f}%"
            ),
            BarColumn(),
            TimeRemainingColumn(),
            TextColumn("{task.description}"),
        )
        self.step_progress = Progress(
            TextColumn("  "),
            TimeElapsedColumn(),
            TextColumn("[bold purple]"),
            BarColumn(),
            TimeRemainingColumn(),
            TextColumn("{task.description}"),
        )
        self.progress_group = Group(
            Group(self.step_progress, self.experiment_iters_progress),
            self.overall_progress,
        )
        self.experiments: list[Experiment] = []

    def add_experiment(self, experiment: Experiment) -> None:
        self.experiments.append(experiment)

    def run_experiments(self):
        with Live(self.progress_group):
            nb_exps = len(self.experiments)
            overall_task_id = self.overall_progress.add_task("", total=nb_exps)

            for i, exp in enumerate(self.experiments):
                description = (
                    f"[bold #AAAAAA]({i} out of {nb_exps} experiments)"
                )
                self.overall_progress.update(
                    overall_task_id, description=description
                )
                exp.run_many(
                    self.experiment_iters_progress, self.step_progress
                )
                self.overall_progress.update(overall_task_id, advance=1)

            self.overall_progress.update(
                overall_task_id, description="[bold green] All done!"
            )
