set(sdf_resource_allocation_flow_sources
        constraint.cc
        flow.cc
        memory.cc
        noc.cc
        tile.cc
        )

set(sdf_resource_allocation_flow_sources_headers
        flow.h
        types.h
        )

add_library(sdf_resource_allocation_flow OBJECT ${sdf_resource_allocation_flow_sources} ${sdf_resource_allocation_flow_sources_headers})
target_compile_definitions(sdf_resource_allocation_flow PUBLIC)