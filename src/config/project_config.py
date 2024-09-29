from dataclasses import dataclass

from config.utils import load_config_from_yaml


@dataclass
class Settings:
    title: str
    version: str

settings = load_config_from_yaml('config.yaml', Settings)