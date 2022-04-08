
add_library(DCT_LINALG SHARED)

target_include_directories(DCT_LINALG INTERFACE .)
target_include_directories(DCT_LINALG PRIVATE ../../include)

target_sources(DCT_LINALG
        PRIVATE
        linalg.c)

#target_compile_options(DCT_LINALG PRIVATE "-march=native" "-O3")
