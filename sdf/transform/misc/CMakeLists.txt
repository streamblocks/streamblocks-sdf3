set(sdf_transform_misc_sources
        reverse_channels.cc
        )

set(sdf_transform_misc_headers
        reverse_channels.h
        )

add_library(sdf_transform_misc OBJECT ${sdf_transform_misc_sources} ${sdf_transform_misc_headers})
target_compile_definitions(sdf_transform_misc PUBLIC)