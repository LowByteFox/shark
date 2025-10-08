# SPDX-License-Identifier: Apache-2.0

file(GLOB AS_SOURCES src/*.c)
add_executable(${PROJECT_NAME}-dis ${AS_SOURCES})
target_include_directories(${PROJECT_NAME}-dis PRIVATE include)
target_link_libraries(${PROJECT_NAME}-dis common)