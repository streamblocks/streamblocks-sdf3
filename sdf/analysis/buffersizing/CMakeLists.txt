set(sdf_analysis_buffersizing_sources
        bounded_buffer.cc
        buffer.cc
        buffer_capacity_constrained.cc
        buffer_ning_gao.h
        )

set(sdf_analysis_buffersizing_headers
        bounded_buffer.h
        buffer.h
        buffer_ning_gao.h
        buffersizing.h
        storage_distribution.h
        )

add_library(sdf_analysis_buffersizing OBJECT ${sdf_analysis_buffersizing_sources} ${sdf_analysis_buffersizing_headers})
target_compile_definitions(sdf_analysis_buffersizing PUBLIC)