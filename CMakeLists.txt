cmake_minimum_required(VERSION 2.6)
project(RISK)

set(CMAKE_CXX_FLAGS "-g")

include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(Risk ${CMAKE_SOURCE_DIR}/src/Game.cxx ${CMAKE_SOURCE_DIR}/src/Player.cxx ${CMAKE_SOURCE_DIR}/src/Country.cxx ${CMAKE_SOURCE_DIR}/src/Army.cxx)

add_executable(test main_test.cpp)

target_link_libraries(test Risk)
