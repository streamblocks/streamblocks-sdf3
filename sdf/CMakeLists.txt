find_package(LibXml2 REQUIRED)

include_directories(${CMAKE_SOURCE_DIR} ${LIBXML2_INCLUDE_DIR})

add_subdirectory(base)
add_subdirectory(analysis)
add_subdirectory(generate)
add_subdirectory(transform)
add_subdirectory(resource_allocation)
add_subdirectory(tools)
add_subdirectory(output)

add_library(sdf3-sdf STATIC)
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

        sdf_generate

        sdf_transform_hsdf
        sdf_transform_misc
        sdf_transform_model
        sdf_transform_to_apg

        sdf_resource_allocation_binding_aware_sdfg
        sdf_resource_allocation_flow
        sdf_resource_allocation_mpsoc_arch
        sdf_resource_allocation_noc_allocation_mapping
        sdf_resource_allocation_noc_allocation_problem
        sdf_resource_allocation_noc_allocation_scheduler
        sdf_resource_allocation_scheduling
        sdf_resource_allocation_tile_allocation

        sdf_output_buffer_throughput
        sdf_output_dot
        sdf_output_hapi
        sdf_output_html
        sdf_output_schedule
        sdf_output_xml
        )

set_target_properties(sdf3-sdf PROPERTIES
        FRAMEWORK TRUE)