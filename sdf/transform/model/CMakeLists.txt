set(sdf_transform_model_sources
        autoconc.cc
        buffer_capacity_constrained.cc
        buffersize.cc
        )

set(sdf_transform_model_headers
        autoconc.h
        buffersize.h
        )

add_library(sdf_transform_model OBJECT ${sdf_transform_model_sources} ${sdf_transform_model_headers})
target_compile_definitions(sdf_transform_model PUBLIC)