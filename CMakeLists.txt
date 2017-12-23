# minimum cmake version required
cmake_minimum_required(VERSION 3.5.1 FATAL_ERROR)

# project name
project(PST)

find_package(OpenCV REQUIRED)

add_subdirectory(cmake)
add_subdirectory(doc)
add_subdirectory(lib)
add_subdirectory(resource)
add_subdirectory(src)
add_subdirectory(temp)

# direct binary outputs
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# enable c++ language
enable_language(CXX)

# project version
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)

# location of additional cmake modules
set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake
)

# guard against in-source builds and bad build-type strings
include(safeguards)

# detect operating system
message(STATUS "${CMAKE_SYSTEM_NAME} ${CMAKE_HOST_SYSTEM_PROCESSOR}")
if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    add_definitions(-DSYSTEM_LINUX)
endif()
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    add_definitions(-DSYSTEM_WINDOWS)
endif()

# create libraries
file(GLOB CONFIG *.h)
file(GLOB LIB_HEADER lib/head/*.hpp)
file(GLOB LIB_SOURCE lib/body/*.cpp)
add_library(LIB ${CONFIG} ${LIB_SOURCE} ${LIB_HEADER})
target_link_libraries(LIB ${OpenCV_LIBS})

# create executables to libraries test
FILE(GLOB_RECURSE LIB_TEST RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/lib/test/*.cpp)
foreach( source_file ${LIB_TEST} )    
    string( REPLACE ".cpp" "" file_name ${source_file} )       
    string( REPLACE "lib/test/" "" file_name ${file_name} )           
    add_executable( ${file_name} ${source_file} )    
    target_link_libraries( ${file_name} LIB )
endforeach( source_file ${LIB_TEST} )

# set c++ compiler flags for GNU
if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wunused-but-set-variable -Wunused-variable -Wall -Wextra -Wshadow -Wstrict-aliasing -pedantic -fmax-errors=5 -Werror -Wunreachable-code -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Wno-unused -Wno-variadic-macros -Wno-parentheses -fdiagnostics-show-option -lopencv_core -lopencv_highgui -lopencv_video -lopencv_nonfree -lopencv_objdetect -lopencv_features2d -lopencv_imgproc -lopencv_highgui -lopencv_core")
endif()

# location of header files
include_directories(    
    ${PROJECT_SOURCE_DIR}    
)

# get git hash
include(git_revision)

# configure header file
configure_file(
    ${PROJECT_SOURCE_DIR}/cmake/config.h.in
    ${PROJECT_BINARY_DIR}/config.h
)