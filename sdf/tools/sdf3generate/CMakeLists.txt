set(sdf_tools_sdf3generate_sdf_sources
        sdf3generate.cc
        )

set(sdf_tools_sdf3generate_sdf_headers
        sdf3generate.h
        )

add_executable(sdf3generate-sdf ${sdf_tools_sdf3generate_sdf_sources} ${sdf_tools_sdf3generate_sdf_headers})
target_link_libraries(sdf3generate-sdf sdf3-sdf sdf3-base)
