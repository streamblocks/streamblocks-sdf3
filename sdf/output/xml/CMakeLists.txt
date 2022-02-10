set(sdf_output_xml_sources
        xml.cc
        )

set(sdf_output_xml_headers
        xml.h
        )

add_library(sdf_output_xml OBJECT ${sdf_output_xml_sources} ${sdf_output_xml_headers})
target_compile_definitions(sdf_output_xml PUBLIC)