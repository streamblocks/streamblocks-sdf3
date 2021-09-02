set(base_string_sources
        cstring.cc
        )

set(base_string_headers
        cstring.h
        )

add_library(base_string OBJECT ${base_string_sources} ${base_string_headers})
target_compile_definitions(base_string PUBLIC BASE_STRING)