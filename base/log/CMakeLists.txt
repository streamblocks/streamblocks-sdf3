set(base_log_sources
        log.cc
        )

set(base_log_headers
        log.h
        )

add_library(base_log OBJECT ${base_log_sources} ${base_log_headers})
target_compile_definitions(base_log PUBLIC BASE_LOG)