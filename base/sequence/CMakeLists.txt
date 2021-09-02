set(base_sequence_headers
        sequence.h
        )

add_library(base_sequence INTERFACE ${base_sequence_headers})
target_include_directories(base_sequence INTERFACE .)
target_compile_definitions(base_sequence INTERFACE)