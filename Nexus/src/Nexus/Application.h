#pragma once

#include "Core.h"

namespace Nexus
{
	class NEXUS_API Application
	{
	public:
		Application();
		~Application();
		void Run();
	};

	Application* CreateApplication();
}

