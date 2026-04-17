#include "Nexus.h"

class ExampleLayer : public Nexus::Layer
{
public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override
	{
		NX_INFO("ExampleLayer::Update");
	}

	void OnEvent(Nexus::Event& event) override
	{
		NX_INFO("{0}", event.ToString());
	}
};

class Sandbox : public Nexus::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Nexus::ImGuiLayer());
	}
	~Sandbox()
	{

	}
};

Nexus::Application* Nexus::CreateApplication()
{
	return new Sandbox();
}