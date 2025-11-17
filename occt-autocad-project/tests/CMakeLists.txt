cmake_minimum_required(VERSION 3.14)

project(occt_autocad_tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/../include)

# Collect test sources
set(TEST_SOURCES
        test_document.cpp
        test_db.cpp
)

# Fetch Catch2 if not available
include(FetchContent)
FetchContent_Declare(
    catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v2.13.10
)
FetchContent_MakeAvailable(catch2)

add_executable(TestOCCT ${TEST_SOURCES})
target_include_directories(TestOCCT PRIVATE ${catch2_SOURCE_DIR}/single_include)

enable_testing()
add_test(NAME TestOCCT COMMAND TestOCCT)