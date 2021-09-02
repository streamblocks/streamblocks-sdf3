set(base_lookup_headers
        clookup.h
        )

add_library(base_lookup INTERFACE ${base_lookup_headers})
target_include_directories(base_lookup INTERFACE .)
target_compile_definitions(base_lookup INTERFACE)