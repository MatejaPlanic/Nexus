#pragma once

#include "Application.h"
#include "Log.h"

#ifdef NX_PLATFORM_WINDOWS

extern Nexus::Application* Nexus::CreateApplication();

int main(int argc, char** argv)
{
	Nexus::Log::Init();

	NX_PROFILE_BEGIN_SESSION("Startup", "Nexus-Startup.json");
	auto app = Nexus::CreateApplication();
	NX_PROFILE_END_SESSION();

	NX_PROFILE_BEGIN_SESSION("Runtime", "Nexus-Runtime.json");
	app->Run();
	NX_PROFILE_END_SESSION();

	NX_PROFILE_BEGIN_SESSION("Shutdown", "Nexus-Shutdown.json");
	delete app;
	NX_PROFILE_END_SESSION();
}

#endif
