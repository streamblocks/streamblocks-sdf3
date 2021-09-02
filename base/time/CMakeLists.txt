set(base_time_sources
        time.cc
        )

set(base_time_headers
        time.h
        )

add_library(base_time OBJECT ${base_time_sources} ${base_time_headers})
target_compile_definitions(base_time PUBLIC)