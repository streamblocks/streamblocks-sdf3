set(sdf_analysis_token_communication_sources
        comm_trace.cc
        )

set(sdf_analysis_token_communication_headers
        comm_trace.h
        )

add_library(sdf_analysis_token_communication OBJECT ${sdf_analysis_token_communication_sources} ${sdf_analysis_token_communication_headers})
target_compile_definitions(sdf_analysis_token_communication PUBLIC)