set(base_exception_sources
        exception.cc
        )

set(base_exception_headers
        exception.h
        )

add_library(base_exception OBJECT ${base_exception_sources} ${base_exception_headers})
target_compile_definitions(base_exception PUBLIC BASE_EXCEPTION)