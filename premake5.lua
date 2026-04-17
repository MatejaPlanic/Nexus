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
IncludeDir["Glad"] = "Nexus/external/glad/include"
IncludeDir["Imgui"] = "Nexus/external/imgui"

include "Nexus/external/glfw"
include "Nexus/external/glad"
include "Nexus/external/imgui"

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
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.Imgui}"
	}

	links
	{
		"GLFW",
		"Glad",
		"Imgui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++23"
		staticruntime "On"
		systemversion "latest"
		defines
		{
			"NX_PLATFORM_WINDOWS",
			"NX_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{MKDIR} ../bin/" .. outputdir .. "/Sandbox"),
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "NX_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "NX_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "NX_DIST"
		buildoptions "/MD"
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
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "NX_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "NX_DIST"
		buildoptions "/MD"
		optimize "On"

	filter "system:windows"
    	buildoptions { "/utf-8" }
