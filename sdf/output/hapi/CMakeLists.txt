set(sdf_output_hapi_sources
        hapi.cc
        )

set(sdf_output_hapi_headers
        hapi.h
        )

add_library(sdf_output_hapi OBJECT ${sdf_output_hapi_sources} ${sdf_output_hapi_headers})
target_compile_definitions(sdf_output_hapi PUBLIC)