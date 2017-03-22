cmake_minimum_required(VERSION 3.0)

project (ScreepsApiV12)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -ggdb")

set(GLOBAL_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(DISABLE_ScreepsApi "bla bla bla... ScreepsApi" OFF)
option(DISABLE_json "bla bla bla ... nlhomann/json" OFF)

find_package ( nlohmann_json REQUIRED
        NO_CMAKE_PACKAGE_REGISTRY
        NO_CMAKE_SYSTEM_PACKAGE_REGISTRY
)
include_directories(${JSON_INCLUDE_DIR})

find_package ( ScreepsApi REQUIRED
        NO_CMAKE_PACKAGE_REGISTRY
        NO_CMAKE_SYSTEM_PACKAGE_REGISTRY
)
include_directories(${ScreepsApi_INCLUDE_DIRS})

link_directories ( ${CMAKE_BINARY_DIR}/lib )
link_directories ( ${ScreepsApi_LIBRARY_DIRS} )

message ( STATUS "${ScreepsApi_LIBRARY_DIRS}")

set (PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
 
file(
        GLOB_RECURSE
        PROJECT_SRCS
        ${PROJECT_SOURCE_DIR}/*
)

file(
        GLOB_RECURSE
        PROJECT_PUBLIC_HEADERS
        ${PROJECT_INCLUDE_DIR}/*
)

include_directories("${PROJECT_INCLUDE_DIR}")

add_library(${PROJECT_NAME} SHARED ${PROJECT_SRCS})
target_link_libraries ( ${PROJECT_NAME} ${ScreepsApi_LIBRARIES} )

#INSTALL(TARGETS ${PROJECT_NAME}
#  RUNTIME DESTINATION bin
#  LIBRARY DESTINATION lib
#  ARCHIVE DESTINATION lib
#)

install(FILES ${PROJECT_PUBLIC_HEADERS} DESTINATION include/${PROJECT_NAME})
install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES cmake/${PROJECT_NAME}Config.cmake DESTINATION cmake)