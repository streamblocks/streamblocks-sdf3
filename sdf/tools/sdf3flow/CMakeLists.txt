set(sdf_tools_sdf3flow_sdf_sources
        settings.cc
        sdf3flow.cc
        )

set(sdf_tools_sdf3flow_sdf_headers
        settings.cc
        sdf3flow.h
        )

add_executable(sdf3flow-sdf ${sdf_tools_sdf3flow_sdf_sources} ${sdf_tools_sdf3flow_sdf_headers})
target_link_libraries(sdf3flow-sdf sdf3-sdf sdf3-base)
