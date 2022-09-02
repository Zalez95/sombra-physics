# Find the tests source files
file(GLOB_RECURSE SOMBRA_PHYSICS_TEST_SOURCES "./*.cpp")

# Create the executable
add_executable(SombraPhysicsTest ${SOMBRA_PHYSICS_TEST_SOURCES})

# Add the include directories
target_include_directories(SombraPhysicsTest PRIVATE "test")

# Add the compiler options
set_target_properties(SombraPhysicsTest PROPERTIES
	CXX_STANDARD			17
	CXX_STANDARD_REQUIRED	On
)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
	target_compile_options(SombraPhysicsTest PRIVATE "-Wall" "-Wextra" "-Werror")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	target_compile_options(SombraPhysicsTest PRIVATE "/W4" "-D_CRT_SECURE_NO_WARNINGS")
endif()

# Link the dependencies
target_link_libraries(SombraPhysicsTest PRIVATE SombraPhysics CONAN_PKG::gtest)

# Add the test
add_test(SombraPhysicsTest SombraPhysicsTest)

# Install the target
install(TARGETS SombraPhysicsTest DESTINATION ${CMAKE_INSTALL_BINDIR})
