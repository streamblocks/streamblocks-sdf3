set(sdf_output_schedule_sources
        schedule.cc
        )

set(sdf_output_schedule_headers
        schedule.h
        )

add_library(sdf_output_schedule OBJECT ${sdf_output_schedule_sources} ${sdf_output_schedule_headers})
target_compile_definitions(sdf_output_schedule PUBLIC)