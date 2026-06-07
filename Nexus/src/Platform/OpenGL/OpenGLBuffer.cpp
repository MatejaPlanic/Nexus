#include "nxpch.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace Nexus {

	// VertexBuffer --------------------------------------------------------------

	Nexus::OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
	{
		NX_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		NX_PROFILE_FUNCTION();

		glDeleteBuffers(1, &m_RendererID);
	}

	void Nexus::OpenGLVertexBuffer::Bind() const
	{
		NX_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void Nexus::OpenGLVertexBuffer::Unbind() const
	{
		NX_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	// IndexBuffer --------------------------------------------------------------

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* vertices, uint32_t count) : m_Count(count)
	{
		NX_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), vertices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		NX_PROFILE_FUNCTION();

		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		NX_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		NX_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}
