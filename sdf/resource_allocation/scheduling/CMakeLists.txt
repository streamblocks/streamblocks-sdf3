set(sdf_resource_allocation_scheduling_sources
        list_scheduler.cc
        priority_list_scheduler.cc
        static_order_schedule.cc
        static_periodic_scheduler.cc
        static_periodic_scheduler_chao.cc
        )

set(sdf_resource_allocation_scheduling_headers
        list_scheduler.h
        priority_list_scheduler.h
        scheduling.h
        static_order_schedule.h
        static_periodic_scheduler.h
        static_periodic_scheduler_chao.h
        )

add_library(sdf_resource_allocation_scheduling OBJECT ${sdf_resource_allocation_scheduling_sources} ${sdf_resource_allocation_scheduling_headers})
target_compile_definitions(sdf_resource_allocation_scheduling PUBLIC)