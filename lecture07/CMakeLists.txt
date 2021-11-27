project(shutdown)

add_executable(client src/client.cpp src/s_error.cpp)
add_executable(server src/server.cpp src/s_error.cpp)