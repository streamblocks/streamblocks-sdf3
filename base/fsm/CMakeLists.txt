set(base_fsm_sources
        fsm.cc
        )

set(base_fsm_headers
        fsm.h
        )

add_library(base_fsm OBJECT ${base_fsm_sources} ${base_fsm_headers})
target_compile_definitions(base_fsm PUBLIC BASE_FSM)