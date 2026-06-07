#include "nxpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Nexus {

	OpenGLContext::OpenGLContext(GLFWwindow* window)
		: m_Window(window)
	{}

	void OpenGLContext::Init()
	{
		NX_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	}

	void OpenGLContext::SwapBuffers()
	{
		NX_PROFILE_FUNCTION();

		glfwSwapBuffers(m_Window);
	}

}