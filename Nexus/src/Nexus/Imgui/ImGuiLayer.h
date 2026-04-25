#pragma once

#include "Nexus/Layer.h"
#include <Nexus/Events/KeyEvent.h>
#include <Nexus/Events/MouseEvent.h>
#include <Nexus/Events/ApplicationEvent.h>

namespace Nexus	{
	class NEXUS_API ImGuiLayer : public Layer 
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach();
		virtual void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);

	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& event);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event);
		bool OnMouseMovedEvent(MouseMovedEvent& event);
		bool OnMouseScrolledEvent(MouseScrolledEvent& event);
		bool OnKeyPressedEvent(KeyPressedEvent& event);
		bool OnKeyReleasedEvent(KeyReleasedEvent& event);
		bool OnKeyTypedEvent(KeyTypedEvent& event);
		bool OnWindowResizeEvent(WindowResizeEvent& event);
	private:
		float m_Time = 0.0f;

	};

}