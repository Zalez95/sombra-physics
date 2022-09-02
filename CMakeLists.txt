cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
include(GNUInstallDirs)

###############################################################################
# 								SOMBRA_PHYSICS
###############################################################################
# Project name and version
project(SombraPhysics LANGUAGES CXX)
set(SOMBRA_PHYSICS_VERSION_MAJOR "1")
set(SOMBRA_PHYSICS_VERSION_MINOR "0")
set(SOMBRA_PHYSICS_VERSION "${SOMBRA_PHYSICS_VERSION_MAJOR}.${SOMBRA_PHYSICS_VERSION_MINOR}")

# Sombra Physics Options
option(SOMBRA_PHYSICS_BUILD_DOC "Generate the Sombra Physics documentation" ON)
option(SOMBRA_PHYSICS_BUILD_TESTS "Build the Sombra Physics test programs" ON)

# Find the dependencies
include("${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
conan_basic_setup(TARGETS)

find_package(Doxygen)

# Find the library source files
file(GLOB_RECURSE SOMBRA_PHYSICS_SOURCES "src/*.cpp")

# Create the library
add_library(SombraPhysics ${SOMBRA_PHYSICS_SOURCES})

# Add the target properties
target_include_directories(SombraPhysics
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
	PRIVATE "src"
)
set_target_properties(SombraPhysics PROPERTIES
	CXX_STANDARD			17
	CXX_STANDARD_REQUIRED	On
)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
	target_compile_options(SombraPhysics PRIVATE "-Wall" "-Wextra" "-Wpedantic")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	target_compile_options(SombraPhysics PRIVATE "/W4" "/bigobj" "-D_CRT_SECURE_NO_WARNINGS")
endif()

# Link the dependencies
target_link_libraries(SombraPhysics PUBLIC CONAN_PKG::stdext CONAN_PKG::glm)

# Install the target
install(TARGETS SombraPhysics EXPORT SombraPhysicsTargets)
install(EXPORT SombraPhysicsTargets
	FILE SombraPhysicsTargets.cmake
	NAMESPACE SombraPhysics::
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/SombraPhysics"
)
install(DIRECTORY "include/sphys" DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Create the documentation
if(SOMBRA_PHYSICS_BUILD_DOC AND DOXYGEN_FOUND)
	set(DOXYGEN_IN "${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in")
	set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/doc")

	configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
	add_custom_target(SombraPhysicsDoc ALL
		COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
		WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/doc"
		COMMENT "Generating API documentation with Doxygen"
	)
endif()

# Create the tests
if(SOMBRA_PHYSICS_BUILD_TESTS)
	add_subdirectory(test)
endif()
