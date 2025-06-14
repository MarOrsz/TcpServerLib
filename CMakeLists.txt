cmake_minimum_required(VERSION 3.10.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(TcpServerLib VERSION 0.1.0 LANGUAGES C CXX)

include_directories({CMAKE_SOURCE_DIR}/inc)

add_library(TcpServerLib src/TcpServer.cpp)

target_link_libraries(TcpServerLib PRIVATE Ws2_32)