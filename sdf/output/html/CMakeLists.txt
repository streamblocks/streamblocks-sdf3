set(sdf_output_html_sources
        html.cc
        )

set(sdf_output_html_headers
        html.h
        )

add_library(sdf_output_html OBJECT ${sdf_output_html_sources} ${sdf_output_html_headers})
target_compile_definitions(sdf_output_html PUBLIC)