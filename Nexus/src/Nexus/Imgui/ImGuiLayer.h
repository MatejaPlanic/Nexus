#pragma once

#include "Nexus/Core/Layer.h"
#include <Nexus/Events/KeyEvent.h>
#include <Nexus/Events/MouseEvent.h>
#include <Nexus/Events/ApplicationEvent.h>

namespace Nexus	{
	class ImGuiLayer : public Layer 
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach();
		virtual void OnDetach();
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		void SetBlockEvents(bool block) { m_BlockEvents = block; }
	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;
	};

}