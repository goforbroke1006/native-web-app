cmake_minimum_required(VERSION 3.9)
project(native-web-app CXX)
set(CMAKE_CXX_STANDARD 11)

add_executable(native-web-app main.cpp)

target_link_libraries(native-web-app
        native-web-app-src
        pthread)

add_subdirectory(src)

include(cmake/googletest.cmake)
fetch_googletest(
        ${PROJECT_SOURCE_DIR}/cmake
        ${PROJECT_BINARY_DIR}/googletest
)
enable_testing()
add_subdirectory(test)
