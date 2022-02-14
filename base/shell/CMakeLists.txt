if(WIN32)
    set(base_shell_sources
            dirs.cc
            shellwin.cc
            shell.cc
            )

    set(base_shell_headers
            dirs.h
            shell.h
            shellwin.h
            )
else()
    set(base_shell_sources
            dirs.cc
            shellnix.cc
            shell.cc
            )

    set(base_shell_headers
            dirs.h
            shell.h
            shellnix.h
            )
endif()

add_library(base_shell OBJECT ${base_shell_sources} ${base_shell_headers})
target_compile_definitions(base_shell PUBLIC)