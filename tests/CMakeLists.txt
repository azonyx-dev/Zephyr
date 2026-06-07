cmake_minimum_required(VERSION 3.21)

add_executable(test_ByteReader test_ByteReader.cpp)

target_link_libraries(test_ByteReader PRIVATE Zephyr)

target_include_directories(test_ByteReader PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

enable_testing()
add_test(NAME ByteReader COMMAND test_ByteReader)
