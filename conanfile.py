import os

from conans import ConanFile, CMake


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
    url = "https://github.com/MinterTeam/cpp-minter-api"
    description = "Minter C++ REST API SDK: access web services like explorer, gate and liquidity provider (bip.dev)"
    topics = ("minter", "minter-network", "minter-blockchain", "blockchain", "explorer")
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = {
        "shared": False,
        "minter_tx:shared": False,
        "toolbox:shared": False,
        "libcurl:shared": False,
        "cpr:shared": False,
        "cpr:with_ssl": 'auto'
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
    )
    generators = "cmake"
    default_user = "minter"
    default_channel = "latest"

    requires = (
        'minter_tx/2.0.3@minter/latest',
        'toolbox/3.2.3@edwardstock/latest',
        'nlohmann_json/3.9.1',
        'fmt/7.1.3',
        'rxcpp/4.1.0',
        'cpr/1.6.2',
        'libcurl/7.69.1',
    )

    build_requires = (
        "gtest/1.10.0",
    )

    def source(self):
        if "CONAN_LOCAL" not in os.environ:
            self.run("rm -rf *")
            self.run("git clone --recursive https://github.com/MinterTeam/cpp-minter-api.git .")

    def configure(self):
        if self.settings.compiler == "Visual Studio":
            del self.settings.compiler.runtime

    def build(self):
        cmake = CMake(self)
        opts = {
            'CMAKE_BUILD_TYPE': self.settings.build_type,
            'ENABLE_SHARED': "Off",
        }

        if self.options.shared:
            opts['ENABLE_SHARED'] = "On"

        cmake.configure(defs=opts)
        cmake.build(target="minter_api")

    def package(self):
        self.copy("*", dst="include", src="include", keep_path=True)
        dir_types = ['bin', 'lib', 'Debug', 'Release', 'RelWithDebInfo', 'MinSizeRel']
        file_types = ['lib', 'dll', 'dll.a', 'a', 'so', 'exp', 'pdb', 'ilk', 'dylib']

        for dirname in dir_types:
            for ftype in file_types:
                self.copy("*." + ftype, src=dirname, dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["minter_api"]
        if self.settings.build_type == "Debug" and self.settings.compiler != "Visual Studio":
            self.cpp_info.cxxflags.append("-g")

    def test(self):
        cmake = CMake(self)
        cmake.configure([], {'ENABLE_TEST': 'On'})
        cmake.build([], None, "minter_api")
        self.run("bin/minter_api-test")
