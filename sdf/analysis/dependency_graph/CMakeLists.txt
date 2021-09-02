set(sdf_analysis_dependency_graph_sources
        dependency_graph.cc
        )

set(sdf_analysis_dependency_graph_headers
        dependency_graph.h
        )

add_library(sdf_analysis_dependency_graph OBJECT ${sdf_analysis_dependency_graph_sources} ${sdf_analysis_dependency_graph_headers})
target_compile_definitions(sdf_analysis_dependency_graph PUBLIC)