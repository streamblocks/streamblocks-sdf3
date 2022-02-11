set(sdf_tools_sdf3cost_sdf_sources
        sdf3cost.cc
        )

set(sdf_tools_sdf3cost_sdf_headers
        sdf3cost.h
        )

add_executable(sdf3cost-sdf ${sdf_tools_sdf3cost_sdf_sources} ${sdf_tools_sdf3cost_sdf_headers})
target_link_libraries(sdf3cost-sdf sdf3-sdf sdf3-base)
