set(sdf_resource_allocation_binding_aware_sdfg_sources
        binding_aware_sdfg.cc
        )

set(sdf_resource_allocation_binding_aware_sdfg_headers
        binding_aware_sdfg.h
        )

add_library(sdf_resource_allocation_binding_aware_sdfg OBJECT ${sdf_resource_allocation_binding_aware_sdfg_sources} ${sdf_resource_allocation_binding_aware_sdfg_headers})
target_compile_definitions(sdf_resource_allocation_binding_aware_sdfg PUBLIC)