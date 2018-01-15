project(client)

add_executable(client
        main.cpp
        ip-client.cpp
        tcp-client.cpp
        udp-client.cpp
        ../socket/socket.cpp)