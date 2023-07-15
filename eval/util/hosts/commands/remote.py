import re
import select
import sys
import termios
import time
import tty
import socket
import paramiko

from typing import TextIO, Union, Optional, Callable

from .command import Command

class RemoteCommand(Command):
    def __init__(
        self,
        ssh_client: paramiko.SSHClient,
        command: str,
        dir: Optional[str] = None,
        source_bashrc: bool = False,
        log_file: Union[bool, str, TextIO] = False,
        pty: bool = False,
    ) -> None:
        super().__init__(command, dir, source_bashrc, log_file)
        self.ssh_client = ssh_client

        transport = ssh_client.get_transport()

        if transport is None:
            raise RuntimeError("Failed to get transport from client.")

        session = transport.open_session()

        if pty:
            session.setblocking(0)
            session.get_pty()

        session.exec_command(self.command)

        self.cmd_ = session

    def send(self, data: Union[str, bytes]) -> None:
        self.cmd_.send(data)

    def recv(self, size: int) -> str:
        data = self.cmd_.recv(size)
        return data.decode("utf-8")

    def recv_stderr(self, size: int) -> str:
        data = self.cmd_.recv_stderr(size)
        return data.decode("utf-8")

    def exit_status_ready(self) -> bool:
        return self.cmd_.exit_status_ready()

    def watch(
        self,
        stop_condition: Optional[Callable[[], bool]] = None,
        keyboard_int: Optional[Callable[[], None]] = None,
        timeout: Optional[float] = None,
        stop_pattern: Optional[str] = None,
        max_match_length: Optional[int] = None,
    ) -> str:
        if stop_condition is None:
            stop_condition = self.cmd_.exit_status_ready

        assert stop_condition is not None

        if timeout is None:
            deadline = None
        else:
            deadline = time.time() + timeout

        if max_match_length is None:
            max_match_length = 1024

        output = ""

        def continue_running():
            if (deadline is not None) and (time.time() > deadline):
                return False

            if stop_pattern is not None:
                search_len = min(len(output), max_match_length)
                if re.search(stop_pattern, output[-search_len:]):
                    return False

            return not stop_condition()

        keep_going = True
        try:
            while keep_going:
                time.sleep(0.01)

                # We consume the output one more time after it's done.
                # This prevents us from missing the last bytes.
                keep_going = continue_running()

                while self.cmd_.recv_ready():
                    data = self.cmd_.recv(512)
                    decoded_data = data.decode("utf-8")
                    output += decoded_data
                    if self.log_file:
                        self.log_file.write(decoded_data)
                        self.log_file.flush()

                while self.cmd_.recv_stderr_ready():
                    data = self.cmd_.recv_stderr(512)
                    decoded_data = data.decode("utf-8")
                    output += decoded_data
                    if self.log_file:
                        self.log_file.write(decoded_data)
                        self.log_file.flush()

        except KeyboardInterrupt:
            if keyboard_int is not None:
                keyboard_int()
            raise

        return output

    def recv_exit_status(self) -> int:
        return self.cmd_.recv_exit_status()

    def fileno(self) -> int:
        return self.cmd_.fileno()

    def run_console_commands(
        self,
        commands: Union[str, list[str]],
        timeout: float = 1.0,
        console_pattern: Optional[str] = None,
    ) -> str:
        if not isinstance(commands, list):
            commands = [commands]

        if console_pattern is not None:
            console_pattern_len = len(console_pattern)
        else:
            console_pattern_len = None

        output = ""
        for cmd in commands:
            self.send(cmd + "\n")
            output += self.watch(
                keyboard_int=lambda: self.send("\x03"),
                timeout=timeout,
                stop_pattern=console_pattern,
                max_match_length=console_pattern_len,
            )

        return output

    def posix_shell(self) -> None:
        oldtty = termios.tcgetattr(sys.stdin)
        try:
            tty.setraw(sys.stdin.fileno())
            tty.setcbreak(sys.stdin.fileno())

            self.pktgen.send("\n")

            while True:
                r, _, _ = select.select([self.pktgen, sys.stdin], [], [])
                if self.pktgen in r:
                    try:
                        data = self.pktgen.recv(512)
                        if len(data) == 0:
                            break
                        sys.stdout.write(data)
                        sys.stdout.flush()
                    except socket.timeout:
                        pass
                if sys.stdin in r:
                    x = sys.stdin.read(1)
                    if len(x) == 0:
                        break
                    # Make sure we read arrow keys.
                    if x == "\x1b":
                        x += sys.stdin.read(2)
                    self.pktgen.send(x)

        finally:
            termios.tcsetattr(sys.stdin, termios.TCSADRAIN, oldtty)

    def __del__(self):
        self.cmd_.close()