#pragma once

#include "Application.h"
#include "Log.h"

#ifdef NX_PLATFORM_WINDOWS

extern Nexus::Application* Nexus::CreateApplication();

int main(int argc, char** argv)
{
	Nexus::Log::Init();
	NX_CORE_WARN("Initialized Log!");
	NX_INFO("Initialized Log!");

	auto app = Nexus::CreateApplication();
	app->Run();
	delete app;
}

#endif
