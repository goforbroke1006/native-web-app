add_library(native-web-app-src)
SET_TARGET_PROPERTIES(native-web-app-src PROPERTIES LINKER_LANGUAGE CXX)
target_sources(
        native-web-app-src
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/net.http.h
        ${CMAKE_CURRENT_LIST_DIR}/Request.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Request.h
        ${CMAKE_CURRENT_LIST_DIR}/HttpServerException.h
        ${CMAKE_CURRENT_LIST_DIR}/HttpHeader.cpp
        ${CMAKE_CURRENT_LIST_DIR}/HttpHeader.h
        ${CMAKE_CURRENT_LIST_DIR}/ResponseWriter.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ResponseWriter.h
        ${CMAKE_CURRENT_LIST_DIR}/Router.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Router.h
        ${CMAKE_CURRENT_LIST_DIR}/Server.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Server.h
)

target_include_directories(
        native-web-app-src
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)