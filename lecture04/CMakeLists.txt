project(echo_socket)

add_executable(echo_client src/echo_client.cpp src/s_error.cpp)
add_executable(echo_server src/echo_server.cpp src/s_error.cpp)