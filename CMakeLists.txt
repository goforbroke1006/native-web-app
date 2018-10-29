cmake_minimum_required(VERSION 3.12)
project(native-web-app)

set(CMAKE_CXX_STANDARD 14)

add_executable(native-web-app main.cpp net.http.h)

target_link_libraries(native-web-app pthread)