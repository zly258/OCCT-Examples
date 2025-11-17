cmake_minimum_required(VERSION 3.14)

project(occt_autocad_tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/../include)

# Collect test sources
file(GLOB TEST_SOURCES LIST_DIRECTORIES OFF "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# Fetch Catch2 if not available
include(FetchContent)
FetchContent_Declare(
    catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v2.13.10
)
FetchContent_MakeAvailable(catch2)

# Fetch nlohmann/json for serialization
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.2
)
FetchContent_MakeAvailable(nlohmann_json)

add_executable(TestOCCT ${TEST_SOURCES})
target_include_directories(TestOCCT PRIVATE ${catch2_SOURCE_DIR}/single_include)
target_link_libraries(TestOCCT PRIVATE nlohmann_json::nlohmann_json)

enable_testing()
add_test(NAME TestOCCT COMMAND TestOCCT)