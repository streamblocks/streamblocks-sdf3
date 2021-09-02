set(sdf_analysis_maxplus_sources
        mpdependencies.cc
        mpexplore.cc
        mpstorage.cc
        )

set(sdf_analysis_maxplus_headers
        mpdependencies.h
        mpexplore.h
        mpstorage.h
        )

add_library(sdf_analysis_maxplus OBJECT ${sdf_analysis_maxplus_sources} ${sdf_analysis_maxplus_headers})
target_compile_definitions(sdf_analysis_maxplus PUBLIC)