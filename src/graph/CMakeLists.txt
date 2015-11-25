add_subdirectory(parse)

add_library(graph_io io.cpp)
#add_definitions(-lboost_system -lboost_filesystem)
#target_link_libraries(trace-finder graph_io)
target_link_libraries(graph_io ${Boost_LIBRARIES})
