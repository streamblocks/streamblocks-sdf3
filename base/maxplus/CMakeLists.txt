set(base_maxplus_sources
        mpmatrix.cc
        )

set(base_maxplus_headers
        mptype.h
        mpmatrix.h
        mptype.h
        )

add_library(base_maxplus OBJECT ${base_maxplus_sources} ${base_maxplus_headers})
target_compile_definitions(base_maxplus PUBLIC)