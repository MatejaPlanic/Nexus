#include "Nexus.h"
#include <imgui/imgui.h>

class ExampleLayer : public Nexus::Layer
{
public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override
	{
		if (Nexus::Input::IsKeyPressed(NX_KEY_TAB))
			NX_INFO("Tab key is pressed!");
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Example");
		ImGui::Text("Hello, world!");
		ImGui::End();
	}

};

class Sandbox : public Nexus::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox()
	{

	}
};

Nexus::Application* Nexus::CreateApplication()
{
	return new Sandbox();
}