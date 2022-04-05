cmake_minimum_required(VERSION 3.21)
project(DCT C)


find_package(OpenCL REQUIRED)

add_executable(DCT main.c)

target_link_libraries(DCT OpenCL::OpenCL)
target_compile_options(DCT PRIVATE "-std=c11")
