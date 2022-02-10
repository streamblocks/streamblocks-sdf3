set(sdf_resource_allocation_noc_allocation_scheduler_sources
        classic.cc
        greedy.cc
        knowledge.cc
        noc_scheduler.cc
        random.cc
        ripup.cc
        )

set(sdf_resource_allocation_noc_allocation_scheduler_headers
        classic.h
        greedy.h
        knowledge.h
        noc_scheduler.h
        random.h
        ripup.h
        )

add_library(sdf_resource_allocation_noc_allocation_scheduler OBJECT ${sdf_resource_allocation_noc_allocation_scheduler_sources} ${sdf_resource_allocation_noc_allocation_scheduler_headers})
target_compile_definitions(sdf_resource_allocation_noc_allocation_scheduler PUBLIC)