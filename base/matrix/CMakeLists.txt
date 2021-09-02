set(base_matrix_sources
        matrix.cc
        )

set(base_matrix_headers
        matrix.h
        )

add_library(base_matrix OBJECT ${base_matrix_sources} ${base_matrix_headers})
target_compile_definitions(base_matrix PUBLIC BASE_MATRIX)