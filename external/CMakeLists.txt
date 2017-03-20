include(ExternalProject)

if(NOT DISABLE_json)
    find_package ( nlohmann_json QUIET )
    if (NOT nlohmann_json_FOUND)
        ExternalProject_Add(nlohmannjson
            GIT_REPOSITORY https://github.com/nlohmann/json
            GIT_TAG "master"
            UPDATE_COMMAND ""
            PATCH_COMMAND ""
            SOURCE_DIR "${CMAKE_SOURCE_DIR}/external/json"
            CMAKE_ARGS -DBuildTests=OFF  -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}
        )
        set(JSON_INCLUDE_DIR "${CMAKE_BINARY_DIR}/include" PARENT_SCOPE)
    endif ()
endif()

if(NOT DISABLE_ScreepsApi)
    find_package ( ScreepsApi QUIET )
    if (NOT ScreepsApi_FOUND)
        ExternalProject_Add(
            ScreepsApi
            GIT_REPOSITORY https://github.com/Lyon1-Asterix/ScreepsApi.git
            GIT_TAG "master"
            PATCH_COMMAND ""
            SOURCE_DIR "${CMAKE_SOURCE_DIR}/external/ScreepsApi"
            CMAKE_ARGS -DDISABLE_json=ON -JSON_INCLUDE_DIR=${JSON_INCLUDE_DIR} -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}
        )
        set(ScreepsApi_INCLUDE_DIRS "${CMAKE_BINARY_DIR}/include" PARENT_SCOPE)
        set(ScreepsApi_LIBRARY_DIR "${CMAKE_BINARY_DIR}/lib" PARENT_SCOPE)
        set(ScreepsApi_LIBRARIES "${CMAKE_SHARED_LIBRARY_PREFIX}ScreepsApi${CMAKE_SHARED_LIBRARY_SUFFIX}" PARENT_SCOPE)
    endif()
endif()
