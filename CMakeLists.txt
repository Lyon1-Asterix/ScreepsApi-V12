cmake_minimum_required(VERSION 3.0)

project (ScreepsApiV12)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -ggdb")

set(GLOBAL_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(DISABLE_ScreepsApi "bla bla bla... ScreepsApi" OFF)
option(DISABLE_json "bla bla bla ... nlhomann/json" OFF)

include(ExternalProject)

macro ( FindOrCloneExternal name repository args varprefix )
    find_package ( ${name} QUIET
        NO_DEFAULT_PATH
        NO_CMAKE_ENVIRONMENT_PATH
        NO_CMAKE_PATH
        NO_SYSTEM_ENVIRONMENT_PATH
        NO_CMAKE_PACKAGE_REGISTRY
        NO_CMAKE_BUILDS_PATH
        NO_CMAKE_SYSTEM_PATH
        NO_CMAKE_SYSTEM_PACKAGE_REGISTRY
    )
    message ( STATUS "args = ${args}")
    if (NOT ${name}_FOUND)
        ExternalProject_Add(${name}
            GIT_REPOSITORY ${repository}
            GIT_TAG "master"
            SOURCE_DIR "${CMAKE_SOURCE_DIR}/external/${name}"
            UPDATE_COMMAND ""
            CMAKE_ARGS ${args}  -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}
        )
        set(${varprefix}_INCLUDE_DIR "${CMAKE_BINARY_DIR}/include")
        set(${varprefix}_LIBRARY_DIR "${CMAKE_BINARY_DIR}/lib")
        set(${varprefix}_LIBRARIES "${CMAKE_SHARED_LIBRARY_PREFIX}${varprefix}${CMAKE_SHARED_LIBRARY_SUFFIX}")
    endif ()
    message ( STATUS "${varprefix} ${${varprefix}_INCLUDE_DIR}")
endmacro ()

FindOrCloneExternal ( nlohmann_json https://github.com/Lyon1-Asterix/json "-DBuildTests=OFF" JSON )
FindOrCloneExternal ( ScreepsApi https://github.com/Lyon1-Asterix/ScreepsApi.git "-Dnlohmann_json_DIR=${CMAKE_BINARY_DIR}/cmake" ScreepsApi )
include_directories(${JSON_INCLUDE_DIR})
include_directories(${ScreepsApi_INCLUDE_DIR})

link_directories ( ${CMAKE_BINARY_DIR}/lib )
link_directories ( ${ScreepsApi_LIBRARY_DIR} )

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
if(TARGET nlohmann_json)
add_dependencies(${PROJECT_NAME} nlohmann_json)
endif ()
if(TARGET ScreepsApi)
add_dependencies(${PROJECT_NAME} ScreepsApi)
endif ()

#INSTALL(TARGETS ${PROJECT_NAME}
#  RUNTIME DESTINATION bin
#  LIBRARY DESTINATION lib
#  ARCHIVE DESTINATION lib
#)

install(FILES ${PROJECT_PUBLIC_HEADERS} DESTINATION include/${PROJECT_NAME})
install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES cmake/${PROJECT_NAME}-Config.cmake DESTINATION cmake)