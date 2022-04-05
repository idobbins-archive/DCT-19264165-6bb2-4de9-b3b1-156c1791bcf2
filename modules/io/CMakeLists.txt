
add_library(DCT_IO SHARED)

target_include_directories(DCT_IO INTERFACE .)
target_include_directories(DCT_IO PRIVATE ../../include)

target_sources(DCT_IO
        PRIVATE
        file.c)

#target_compile_options(DCT_IO PRIVATE "-march=native")
#target_compile_options(DCT_IO PRIVATE "-march=native" "-O3")
