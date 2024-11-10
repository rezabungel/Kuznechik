import os
from dataclasses import fields
from typing import Type, TypeVar

import yaml


T = TypeVar('T')

def get_config_path(yaml_file: str) -> str:
    current_dir = os.path.dirname(__file__)
    config_path = os.path.join(current_dir, '..', '..', 'config', yaml_file)
    return os.path.abspath(config_path)

def get_lib_path(lib_file: str) -> str:
    current_dir = os.path.dirname(__file__)
    lib_path = os.path.join(current_dir, '..', '..', 'lib', lib_file)
    return os.path.abspath(lib_path)

def load_config_from_yaml(yaml_file: str, settings_class: Type[T]) -> T:
    yaml_file_path = get_config_path(yaml_file)
    with open(yaml_file_path, 'r', encoding='utf-8') as config:
        config_dict = yaml.safe_load(config)

    for field in fields(settings_class):
        if field.name not in config_dict and field.default is field.default_factory:
            raise ValueError(f"Missing required configuration key: '{field.name}'")

    return settings_class(**config_dict)