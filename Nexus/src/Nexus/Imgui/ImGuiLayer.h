#pragma once

#include "Nexus/Core/Layer.h"
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

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}