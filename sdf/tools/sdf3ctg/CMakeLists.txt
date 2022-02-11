set(sdf_tools_sdf3ctg_sdf_sources
        sdf3ctg.cc
        )

set(sdf_tools_sdf3ctg_sdf_headers
        sdf3ctg.h
        )

add_executable(sdf3ctg-sdf ${sdf_tools_sdf3ctg_sdf_sources} ${sdf_tools_sdf3ctg_sdf_headers})
target_link_libraries(sdf3ctg-sdf sdf3-base)
