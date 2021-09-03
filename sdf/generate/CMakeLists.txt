set(sdf_generate_sources
        generate.cc
        )

set(sdf_generate_headers
        generate.h
        )

add_library(sdf_generate OBJECT ${sdf_generate_sources} ${sdf_generate_headers})
target_compile_definitions(sdf_generate PUBLIC)