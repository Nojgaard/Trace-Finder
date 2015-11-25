cmake_minimum_required(VERSION 2.8)
project(trace-finder)

find_package(Boost COMPONENTS system filesystem program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})
add_definitions(-std=c++11)
add_definitions(-lboost_program_options -lboost_filesystem -lboost_system)

add_subdirectory(src)

add_executable(trace-finder src/main.cpp)

target_link_libraries(trace-finder ${Boost_LIBRARIES})
target_link_libraries(trace-finder graph_io graph_parse)

