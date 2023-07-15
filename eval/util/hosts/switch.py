#!/usr/bin/env python3

from pathlib import Path
from typing import Any, TextIO, Union

from .remote import RemoteHost

class Switch:
    def __init__(
        self,
        hostname: str,
        src: Union[str, Path],
        compiler: Union[str, Path],
        build_vars: dict[str, Any] = {},
        log_file: Union[bool, TextIO] = False,
    ) -> None:
        self.host = RemoteHost(hostname)
        self.src = Path(src)
        self.compiler = Path(compiler)
        self.build_vars = build_vars
        self.log_file = log_file

    def install(self) -> None:
        compilation_cmd = f"{str(self.compiler)} {str(self.src)}"

        vars = [ f"-D{k}={v}" for k,v in self.build_vars.items() ]
        compilation_cmd += ' ' + ' '.join(vars)

        cmd = self.host.run_command(
            compilation_cmd,
            log_file=self.log_file,
        )

        cmd.watch()
