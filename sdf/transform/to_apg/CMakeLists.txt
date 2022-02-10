set(sdf_transform_to_apg_sources
        apg.cc
        sdftoapg.cc
        )

set(sdf_transform_to_apg_headers
        apg.h
        sdftoapg.h
        )

add_library(sdf_transform_to_apg OBJECT ${sdf_transform_to_apg_sources} ${sdf_transform_to_apg_headers})
target_compile_definitions(sdf_transform_to_apg PUBLIC)