import os
from conans import ConanFile, CMake, tools


def get_version():
    with open(os.path.join(os.path.dirname(__file__), 'version'), 'r') as f:
        content = f.read()
        try:
            content = content.decode()
        except AttributeError:
            pass
        return content.strip()


class MinterApiConan(ConanFile):
    name = "minter_api"
    version = get_version()
    license = "MIT"
    author = "Eduard Maximovich edward.vstock@gmail.com"
    url = "https://github.com/MinterTeam/cpp-minter"
    description = "Minter C++ REST API SDK: access web services like explorer, gate and liquidity provider (bip.dev)"
    topics = ("minter", "minter-network", "minter-blockchain", "blockchain", "explorer")
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = {
        "shared": False,
        "boost:shared": False,
        "httb:shared": False,
    }
    exports = "version"
    exports_sources = (
        "modules/*",
        "include/*",
        "cfg/*",
        "tests/*",
        "src/*",
        "libs/*",
        "CMakeLists.txt",
        "conanfile.py",
        "conanfile.txt",
        "LICENSE",
        "README.md",
        "merge_libs.sh"
    )
    generators = "cmake"
    default_user = "minter"
    default_channel = "latest"

    requires = (
        'httb/1.0.0@edwardstock/latest',
        'minter_tx/0.5.1@minter/latest',
        'toolbox/3.1.0@edwardstock/latest',
        'boost/1.70.0@conan/stable',
        'nlohmann_json/3.7.3',
        'fmt/5.3.0@bincrafters/stable',
    )

    build_requires = (
        "gtest/1.8.1@bincrafters/stable",
    )

    def source(self):
        if "CONAN_LOCAL" not in os.environ:
            self.run("rm -rf *")
            self.run("git clone --recursive https://github.com/MinterTeam/cpp-minter-api.git .")

    def build(self):
        cmake = CMake(self)
        cmake.configure(defs={'CMAKE_BUILD_TYPE': self.options["build_type"]})
        cmake.build(target="minter_api")

    def package(self):
        self.copy("*", dst="include", src="include", keep_path=True)
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="lib", keep_path=False)
        self.copy("*.dll.a", dst="lib", keep_path=False)
        self.copy("*.exp", dst="lib", keep_path=False)
        self.copy("*.ilk", dst="lib", keep_path=False)
        self.copy("*.pdb", dst="lib", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.dylib", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = self.collect_libs(folder="lib")
