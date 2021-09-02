set(sdf_base_algo_sources
        acyclic.cc
        components.cc
        connected.cc
        cycle.cc
        dfs.cc
        graph.cc
        repetition_vector.cc
        )

set(sdf_base_algo_headers
        acyclic.h
        components.h
        connected.h
        cycle.h
        dfs.h
        graph.h
        repetition_vector.h
        )

add_library(sdf_base_algo OBJECT ${sdf_base_algo_sources} ${sdf_base_algo_headers})
target_compile_definitions(sdf_base_algo PUBLIC)