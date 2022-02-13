set(base_math_headers
        cmath.h
        )

add_library(base_math INTERFACE)
target_include_directories(base_math INTERFACE .)
target_compile_definitions(base_math INTERFACE)