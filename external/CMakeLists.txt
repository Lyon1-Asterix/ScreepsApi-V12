include(ExternalProject)

if(NOT DISABLE_json)
include(ExternalProject)
  ExternalProject_Add(nlohmannjson
    GIT_REPOSITORY https://github.com/nlohmann/json
    GIT_TAG "master"
    BUILD_COMMAND ""
    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    INSTALL_COMMAND ""
    SOURCE_DIR "${CMAKE_SOURCE_DIR}/external/json"
    )
set(Json_INCLUDE_DIRS_EXT "${CMAKE_SOURCE_DIR}/external/json/src")
set(Json_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/external/json/src" PARENT_SCOPE)
endif()

if(NOT DISABLE_ScreepsApi)
ExternalProject_Add(
    ScreepsApi
    GIT_REPOSITORY https://github.com/Lyon1-Asterix/ScreepsApi.git
    GIT_TAG "master"
    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    SOURCE_DIR "${CMAKE_SOURCE_DIR}/external/ScreepsApi"
    CMAKE_ARGS -DDISABLE_json=ON -DJson_INCLUDE_DIRS=${Json_INCLUDE_DIRS_EXT} -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}
)
#
set(ScreepsApi_INCLUDE_DIRS_loc "${CMAKE_SOURCE_DIR}/external/ScreepsApi/include")
set(ScreepsApi_LIBRARY_DIR_loc "${CMAKE_BINARY_DIR}/lib")
set(ScreepsApi_LIBRARIES_loc "${CMAKE_SHARED_LIBRARY_PREFIX}ScreepsApi${CMAKE_SHARED_LIBRARY_SUFFIX}")
#
set(ScreepsApi_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/external/ScreepsApi/include" PARENT_SCOPE)
set(ScreepsApi_LIBRARY_DIR "${CMAKE_BINARY_DIR}/lib" PARENT_SCOPE)
set(ScreepsApi_LIBRARIES "${CMAKE_SHARED_LIBRARY_PREFIX}ScreepsApi${CMAKE_SHARED_LIBRARY_SUFFIX}" PARENT_SCOPE)
endif()
