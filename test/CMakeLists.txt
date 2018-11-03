cmake_minimum_required(VERSION 3.9)
project(native-web-app-test CXX)
set(CMAKE_CXX_STANDARD 14)

add_executable(native-web-app-test
        ../src/Request.h
        net.http-test.h
        main.cpp)
SET_TARGET_PROPERTIES(native-web-app-test PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(native-web-app-test
        native-web-app-src
        gtest_main
        pthread
        )

add_test(NAME unit COMMAND $<TARGET_FILE:native-web-app-test>)

#add_test(NAME native-web-app-test
#        COMMAND ${CMAKE_COMMAND}
#        -DTEST_PROG=$<TARGET_FILE:native-web-app-test>
#        -DSOURCEDIR=${CMAKE_CURRENT_SOURCE_DIR})
