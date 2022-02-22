find_package(LibXml2 REQUIRED)

if(WIN32)
    add_definitions(-D_ITERATION_DEBUG_LEVEL=0)
endif()

include_directories(${CMAKE_SOURCE_DIR} ${LIBXML2_INCLUDE_DIR})

add_subdirectory(exception)
add_subdirectory(string)
add_subdirectory(fraction)
add_subdirectory(fsm)
add_subdirectory(log)
add_subdirectory(lookup)
add_subdirectory(math)
add_subdirectory(matrix)
add_subdirectory(maxplus)
add_subdirectory(random)
add_subdirectory(sequence)
add_subdirectory(shell)
add_subdirectory(sort)
add_subdirectory(tempfile)
add_subdirectory(time)
add_subdirectory(xml)


add_library(sdf3-base STATIC)
target_link_libraries(sdf3-base PUBLIC
        base_exception
        base_fraction
        base_fsm
        base_log
        base_lookup
        base_math
        base_matrix
        base_maxplus
        base_random
        base_sequence
        base_shell
        base_sort
        base_string
        base_tempfile
        base_time
        base_xml
        )