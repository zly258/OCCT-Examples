project(TestOCCT)

cmake_minimum_required(VERSION 3.10)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add the test source files
set(TEST_SOURCES
    test_document.cpp
)

# Create the test executable
add_executable(TestOCCT ${TEST_SOURCES})

# Link with the OCCT library
find_package(OCCT REQUIRED)
target_link_libraries(TestOCCT ${OCCT_LIBRARIES})

# Enable testing
enable_testing()

# Add tests
add_test(NAME TestDocument COMMAND TestOCCT)