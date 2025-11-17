cmake_minimum_required(VERSION 3.14)

project(OCCT_AutoCAD_Project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify the OCCT library path (override via -DOCCT_DIR=... when invoking cmake)
set(OCCT_DIR "path/to/occt" CACHE PATH "Path to OCCT installation")

find_package(OCCT REQUIRED)
include_directories(${OCCT_INCLUDE_DIR})

# FetchContent for nlohmann/json so main target can use JSON serialization too
include(FetchContent)
FetchContent_Declare(
  nlohmann_json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.11.2
)
FetchContent_MakeAvailable(nlohmann_json)

# Add source files
file(GLOB_RECURSE SOURCES
    src/*.cpp
)

# Add include directories
include_directories(include)

# Create the executable
add_executable(occt_autocad ${SOURCES})

# Link OCCT libraries
target_link_libraries(occt_autocad PRIVATE ${OCCT_LIBRARIES} nlohmann_json::nlohmann_json)

# Set the output directory for the executable
set_target_properties(occt_autocad PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Add tests
enable_testing()
add_subdirectory(tests)