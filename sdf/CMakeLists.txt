include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(base)
add_subdirectory(analysis)

add_library(sdf3-sdf)
target_link_libraries(sdf3-sdf PUBLIC
        sdf_base_algo
        sdf_base_hsdf
        sdf_base_untimed
        sdf_base_timed

        sdf_analysis_buffersizing
        sdf_analysis_throughput
        sdf_analysis_dependency_graph
        sdf_analysis_latency
        sdf_analysis_maxplus
        sdf_analysis_mcm
        sdf_analysis_token_communication
        )