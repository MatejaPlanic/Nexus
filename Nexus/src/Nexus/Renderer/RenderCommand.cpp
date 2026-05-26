#include "nxpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Nexus
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}