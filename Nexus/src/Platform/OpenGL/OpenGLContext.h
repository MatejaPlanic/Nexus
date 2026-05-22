#pragma once

#include "Nexus/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Nexus {
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* window);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_Window;
	};
}