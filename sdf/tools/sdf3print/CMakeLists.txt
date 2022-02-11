set(sdf_tools_sdf3print_sdf_sources
        sdf3print.cc
        )

set(sdf_tools_sdf3print_sdf_headers
        sdf3print.h
        )

add_executable(sdf3print-sdf ${sdf_tools_sdf3print_sdf_sources} ${sdf_tools_sdf3print_sdf_headers})
target_link_libraries(sdf3print-sdf sdf3-sdf sdf3-base)
