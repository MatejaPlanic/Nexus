#include "nxpch.h"
#include "FrameBuffer.h"

#include "Platform/OpenGL/OpenGLFrameBuffer.h"
#include "Renderer.h"

namespace Nexus {
	Ref<FrameBuffer> FrameBuffer::Create(const FrameBufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			NX_CORE_INFO("RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLFrameBuffer>(spec);
		}

		NX_CORE_ERROR("Unknown RendererAPI!");

		return nullptr;
	}
}