# SPDX-License-Identifier: Apache-2.0
cmake_minimum_required(VERSION 3.22)
project(shark VERSION 0.1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# options

option(AS "Build the Assembler" ON)
option(DIS "Build the Disassembler" ON)
set(PAGE_SIZE 4096 CACHE STRING "Default page size")

include(CheckIncludeFile)
check_include_file("sys/mman.h" HAVE_SYS_MMAN_H)
check_include_file("sys/stat.h" HAVE_SYS_STAT_H)
check_include_file("unistd.h" HAVE_UNISTD_H)
check_include_file("fcntl.h" HAVE_FCNTL_H)
check_include_file("libgen.h" HAVE_LIBGEN_H)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/common/config.h.in
    ${CMAKE_CURRENT_SOURCE_DIR}/common/include/config.h
    @ONLY
)

# common

file(GLOB COMMON_SOURCES common/src/*.c)

add_library(common STATIC ${COMMON_SOURCES})
target_include_directories(common PUBLIC common/include/)


if (${AS})
    add_subdirectory(as)
endif()

if (${DIS})
    add_subdirectory(dis)
endif()