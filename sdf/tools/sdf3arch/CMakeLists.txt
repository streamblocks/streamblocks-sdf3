set(sdf_tools_sdf3arch_sdf_sources
        sdf3arch.cc
        )

set(sdf_tools_sdf3arch_sdf_headers
        sdf3arch.h
        )

add_executable(sdf3arch-sdf ${sdf_tools_sdf3arch_sdf_sources} ${sdf_tools_sdf3arch_sdf_headers})
target_link_libraries(sdf3arch-sdf sdf3-base)
