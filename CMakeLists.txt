cmake_minimum_required(VERSION 3.18)

project(socket_program)

include_directories(${PROJECT_SOURCE_DIR}/include)


set(SUBPROJECT ${PROJECT_SOURCE_DIR}/lecture04)
add_subdirectory(${SUBPROJECT})


add_library(lib_error STATIC ${PROJECT_SOURCE_DIR}/error/s_error.cpp)

add_executable(client ${SUBPROJECT}/src/client.cpp)
add_executable(server ${SUBPROJECT}/src/server.cpp)

target_link_libraries(client PRIVATE lib_error)
target_link_libraries(server PRIVATE lib_error)