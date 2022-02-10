set(sdf_resource_allocation_mpsoc_arch_sources
        binding.cc
        component.cc
        connection.cc
        graph.cc
        memory.cc
        networkinterface.cc
        processor.cc
        tile.cc
        xml.cc
        )

set(sdf_resource_allocation_mpsoc_arch_sources_headers
        binding.h
        component.h
        connection.h
        graph.h
        memory.h
        networkinterface.h
        processor.h
        tile.h
        xml.h
        )

add_library(sdf_resource_allocation_mpsoc_arch OBJECT ${sdf_resource_allocation_mpsoc_arch_sources} ${sdf_resource_allocation_mpsoc_arch_sources_headers})
target_compile_definitions(sdf_resource_allocation_mpsoc_arch PUBLIC)