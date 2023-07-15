import paramiko
import os
import time

from .host import Host

from .commands.command import Command
from .commands.remote import RemoteCommand

class RemoteHost(Host):
    def __init__(
        self, host: str, nb_retries: int = 0, retry_interval: int = 1
    ) -> None:
        self.host = host
        self.nb_retries = nb_retries
        self.retry_interval = retry_interval

        self._ssh_client = None
    
    def run_command(self, *args, **kwargs) -> Command:
        return RemoteCommand(self.ssh_client, *args, **kwargs)
    
    @property
    def ssh_client(self):
        if self._ssh_client is not None:
            return self._ssh_client

        # adapted from https://gist.github.com/acdha/6064215
        nb_retries: 0
        retry_interval: 1

        client = paramiko.SSHClient()
        client._policy = paramiko.WarningPolicy()
        client.set_missing_host_key_policy(paramiko.AutoAddPolicy())

        ssh_config = paramiko.SSHConfig()
        user_config_file = os.path.expanduser("~/.ssh/config")
        if os.path.exists(user_config_file):
            with open(user_config_file) as f:
                ssh_config.parse(f)

        cfg = {"hostname": self.host}

        user_config = ssh_config.lookup(self.host)

        for k in ("hostname", "username", "port"):
            if k in user_config:
                cfg[k] = user_config[k]

        if "user" in user_config:
            cfg["username"] = user_config["user"]

        if "proxycommand" in user_config and user_config["proxycommand"]:
            cfg["sock"] = paramiko.ProxyCommand(user_config["proxycommand"])

        if "identityfile" in user_config:
            cfg["pkey"] = paramiko.RSAKey.from_private_key_file(
                user_config["identityfile"][0]
            )

        trial = 0
        while True:
            trial += 1
            try:
                client.connect(**cfg)
                break
            except KeyboardInterrupt as e:
                raise e
            except Exception as e:
                time.sleep(retry_interval)
                if trial > nb_retries:
                    raise e

        self._ssh_client = client
        return self._ssh_client

    @ssh_client.deleter
    def ssh_client(self):
        if self._ssh_client is not None:
            self._ssh_client.close()
            del self._ssh_client
        self._ssh_client = None

    def __del__(self):
        del self.ssh_client
