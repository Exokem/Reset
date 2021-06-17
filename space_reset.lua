
workspace "SpaceReset"
    configurations { "Debug", "Release" }
    architecture ( "x86" )
    platforms { "x86" }

    filter "configurations:Debug" defines { "DEBUG" } symbols "On"
    filter "configurations:Release" defines { "NDEBUG" } optimize "On"

    filter {}

    SDL2_LIB = "vendor/x86/SDL2/lib"
    SDL2_INCLUDE = "vendor/x86/SDL2/include/SDL2"
    SDL2_IMAGE_LIB = "vendor/x86/SDL2_image/lib"
    SDL2_IMAGE_INCLUDE = "vendor/x86/SDL2_image/include/SDL2"

project "RESET"
    kind "StaticLib"
    language "C"
    targetdir "bin/RESET/%{cfg.buildcfg}_%{cfg.platform}"
    targetname "RESET"

    files 
    { 
        "include/*.h",
        "src/**.c"
    }

    includedirs 
    { 
        "include/reset", 
        SDL2_INCLUDE,
        SDL2_IMAGE_INCLUDE
    }

    libdirs
    {
        SDL2_LIB,
        SDL2_IMAGE_LIB
    }

    links { "SDL2", "SDL2main", "SDL2_image" }

project "RTEST"
    kind "ConsoleApp"
    language "C"
    targetdir "bin/RTEST/%{cfg.buildcfg}_%{cfg.platform}"
    targetname "RTEST"

    files
    {
        "test/**.h",
        "test/**.c"
    }

    buildoptions { "-std=c99 -Wall -Wextra -ggdb" }

    includedirs 
    { 
        "include/reset", 
        SDL2_INCLUDE,
        SDL2_IMAGE_INCLUDE
    }

    libdirs
    {
        "bin/RESET/Debug_%{architecture}",
        SDL2_LIB,
        SDL2_IMAGE_LIB
    }

    links { "RESET", "SDL2", "SDL2main", "SDL2_image" }
