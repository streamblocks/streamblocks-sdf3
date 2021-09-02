set(base_tempfile_sources
        tempfile.cc
        )

set(base_tempfile_headers
        tempfile.h
        )

add_library(base_tempfile OBJECT ${base_tempfile_sources} ${base_tempfile_headers})
target_compile_definitions(base_tempfile PUBLIC)