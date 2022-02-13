set(base_xml_sources
        xml.cc
        )

set(base_xml_headers
        xml.h
        )

add_library(base_xml OBJECT ${base_xml_sources})
target_link_libraries(base_xml ${LIBXML2_LIBRARIES})
target_compile_definitions(base_xml PUBLIC)