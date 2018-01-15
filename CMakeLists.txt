CMAKE_MINIMUM_REQUIRED(VERSION 3.7)

project(client-server)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread")

add_subdirectory(client)
add_subdirectory(server)
