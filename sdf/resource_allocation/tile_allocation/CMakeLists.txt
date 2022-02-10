set(sdf_resource_allocation_tile_allocation_sources
        binding.cc
        loadbalance.cc
        )

set(sdf_resource_allocation_tile_allocation_headers
        binding.h
        loadbalance.h
        )

add_library(sdf_resource_allocation_tile_allocation OBJECT ${sdf_resource_allocation_tile_allocation_sources} ${sdf_resource_allocation_tile_allocation_sources_headers})
target_compile_definitions(sdf_resource_allocation_tile_allocation PUBLIC)