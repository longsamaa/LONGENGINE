workspace "LONG"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "LONG/vendor/GLFW/include"
include "LONG/vendor/GLFW"

project "LONG"
	location "LONG"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" ..outputdir.. "/%{prj.name}")
	objdir ("bin-int/" ..outputdir.. "/%{prj.name}")

	pchheader "Longpch.h"
	pchsource "LONG/src/Longpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"LONG_PLATFORM_WINDOWS",
			"LONG_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "LONG_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "LONG_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "LONG_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" ..outputdir.. "/%{prj.name}")
	objdir ("bin-int/" ..outputdir.. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Long/vendor/spdlog/include",
		"Long/src"
	}

	links
	{
		"LONG"
	}


	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.18362.0"

		defines
		{
			"LONG_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "LONG_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "LONG_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "LONG_DIST"
		optimize "On"