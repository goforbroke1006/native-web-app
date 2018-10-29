add_library(native-web-app-src "")
SET_TARGET_PROPERTIES(native-web-app-src PROPERTIES LINKER_LANGUAGE CXX)
target_sources(
        native-web-app-src
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/net.http.h
)

target_include_directories(
        native-web-app-src
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)