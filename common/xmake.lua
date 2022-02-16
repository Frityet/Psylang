target("psycommon")
do
    set_kind("headeronly")
    add_headerfiles("src/**.h")
    add_includedirs("src/", { public = true })
end
target_end()