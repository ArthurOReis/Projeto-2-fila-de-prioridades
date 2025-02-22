cmake_minimum_required(VERSION 3.27)
project(modelo C)

set(CMAKE_C_STANDARD 17)
include_directories(include)

add_executable(modelo main.c)
target_link_libraries(modelo ${CMAKE_SOURCE_DIR}/lib/libprg.a m)

