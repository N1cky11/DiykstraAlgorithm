cmake_minimum_required(VERSION 3.10)
project(Dijkstra)

set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(Dijkstra DijkstraMain.cpp Dijkstra.cpp )

find_package(GTest REQUIRED)

if(GTest_FOUND)
    target_link_libraries(Dijkstra GTest::GTest)
else()
     message(WARNING "Google test not found")
endif()
