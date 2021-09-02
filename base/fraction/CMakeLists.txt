set(base_fraction_headers
        fraction.h
        )

add_library(base_fraction INTERFACE ${base_fraction_headers})
target_compile_definitions(base_fraction INTERFACE)