cmake_minimum_required(VERSION 2.8)
project(test_str)
set(SRC_LIST src/test.c src/test_cmp.c src/test_cpy.c src/test_len.c src/test_cat.c)
add_executable(${PROJECT_NAME} ${SRC_LIST})
