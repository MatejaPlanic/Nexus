#include "Nexus.h"
#include "Nexus/Core/EntryPoint.h"

#include "EditorLayer.h"

namespace Nexus {
	class NexusEditor : public Application
	{
	public:
		NexusEditor()
			: Application("Nexus Editor")
		{
			PushLayer(new EditorLayer());
		}
		~NexusEditor()
		{

		}
	};

	Application* CreateApplication()
	{
		return new NexusEditor();
	}
}