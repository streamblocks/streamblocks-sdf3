set(sdf_tools_sdf3transform_sdf_sources
        sdf3transform.cc
        )

set(sdf_tools_sdf3transform_sdf_headers
        sdf3transform.h
        )

add_executable(sdf3transform-sdf ${sdf_tools_sdf3transform_sdf_sources} ${sdf_tools_sdf3transform_sdf_headers})
target_link_libraries(sdf3transform-sdf sdf3-sdf sdf3-base)
