
add_library(DCT_ACTIONS SHARED)

target_include_directories(DCT_ACTIONS INTERFACE .)
target_include_directories(DCT_ACTIONS PRIVATE ../include)

target_sources(DCT_ACTIONS
        PRIVATE
        compress.c
        expand.c
        transform.c
        quantize.c)

target_link_libraries(DCT_ACTIONS DCT_IO DCT_LINALG)

target_compile_options(DCT_ACTIONS PRIVATE "-march=native" "-O3")
