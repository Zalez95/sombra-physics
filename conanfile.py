from conans import ConanFile, CMake

class SombraPhysicsConan(ConanFile):
	name = "SombraPhysics"
	version = "v1.0"
	license = "MIT"
	author = "Zalez95"
	settings = "os", "compiler", "build_type", "arch"
	options = {
		"shared" : [True, False],
		"fPIC" : [True, False],
		"test" : [True, False]
	}
	default_options = {"shared": False, "fPIC": True, "test": False}
	generators = "cmake"

	def requirements(self):
		self.requires("stdext/v1.0")
		self.requires("glm/0.9.9.8")
		if self.options.test:
			self.requires("gtest/1.10.0")

	def config_options(self):
		if self.settings.os == "Windows":
			del self.options.fPIC
		self.options["gtest"].shared = True

	def export_sources(self):
		self.copy("*")

	def build(self):
		cmake = CMake(self)
		cmake.definitions["SOMBRA_PHYSICS_BUILD_TESTS"] = self.options.test
		cmake.definitions["SOMBRA_PHYSICS_BUILD_DOC"] = False
		cmake.configure()
		cmake.build()

	def package(self):
		cmake = CMake(self)
		cmake.install()

	def package_info(self):
		self.cpp_info.includedirs = ["include"]
		self.cpp_info.libdirs = ["lib"]
		self.cpp_info.libs = [self.name]
