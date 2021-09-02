set(sdf_base_timed_sources
        actor.cc
        channel.cc
        graph.cc
        )

set(sdf_base_timed_headers
        actor.h
        channel.h
        graph.h
        timed_types.h
        )

add_library(sdf_base_timed OBJECT ${sdf_base_timed_sources} ${sdf_base_timed_headers})
target_compile_definitions(sdf_base_timed PUBLIC)