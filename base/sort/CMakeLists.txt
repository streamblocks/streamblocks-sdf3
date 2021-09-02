set(base_sort_headers
        sort.h
        )

add_library(base_sort INTERFACE ${base_sort_headers})
target_include_directories(base_sort INTERFACE .)
target_compile_definitions(base_sort INTERFACE)