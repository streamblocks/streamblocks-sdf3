set(sdf_tools_sdf3analysis_sdf_sources
        sdf3analysis.cc
        )

set(sdf_tools_sdf3analysis_sdf_headers
        sdf3analysis.h
        )

add_executable(sdf3analysis-sdf ${sdf_tools_sdf3analysis_sdf_sources} ${sdf_tools_sdf3analysis_sdf_headers})
target_link_libraries(sdf3analysis-sdf sdf3-sdf sdf3-base)
