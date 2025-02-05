# Find the dependencies
find_package(GTest)

# Find the source files
file(GLOB_RECURSE TEST_SPHYS_SOURCES "*.cpp")

# Create the executable
add_executable(TestSPHYS ${TEST_SPHYS_SOURCES})

# Add the target properties
set_target_properties(TestSPHYS PROPERTIES
	CXX_STANDARD			17
	CXX_STANDARD_REQUIRED	ON
)
target_include_directories(TestSPHYS PRIVATE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
	$<INSTALL_INTERFACE:include>
)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
	target_compile_options(TestSPHYS PRIVATE "-Wall" "-Wextra" "-Wpedantic")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	target_compile_options(TestSPHYS PRIVATE "/W4" "-D_CRT_SECURE_NO_WARNINGS")
endif()

# Link the dependencies
target_link_libraries(TestSPHYS PRIVATE gtest::gtest SombraPhysics)

# Add the test
add_test(TestSPHYS TestSPHYS)

# Install the target
set_target_properties(TestSPHYS PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}"
)
install(TARGETS TestSPHYS DESTINATION ${CMAKE_INSTALL_BINDIR})
