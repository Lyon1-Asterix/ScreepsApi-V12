cmake_minimum_required (VERSION 2.8.8)

project (Api-V12)

# JSON
include_directories(../external/json/src)

# ScreepsApi
include_directories(../ScreepsApi/include)

set (PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
 
set(PROJECT_SRCS 
    #
    ${PROJECT_SOURCE_DIR}/Routers/Api.cpp
    ${PROJECT_SOURCE_DIR}/Routers/Auth.cpp
    ${PROJECT_SOURCE_DIR}/Routers/Client.cpp
    ${PROJECT_SOURCE_DIR}/Routers/Game.cpp
    ${PROJECT_SOURCE_DIR}/Routers/Register.cpp
    ${PROJECT_SOURCE_DIR}/Routers/Socket.cpp
    ${PROJECT_SOURCE_DIR}/Routers/User.cpp
    ${PROJECT_SOURCE_DIR}/Api.cpp
    ${PROJECT_SOURCE_DIR}/V12.cpp
)

include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_INCLUDE_DIR}")

add_library(${PROJECT_NAME} SHARED ${PROJECT_SRCS})
target_link_libraries ( ${PROJECT_NAME} ScreepsApi )
