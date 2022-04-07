cmake_minimum_required(VERSION 3.21)
project(DCT C)


add_subdirectory(modules/compute)
add_subdirectory(modules/io)


add_executable(DCT runtime/main.c)

target_link_libraries(DCT DCT_COMPUTE DCT_IO)

target_compile_options(DCT PRIVATE "-std=c11")

enable_testing()
add_subdirectory(tests)