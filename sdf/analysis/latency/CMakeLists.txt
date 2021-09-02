set(sdf_analysis_latency_sources
        minimal.cc
        selftimed.cc
        selftimed_minimal.cc
        single_processor_random_staticorder.cc
        )

set(sdf_analysis_latency_headers
        latency.h
        minimal.h
        selftimed.h
        selftimed_minimal.h
        single_processor_random_staticorder.h
        )

add_library(sdf_analysis_latency OBJECT ${sdf_analysis_latency_sources} ${sdf_analysis_latency_headers})
target_compile_definitions(sdf_analysis_latency PUBLIC)