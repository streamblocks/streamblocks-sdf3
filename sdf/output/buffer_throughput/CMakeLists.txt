set(sdf_output_buffer_throughput_sources
        buffy.cc
        buffy_autoconc.cc
        )

set(sdf_output_buffer_throughput_headers
        buffy.h
        )

add_library(sdf_output_buffer_throughput OBJECT ${sdf_output_buffer_throughput_sources} ${sdf_output_buffer_throughput_headers})
target_compile_definitions(sdf_output_buffer_throughput PUBLIC)