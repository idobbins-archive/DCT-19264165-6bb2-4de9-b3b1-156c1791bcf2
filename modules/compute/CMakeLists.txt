
find_package(OpenCL REQUIRED)

add_library(DCT_COMPUTE SHARED)

target_include_directories(DCT_COMPUTE INTERFACE .)
target_include_directories(DCT_COMPUTE PRIVATE ../../include)

target_sources(DCT_COMPUTE
        PRIVATE
        opencl.c)

target_link_libraries(DCT_COMPUTE OpenCL::OpenCL)
