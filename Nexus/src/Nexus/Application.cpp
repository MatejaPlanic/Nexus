#include "nxpch.h"
#include "Application.h"

#include "Nexus/Events/ApplicationEvent.h"
#include "Nexus/Log.h"

namespace Nexus
{
	Application::Application()
	{
	}
	Application::~Application()
	{
	}
	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);

		NX_TRACE(e.ToString());

		while (true);
	}
}
