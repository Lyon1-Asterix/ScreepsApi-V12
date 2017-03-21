
get_filename_component(SELF_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
get_filename_component(ScreepsApiV12_INCLUDE_DIRS "${SELF_DIR}/../../include" ABSOLUTE)
get_filename_component(ScreepsApiV12_LIBRARY_DIRS "${SELF_DIR}/../lib" ABSOLUTE)
set(ScreepsApiV12_LIBRARIES "${CMAKE_SHARED_LIBRARY_PREFIX}ScreepsApiV12${CMAKE_SHARED_LIBRARY_SUFFIX}")
