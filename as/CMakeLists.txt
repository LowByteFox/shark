# SPDX-License-Identifier: Apache-2.0

file(GLOB AS_SOURCES src/*.c)
add_executable(${PROJECT_NAME}-as ${AS_SOURCES})
target_include_directories(${PROJECT_NAME}-as PRIVATE include)
target_link_libraries(${PROJECT_NAME}-as common)