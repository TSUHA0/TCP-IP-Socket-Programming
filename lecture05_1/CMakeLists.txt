project(echo_socket)

add_executable(uecho_client src/client.cpp src/s_error.cpp)
add_executable(uecho_server src/server.cpp src/s_error.cpp)