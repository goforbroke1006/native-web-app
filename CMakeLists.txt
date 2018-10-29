cmake_minimum_required(VERSION 3.9.2)
project(native-web-app)

set(CMAKE_CXX_STANDARD 14)

add_executable(native-web-app main.cpp net.http.h)

target_link_libraries(native-web-app pthread)


add_subdirectory(tests)

