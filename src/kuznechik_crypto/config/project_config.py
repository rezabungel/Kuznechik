from dataclasses import dataclass

from config.utils import load_config_from_yaml


@dataclass
class Settings:
    title: str
    version: str
    host: str
    port: int
    auto_reload: bool

settings = load_config_from_yaml('kuznechik_crypto', 'config.yaml', Settings)