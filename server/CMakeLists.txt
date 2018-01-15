project(server)

add_executable(server
        main.cpp
        ip-server.cpp
        udp-server.cpp
        tcp-server.cpp
        ../socket/socket.cpp)