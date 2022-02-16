
includes("repl", "psyc")

add_cflags("-Wall", "-Wextra", "-Werror")

target("Psylang")
do
    set_kind("phony")
end
target_end()