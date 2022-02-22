includes("repl", "psyc", "common")

add_cflags("-Wall", "-Wextra", "-Werror", "-Og", "-g")

target("Psylang")
do
    set_kind("phony")
    add_deps("psyrepl", "psyc", "psycommon")
end
target_end()
