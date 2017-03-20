cmake_minimum_required(VERSION 3.0)
include(ConfigExternal)

project (ScreepsApiV12)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -ggdb")

set(GLOBAL_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(DISABLE_ScreepsApi "bla bla bla... ScreepsApi" OFF)
option(DISABLE_json "bla bla bla ... nlhomann/json" OFF)

add_subdirectory ( external )
include_directories(${Json_INCLUDE_DIRS})
include_directories(${ScreepsApi_INCLUDE_DIRS})

link_directories ( ${CMAKE_BINARY_DIR}/lib )

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

include_directories("${PROJECT_INCLUDE_DIR}")

add_library(${PROJECT_NAME} SHARED ${PROJECT_SRCS})
target_link_libraries ( ${PROJECT_NAME} ${ScreepsApi_LIBRARIES} )
if(NOT DISABLE_json)
add_dependencies(${PROJECT_NAME} nlohmannjson)
endif ()
if(NOT DISABLE_ScreepsApi)
add_dependencies(${PROJECT_NAME} ScreepsApi)
endif ()
