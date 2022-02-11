set(sdf_tools_sdf3gast_sdf_sources
        sdf3gast.cc
        )

set(sdf_tools_sdf3gast_sdf_headers
        sdf3gast.h
        )

add_executable(sdf3gast-sdf ${sdf_tools_sdf3gast_sdf_sources} ${sdf_tools_sdf3gast_sdf_headers})
target_link_libraries(sdf3gast-sdf sdf3-sdf sdf3-base)
