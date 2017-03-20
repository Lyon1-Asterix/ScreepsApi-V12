cmake_minimum_required(VERSION 3.0)

project (ScreepsApiV12)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -ggdb")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# JSON
include_directories(external/json/src)

if (NOT DEFINED ${HasScreepsApi})
add_subdirectory ( external/ScreepsApi )
include_directories(external/ScreepsApi/include)
endif ( NOT DEFINED ${HasScreepsApi})

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
    ${PROJECT_SOURCE_DIR}/Data.cpp
    ${PROJECT_SOURCE_DIR}/Api.cpp
    ${PROJECT_SOURCE_DIR}/V12.cpp
)

include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_INCLUDE_DIR}")

add_library(${PROJECT_NAME} SHARED ${PROJECT_SRCS})
target_link_libraries ( ${PROJECT_NAME} ScreepsApi )
