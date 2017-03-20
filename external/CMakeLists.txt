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
    set(${varprefix}_LOCAL 0 PARENT_SCOPE)
    if (NOT ${name}_FOUND)
        ExternalProject_Add(${name}
            GIT_REPOSITORY ${repository}
            GIT_TAG "master"
            SOURCE_DIR "${CMAKE_SOURCE_DIR}/external/${name}"
#            UPDATE_COMMAND ""
            CMAKE_ARGS ${args}  -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}
        )
        set(${varprefix}_INCLUDE_DIR "${CMAKE_BINARY_DIR}/include")
        set(${varprefix}_LIBRARY_DIR "${CMAKE_BINARY_DIR}/lib")
        set(${varprefix}_LIBRARIES "${CMAKE_SHARED_LIBRARY_PREFIX}${varprefix}${CMAKE_SHARED_LIBRARY_SUFFIX}")
        set(${varprefix}_LOCAL 1 PARENT_SCOPE)
    endif ()
    message ( STATUS "${varprefix} ${${varprefix}_INCLUDE_DIR}")
endmacro ()

FindOrCloneExternal ( nlohmann_json https://github.com/Lyon1-Asterix/json "-DBuildTests=OFF" JSON )
FindOrCloneExternal ( ScreepsApi https://github.com/Lyon1-Asterix/ScreepsApi.git "-Dnlohmann_json_DIR=${CMAKE_BINARY_DIR}/cmake" ScreepsApi )
