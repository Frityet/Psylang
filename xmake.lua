--Config:
local packages = {
}

local sanitizers = { "address", "leak", "undefined" }

local cxxflags = {
    release = {},
    debug = {
        "-Wno-unused-function", "-Wno-unused-parameter", "-Wno-unused-variable"
    },
    regular = {
        "-Wall", "-Wextra", "-Werror",
        "-fms-extensions", "-Wno-microsoft"
    }
}

local ldflags = {
    release = {},
    debug = {},
    regular = {}
}

set_languages {
    "cxx98"
}

add_rules("mode.debug", "mode.release")

add_requires(packages)

target("Psylang")
do
    set_kind("binary")
    add_packages(packages)

    add_files("src/**.cpp")
    add_headerfiles("src/**.hpp")

    add_includedirs("src/", "src/include")

    add_cflags(cxxflags.regular)
    add_ldflags(ldflags.regular)

    if is_mode("debug") then
        add_cflags(cxxflags.debug)
        add_ldflags(ldflags.debug)

        for _, v in ipairs(sanitizers) do
            add_cxflags("-fsanitize=" .. v)
            add_ldflags("-fsanitize=" .. v)
        end

        add_defines("PROJECT_DEBUG")
    elseif is_mode("release") then
        add_cflags(cxxflags.release)
        add_ldflags(ldflags.release)
    end
end
target_end()
