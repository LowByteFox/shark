# SPDX-License-Identifier: Apache-2.0

file(GLOB AS_SOURCES src/*.c)
list(FILTER AS_SOURCES EXCLUDE REGEX ".*src/main\.c$")

add_executable(${PROJECT_NAME}-as ${AS_SOURCES} src/main.c)
target_include_directories(${PROJECT_NAME}-as PRIVATE include)
target_link_libraries(${PROJECT_NAME}-as common)

if (${BUILD_TESTING})
    add_executable(as-lexer-test test/lexer.cpp ${AS_SOURCES})
    target_include_directories(as-lexer-test PRIVATE include)
    target_link_libraries(as-lexer-test PRIVATE GTest::gtest_main common)

    include(GoogleTest)
    gtest_discover_tests(as-lexer-test)
endif()