set(sdf_resource_allocation_noc_allocation_problem_sources
        interconnect_graph.cc
        link.cc
        message.cc
        problem.cc
        route.cc
        schedulingentity.cc
        slot.h
        )

set(sdf_resource_allocation_noc_allocation_problem_headers
        interconnect_graph.h
        link.h
        message.h
        node.h
        problem.h
        route.h
        schedulingentity.h
        slot.h
        )

add_library(sdf_resource_allocation_noc_allocation_problem OBJECT ${sdf_resource_allocation_noc_allocation_problem_sources} ${sdf_resource_allocation_noc_allocation_problem_headers})
target_compile_definitions(sdf_resource_allocation_noc_allocation_problem PUBLIC)