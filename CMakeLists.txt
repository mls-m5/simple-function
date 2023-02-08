
cmake_minimum_required(VERSION 3.23)
project(simple-function)

add_executable(
    simple-function
    src/main.cpp
    )

target_compile_features(
    simple-function
    PRIVATE
    cxx_std_17
    )

target_include_directories(
    simple-function
    PUBLIC
    include
    )

find_package(Threads)
target_link_libraries(
    simple-function
    PRIVATE
    ${CMAKE_THREAD_LIBS_INIT}
    )
