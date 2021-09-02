set(sdf_analysis_mcm_sources
        mcm.cc
        mcmdg.cc
        mcmgraph.cc
        mcmhoward.cc
        mcmkarp.cc
        mcmyto.cc
        )

set(sdf_analysis_mcm_headers
        mcm.h
        mcmgraph.h
        mcmyto.cc
        )

add_library(sdf_analysis_mcm OBJECT ${sdf_analysis_mcm_sources} ${sdf_analysis_mcm_headers})
target_compile_definitions(sdf_analysis_mcm PUBLIC)