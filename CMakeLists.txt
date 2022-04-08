cmake_minimum_required(VERSION 3.21)
project(DCT C)


add_subdirectory(actions)
add_subdirectory(modules/compute)
add_subdirectory(modules/io)
add_subdirectory(modules/linalg)
add_subdirectory(runtime)



enable_testing()
add_subdirectory(tests)