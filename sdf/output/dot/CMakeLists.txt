set(sdf_output_dot_sources
        dot.cc
        )

set(sdf_output_dot_headers
        dot.h
        )

add_library(sdf_output_dot OBJECT ${sdf_output_dot_sources} ${sdf_output_dot_headers})
target_compile_definitions(sdf_output_dot PUBLIC)