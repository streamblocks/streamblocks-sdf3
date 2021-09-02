set(sdf_base_untimed_sources
        actor.cc
        channel.cc
        component.cc
        graph.cc
        port.cc
        )

set(sdf_base_untimed_headers
        actor.h
        channel.h
        component.h
        graph.h
        port.h
        )

add_library(sdf_base_untimed OBJECT ${sdf_base_untimed_sources} ${sdf_base_untimed_headers})
target_compile_definitions(sdf_base_untimed PUBLIC)