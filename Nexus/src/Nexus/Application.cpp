#include "nxpch.h"
#include "Application.h"

#include "Nexus/Events/ApplicationEvent.h"
#include "Nexus/Log.h"

#include <GLFW/glfw3.h>

namespace Nexus
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}
	Application::~Application()
	{
	}
	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}
}
