add_library(native-web-app-src)
SET_TARGET_PROPERTIES(native-web-app-src PROPERTIES LINKER_LANGUAGE CXX)
target_sources(
        native-web-app-src
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/net/http/common.cpp
        ${CMAKE_CURRENT_LIST_DIR}/net/http/common.h
        ${CMAKE_CURRENT_LIST_DIR}/net/mux/common.cpp
        ${CMAKE_CURRENT_LIST_DIR}/net/mux/common.h
        ${CMAKE_CURRENT_LIST_DIR}/net/http/Request.cpp
        ${CMAKE_CURRENT_LIST_DIR}/net/http/Request.h
        ${CMAKE_CURRENT_LIST_DIR}/net/http/HttpServerException.h
        ${CMAKE_CURRENT_LIST_DIR}/net/http/HttpHeader.cpp
        ${CMAKE_CURRENT_LIST_DIR}/net/http/HttpHeader.h
        ${CMAKE_CURRENT_LIST_DIR}/net/http/ResponseWriter.cpp
        ${CMAKE_CURRENT_LIST_DIR}/net/http/ResponseWriter.h
        ${CMAKE_CURRENT_LIST_DIR}/net/http/Router.cpp
        ${CMAKE_CURRENT_LIST_DIR}/net/http/Router.h
        ${CMAKE_CURRENT_LIST_DIR}/net/http/Server.cpp
        ${CMAKE_CURRENT_LIST_DIR}/net/http/Server.h
)

target_include_directories(
        native-web-app-src
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)