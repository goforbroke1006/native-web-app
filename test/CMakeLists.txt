project(native-web-app-tests)

set(CMAKE_CXX_STANDARD 11)
find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS})
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(native-web-app-tests net.http.test.h)
target_link_libraries(native-web-app-tests gtest gtest_main)

add_test(native-web-app-tests native-web-app-tests)

