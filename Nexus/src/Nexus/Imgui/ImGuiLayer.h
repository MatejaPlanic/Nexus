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
		virtual void OnImGuiRender();

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}