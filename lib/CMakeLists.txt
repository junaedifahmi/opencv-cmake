# minimum cmake version required
cmake_minimum_required(VERSION 3.5.1 FATAL_ERROR)

# project name
project(LIB)

add_subdirectory(body)
add_subdirectory(head)
add_subdirectory(test)