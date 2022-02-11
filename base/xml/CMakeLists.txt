find_package(LibXml2 REQUIRED)

set(base_xml_sources
        xml.cc
        )

set(base_xml_headers
        xml.h
        )

add_library(base_xml OBJECT ${base_xml_sources} ${base_xml_headers})
target_link_libraries(base_xml ${LIBXML2_LIBRARIES})
target_compile_definitions(base_xml PUBLIC)