workspace "Nexus"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Nexus/external/glfw/include"

include "Nexus/external/glfw"

project "Nexus"
	location "Nexus"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "nxpch.h"
	pchsource "Nexus/src/nxpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/external/spdlog/include",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++23"
		staticruntime "On"
		systemversion "latest"
		defines
		{
			"NX_PLATFORM_WINDOWS",
			"NX_BUILD_DLL"
		}

		postbuildcommands
		{
			("{MKDIR} ../bin/" .. outputdir .. "/Sandbox"),
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "NX_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "NX_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "NX_DIST"
		optimize "On"

	filter "system:windows"
    	buildoptions { "/utf-8" }

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Nexus/external/spdlog/include",
		"Nexus/src"
	}

	links
	{
		"Nexus"
	}

	filter "system:windows"
		cppdialect "C++23"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"NX_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "NX_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "NX_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "NX_DIST"
		optimize "On"

	filter "system:windows"
    	buildoptions { "/utf-8" }
