target("psyc")
do
    set_kind("static")
    add_files("src/**.c")
    add_headerfiles("src/**.h")
    add_includedirs("src/", { public = true })
end
target_end()