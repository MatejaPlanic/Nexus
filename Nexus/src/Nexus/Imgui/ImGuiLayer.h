#pragma once

#include "Nexus/Layer.h"

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
		float m_Time = 0.0f;

	};

}