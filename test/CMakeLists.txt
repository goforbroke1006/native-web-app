cmake_minimum_required(VERSION 3.9)
project(native-web-app-test CXX)
set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_BINARY_DIR build)

#enable_testing()
#add_executable(testprog ../src/net.http.h net.http-test.h main.cpp)
#add_test(NAME runtestprog
#        COMMAND ${CMAKE_COMMAND}
#        -DTEST_PROG=$<TARGET_FILE:testprog>
#        -DSOURCEDIR=${CMAKE_CURRENT_SOURCE_DIR}
#        -P ${CMAKE_CURRENT_SOURCE_DIR}/runtest.cmake)
#
#target_link_libraries(testprog gtest pthread)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(native-web-app-test net.http-test.h main.cpp)
SET_TARGET_PROPERTIES(native-web-app-test PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(native-web-app-test
        native-web-app-src
        ${GTEST_LIBRARIES}
        pthread
        )

#add_test(
#        NAME
#        unit
#        COMMAND
#        ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/native-web-app-test
#)
add_test(NAME unit COMMAND $<TARGET_FILE:native-web-app-test>)

#add_test(NAME native-web-app-test
#        COMMAND ${CMAKE_COMMAND}
#        -DTEST_PROG=$<TARGET_FILE:native-web-app-test>
#        -DSOURCEDIR=${CMAKE_CURRENT_SOURCE_DIR})