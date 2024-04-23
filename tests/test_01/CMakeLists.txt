# Include common cmake file
include(../../common/cmake-common.cmake)

# Definition of the project
project(test_01)

# Add executable
add_executable(test_01  src/main.cpp ${COMMON_FILES})


