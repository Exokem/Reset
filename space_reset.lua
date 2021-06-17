workspace "SpaceReset"
    configurations { "Debug", "Release" }
    architecture ( "x86" )
    platforms { "x64", "x32" }

    filter "configurations:Debug" defines { "DEBUG" } symbols "On"
    filter "configurations:Release" defines { "NDEBUG" } optimize "On"

    filter { "platforms:*32" } architecture "x86"
    filter { "platforms:*64" } architecture "x64"

    filter { "action:gmake2" } flags { cdialect "gnu99" }

    filter {}

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

    filter { "platforms:*32" }

    includedirs 
    { 
        "include/reset", 
        "vendor/x86/SDL2/include/SDL2",
        "vendor/x86/SDL2_image/include/SDL2",
    }

    libdirs
    {
        "vendor/x86/SDL2/lib",
        "vendor/x86/SDL2_image/lib"
    }

    filter { "platforms:*64" }
    
    includedirs 
    { 
        "include/reset", 
        "vendor/SDL2/x86_64-w64-mingw32/include/SDL2",
        "vendor/SDL2_image/x86_64-w64-mingw32/include/SDL2",
    }

    libdirs
    {
        "vendor/SDL2/x86_64-w64-mingw32/lib/x64",
        "vendor/SDL2_image/x86_64-w64-mingw32/lib/x64"
    }

    filter {}

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

    filter { "platforms:*32" }

    includedirs 
    { 
        "include/reset", 
        "vendor/x86/SDL2/include/SDL2",
        "vendor/x86/SDL2_image/include/SDL2",
    }

    libdirs
    {
        "bin/RESET/Debug_x32",
        "vendor/x86/SDL2/lib",
        "vendor/x86/SDL2_image/lib"
    }

    filter {}

    links { "RESET", "SDL2", "SDL2main", "SDL2_image" }
