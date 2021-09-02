set(base_random_headers
        random.h
        )

add_library(base_random INTERFACE ${base_random_headers})
target_include_directories(base_random INTERFACE .)
target_compile_definitions(base_random INTERFACE)