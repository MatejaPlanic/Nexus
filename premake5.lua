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
IncludeDir["glm"] = "Nexus/external/glm"
IncludeDir["entt"] = "Nexus/external/entt/include"
IncludeDir["stb_image"] = "Nexus/external/stb_image"
IncludeDir["yaml_cpp"] = "Nexus/external/yaml-cpp/include"
IncludeDir["ImGuizmo"] = "Nexus/external/ImGuizmo"

include "Nexus/external/glfw"
include "Nexus/external/glad"
include "Nexus/external/imgui"
include "Nexus/external/yaml-cpp"

project "Nexus"
	location "Nexus"
	kind "StaticLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "nxpch.h"
	pchsource "Nexus/src/nxpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/external/stb_image/**.cpp",
		"%{prj.name}/external/stb_image/**.h",
		"%{prj.name}/external/glm/glm/**.hpp",
		"%{prj.name}/external/glm/glm/**.inl",
		"%{prj.name}/external/ImGuizmo/ImGuizmo.h",
		"%{prj.name}/external/ImGuizmo/ImGuizmo.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/external/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.Imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.yaml_cpp}",
		"%{IncludeDir.ImGuizmo}"
	}

	links
	{
		"GLFW",
		"Glad",
		"Imgui",
		"yaml-cpp",
		"opengl32.lib"
	}

	filter "files:Nexus/external/ImGuizmo/**.cpp"
		flags { "NoPCH" }

	filter "system:windows"
		cppdialect "C++23"
		staticruntime "On"
		systemversion "latest"
		defines
		{
			"NX_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE",
			"YAML_CPP_STATIC_DEFINE"
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
		"Nexus/src",
		"%{IncludeDir.glm}",
		"Nexus/external"
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

project "Nexus-Editor"
	location "Nexus-Editor"
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
		"Nexus/src",
		"%{IncludeDir.glm}",
		"Nexus/external",
		"%{IncludeDir.entt}",
		"%{IncludeDir.ImGuizmo}"
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
