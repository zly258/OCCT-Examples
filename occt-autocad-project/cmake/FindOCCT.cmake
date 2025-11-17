# FindOCCT.cmake

find_package(OCCT REQUIRED)

if(NOT OCCT_FOUND)
    message(FATAL_ERROR "OCCT library not found. Please install OCCT and set the OCCT_DIR variable.")
endif()

include_directories(${OCCT_INCLUDE_DIRS})
link_directories(${OCCT_LIBRARY_DIRS})

set(OCCT_LIBRARIES
    ${OCCT_LIBRARIES}
)

message(STATUS "Found OCCT: ${OCCT_LIBRARIES}")