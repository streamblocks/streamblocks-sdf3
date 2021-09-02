set(base_shell_sources
        dirs.cc
        shellnix.cc
        shellwin.cc
        shell.cc
        )

set(base_shell_headers
        dirs.cc
        shell.h
        shellnix.h
        shellwin.h
        )

add_library(base_shell OBJECT ${base_shell_sources} ${base_shell_headers})
target_compile_definitions(base_shell PUBLIC)