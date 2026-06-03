#include "nxpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Nexus {

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				NX_CORE_INFO("RendererAPI::None is currently not supported!");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return std::make_shared<OpenGLVertexArray>();
		}

		NX_CORE_ERROR("Unknown RendererAPI!");

		return nullptr;
	}
}
