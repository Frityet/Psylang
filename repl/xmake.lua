target("psyrepl")
do
    set_kind("binary")
    add_files("src/**.c")
    add_headerfiles("src/**.h")
    add_deps("psyc")
end
target_end()