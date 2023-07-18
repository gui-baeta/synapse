#!/usr/bin/env python3

from pathlib import Path
from typing import Any, TextIO, Union

from .remote import RemoteHost

CONTROLLER_FLAGS   = "--hw"
MIN_TIMEOUT        = 10 # miliseconds

class Controller:
    def __init__(
        self,
        hostname: str,
        src: Union[str, Path],
        builder: Union[str, Path],
        sde_install: Union[str, Path],
        timeout_ms: int = MIN_TIMEOUT,
        log_file: Union[bool, TextIO] = False,
    ) -> None:
        self.host = RemoteHost(hostname)

        self.src = Path(src)
        self.builder = Path(builder)
        self.sde_install = Path(sde_install)
        self.timeout_ms = timeout_ms
        self.log_file = log_file

        self.controller_cmd = None

        if timeout_ms < MIN_TIMEOUT:
            raise Exception(f"Timeout value must be >= {MIN_TIMEOUT}ms (is {timeout_ms}ms)")
        
        assert self.host.remote_file_exists(self.src)
        
    def __compile(self) -> None:
        compilation_cmd = f"{self.controller_env} {str(self.builder)} {str(self.src)}"
        cmd = self.host.run_command(
            compilation_cmd,
            dir=str(self.src.parent),
            log_file=self.log_file,
        )
        cmd.watch()

        self.controller_cmd = None

    def launch(self) -> None:
        self.__compile()

        # The build script generates an executable with the same name as the source file,
        # minus the extension.
        self.exe = self.src.stem

        cmd = f"{self.controller_env} ./{self.exe} {self.timeout_ms} {CONTROLLER_FLAGS}"

        self.controller_cmd = self.host.run_command(
            cmd,
            dir=str(self.src.parent),
            log_file=self.log_file,
        )

    def wait_ready(self) -> None:
        # Wait for the controller to be ready.
        # It prints the message "Controller is ready." when it's ready.

        if self.controller_cmd is None:
            raise RuntimeError("Controller not started")

        self.controller_cmd.watch(
            stop_pattern="Controller is ready",
        )

    def stop(self) -> None:
        if self.controller_cmd is None:
            return

        # Kill all instances
        cmd = f"killall {self.exe}"

        self.host.run_command(
            cmd,
            log_file=self.log_file,
        )

        self.controller_cmd.watch()

        self.controller_cmd = None
        self.exe = None
    
    def __del__(self):
        self.stop()
    
    @property
    def controller_env(self) -> str:
        if hasattr(self, '_controller_env'):
            return self._controller_env
        
        env_vars_dict = {
            "SDE_INSTALL": [ str(self.sde_install) ],
            "LD_LIBRARY_PATH": [
                "/usr/local/lib/",
                f"{str(self.sde_install)}/lib/"
            ],
        }

        all_env_list = [ f"{k}={':'.join(env_vars_dict[k])}" for k in env_vars_dict.keys() ]
        self._controller_env = ' '.join(all_env_list)

        return self._controller_env
