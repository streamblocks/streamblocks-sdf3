set(sdf_resource_allocation_noc_allocation_mapping_sources
        nocmapping.cc
        )

set(sdf_resource_allocation_noc_allocation_mapping_headers
        nocmapping.h
        )

add_library(sdf_resource_allocation_noc_allocation_mapping OBJECT ${sdf_resource_allocation_noc_allocation_mapping_sources} ${sdf_resource_allocation_noc_allocation_mapping_headers})
target_compile_definitions(sdf_resource_allocation_noc_allocation_mapping PUBLIC)