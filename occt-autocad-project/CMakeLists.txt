project(OCCT_AutoCAD_Project)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify the OCCT library path
set(OCCT_DIR "path/to/occt")

# Find OCCT package
find_package(OCCT REQUIRED)

include_directories(${OCCT_INCLUDE_DIR})

# Add source files
file(GLOB_RECURSE SOURCES
    src/*.cpp
)

# Add include directories
include_directories(include)

# Create the executable
add_executable(occt_autocad ${SOURCES})

# Link OCCT libraries
target_link_libraries(occt_autocad ${OCCT_LIBRARIES})

# Set the output directory for the executable
set_target_properties(occt_autocad PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Add tests
enable_testing()
add_subdirectory(tests)