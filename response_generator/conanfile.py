import os

from conans import ConanFile


def get_version():
    with open(os.path.join(os.path.dirname(__file__), 'version'), 'r') as f:
        content = f.read()
        try:
            content = content.decode()
        except AttributeError:
            pass
        return content.strip()


class MinterApiConan(ConanFile):
    name = "resp_gen"
    version = "0.1.0"
    license = "MIT"
    author = "Eduard Maximovich edward.vstock@gmail.com"
    url = "https://github.com/MinterTeam/cpp-minter-api"
    settings = "os", "compiler", "build_type", "arch"
    default_options = {
        "boost:shared": False,
        "httb:shared": False,
        "minter_tx:shared": False,
    }
    generators = "cmake"
    default_user = "minter"
    default_channel = "latest"

    requires = (
        'toolbox/3.2.3@edwardstock/latest',
        'nlohmann_json/3.9.1',
        'boost/1.76.0',
        'fmt/7.1.3',
    )

    build_requires = ()
