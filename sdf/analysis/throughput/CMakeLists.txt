set(sdf_analysis_throughput_sources
        deadlock.cc
        selftimed_throughput.cc
        static_periodic_ning_gao.cc
        tdma_schedule.cc
        )

set(sdf_analysis_throughput_headers
        deadlock.h
        selftimed_throughput.h
        static_periodic_ning_gao.h
        tdma_schedule.h
        throughput.h
        )

add_library(sdf_analysis_throughput OBJECT ${sdf_analysis_throughput_sources} ${sdf_analysis_throughput_headers})
target_compile_definitions(sdf_analysis_throughput PUBLIC)