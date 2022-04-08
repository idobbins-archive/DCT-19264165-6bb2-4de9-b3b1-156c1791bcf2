
add_executable(DCT)

target_sources(DCT PRIVATE main.c)
target_link_libraries(DCT DCT_IO DCT_LINALG DCT_ACTIONS)

target_compile_options(DCT PRIVATE "-std=c11")

set_target_properties(DCT PROPERTIES OUTPUT_NAME "dct")

target_compile_options(DCT PRIVATE "-march=native" "-O3")
