workspace "Lumex"
    architecture "x64"
    cppdialect "C++17"

    configurations { "Debug", "Release" }

    filter "configurations:Debug"
        targetdir "bin/debug"
        objdir "bin-int/debug"

        symbols "On"

        defines { LX_DEBUG }

    filter "configurations:Release"
        targetdir "bin/release"
        objdir "bin-int/release"

        optimize "On"
        buildoptions "/MT"

        defines { LX_RELEASE }

project "Engine"
    location "Engine"
    kind "ConsoleApp"
    language "C++"
    
    files { "Engine/src/**.h", "Engine/src/**.cpp" }

    includedirs { "Engine/src" }