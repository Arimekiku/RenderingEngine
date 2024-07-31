workspace "RenderingEngine"
	architecture "x86_64"

	configurations 
	{
		"Debug",
		"Release"
	}

outdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

includes = {}
includes["GLFW"] = "RenderingEngine/vendor/GLFW/include"
includes["spdlog"] = "RenderingEngine/vendor/spdlog/include"

include "RenderingEngine/vendor/GLFW"

project "RenderingEngine"
	location "RenderingEngine"
	kind "SharedLib"
	language "C++"

	targetdir ("binaries/" .. outdir .. "/%{prj.name}")
	objdir ("intermediates/" .. outdir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs 
	{
		"%{includes.spdlog}",
		"%{includes.GLFW}",
	}

	links 
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines 
		{
			"APP_PLATFORM_WINDOWS",
			"APP_BUILD_SHAREDLIB"
		}
		
		postbuildcommands 
		{
			("{COPY} %{cfg.buildtarget.relpath} ../binaries/" .. outdir .. "/Application")
		}

	filter "configurations:Debug"
		defines "APP_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "APP_RELEASE"
		optimize "On"

project "Application"
	location "Application"
	kind "ConsoleApp"
	language "C++"

	targetdir ("binaries/" .. outdir .. "/%{prj.name}")
	objdir ("intermediates/" .. outdir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs 
	{
		"RenderingEngine/src",
		"%{includes.spdlog}",
	}

	links 
	{
		"RenderingEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines 
		{
			"APP_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "APP_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "APP_RELEASE"
		optimize "On"