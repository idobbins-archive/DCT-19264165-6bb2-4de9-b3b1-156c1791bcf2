


add_executable(test_software)

target_include_directories(test_software PRIVATE ../include)

target_sources(test_software PRIVATE software.test.c)
target_link_libraries(test_software PRIVATE DCT_IO)

add_test(NAME software COMMAND test_software)