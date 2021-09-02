set(sdf_base_hsdf_sources
       check.cc
        )

set(sdf_base_hsdf_headers
        check.h
        )

add_library(sdf_base_hsdf OBJECT ${sdf_base_hsdf_sources} ${sdf_base_hsdf_headers})
target_compile_definitions(sdf_base_hsdf PUBLIC)