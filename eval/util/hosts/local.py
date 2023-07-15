from .commands.command import Command
from .commands.local import LocalCommand

from .host import Host

class LocalHost(Host):
    def run_command(self, *args, **kwargs) -> Command:
        return LocalCommand(*args, **kwargs)
