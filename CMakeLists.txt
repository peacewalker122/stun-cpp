cmake_minimum_required(VERSION 3.10)
project(StunServer)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

# Source files for the main application
set(SOURCES
  src/stunHeader.cpp
  src/stunService.cpp
  src/main.cpp
)

# Define the main executable
add_executable(stun-server ${SOURCES})

# Enable testing but don't add tests by default
option(BUILD_TESTS "Build the tests" OFF)

if(BUILD_TESTS)
    # Source files for the tests
    set(TEST_SOURCES
      tests/stunHeader.cpp
      src/stunService.cpp
      src/stunHeader.cpp
    )

    # Add the test executable
    add_executable(tests ${TEST_SOURCES})
    
    # Enable testing
    enable_testing()

    # Add test
    add_test(NAME coba COMMAND tests)
endif()

