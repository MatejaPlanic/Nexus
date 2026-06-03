#include "nxpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Nexus {
	Ref<Shader> Shader::Create(const std::string& filePath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			NX_CORE_INFO("RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return make_shared<OpenGLShader>(filePath);
		}

		NX_CORE_ERROR("Unknown RendererAPI!");

		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			NX_CORE_INFO("RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return make_shared<OpenGLShader>(name,vertexSrc, fragmentSrc);
		}

		NX_CORE_ERROR("Unknown RendererAPI!");

		return nullptr;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();

		Add(name, shader);

	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		if (m_Shaders.find(name) != m_Shaders.end())
		{
			NX_CORE_ERROR("Shader already exists!");
			return;
		}

		m_Shaders[name] = shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filePath)
	{
		auto shader = Shader::Create(filePath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filePath)
	{
		auto shader = Shader::Create(filePath);
		Add(name,shader);
		return shader;;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		if (m_Shaders.find(name) == m_Shaders.end())
		{
			NX_CORE_ERROR("Shader not found!");
			return nullptr;
		}
		return m_Shaders[name];
	}
}
