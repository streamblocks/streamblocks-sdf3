set(sdf_transform_hsdf_sources
        hsdf.cc
        unfold.cc
        )

set(sdf_transform_hsdf_headers
        hsdf.h
        unfold.h
        )

add_library(sdf_transform_hsdf OBJECT ${sdf_transform_hsdf_sources} ${sdf_transform_hsdf_headers})
target_compile_definitions(sdf_transform_hsdf PUBLIC)