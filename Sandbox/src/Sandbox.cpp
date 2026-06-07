#include "Nexus.h"
#include "Nexus/Core/EntryPoint.h"

#include "GameLayer.h"

class Sandbox : public Nexus::Application
{
public:
	Sandbox()
	{
		// PushLayer(new ExampleLayer());
		//PushLayer(new Sandbox2D());
		PushLayer(new GameLayer());
	}
	~Sandbox()
	{

	}
};

Nexus::Application* Nexus::CreateApplication()
{
	return new Sandbox();
}