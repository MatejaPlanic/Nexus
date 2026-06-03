#include "Nexus.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include "Nexus/Core/EntryPoint.h"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"

class ExampleLayer : public Nexus::Layer
{
public:
	ExampleLayer() : Layer("Example"), m_CameraController(1280.0f / 720.0f,true)
	{
		m_VertexArray = Nexus::VertexArray::Create();

		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		Nexus::Ref<Nexus::VertexBuffer> vertexBuffer(Nexus::VertexBuffer::Create(vertices, sizeof(vertices)));

		Nexus::BufferLayout layout = {
			{ Nexus::ShaderDataType::Float3, "a_Position" }
		};

		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = {
			0, 1, 2
		};

		Nexus::Ref<Nexus::IndexBuffer> indexBuffer(Nexus::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVertexArray = Nexus::VertexArray::Create();

		float squareVerticies[5 * 4] = {
			-0.5f, -0.5f, 0.0f,0.0f,0.0f,
			 0.5f, -0.5f, 0.0f,1.0f,0.0f,
			 0.5f,  0.5f, 0.0f,1.0f,1.0f,
			-0.5f,  0.5f, 0.0f,0.0f,1.0f
		};

		Nexus::Ref<Nexus::VertexBuffer> squareVB(Nexus::VertexBuffer::Create(squareVerticies, sizeof(squareVerticies)));

		Nexus::BufferLayout squareLayout = {
			{ Nexus::ShaderDataType::Float3, "a_Position" },
			{ Nexus::ShaderDataType::Float2, "a_TexCoord" }
		};

		squareVB->SetLayout(squareLayout);

		m_SquareVertexArray->AddVertexBuffer(squareVB);

		uint32_t squareInices[6] = {
			0, 1, 2, 2, 3, 0
		};

		Nexus::Ref<Nexus::IndexBuffer> squareVA(Nexus::IndexBuffer::Create(squareInices, sizeof(squareInices) / sizeof(uint32_t)));

		m_SquareVertexArray->SetIndexBuffer(squareVA);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			void main()
			{
				color = vec4(1.0,0.0,0.0,1.0);
			}
		)";

		m_Shader = Nexus::Shader::Create("Triangle",vertexSrc, fragmentSrc);


		std::string vertexSrc2 = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc2 = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color,1.0);
			}
		)";

		m_Shader2 = Nexus::Shader::Create("FlatColor",vertexSrc2, fragmentSrc2);

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");
	
		m_Texture = Nexus::Texture2D::Create("assets/textures/Checkerboard.png");
		
		m_NexusLogoTexture = Nexus::Texture2D::Create("assets/textures/NexusLogo.png");

		std::dynamic_pointer_cast<Nexus::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Nexus::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
    }

	void OnUpdate(Nexus::Timestep ts) override
	{
		m_CameraController.OnUpdate(ts);

		Nexus::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Nexus::RenderCommand::Clear();

		Nexus::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Nexus::OpenGLShader>(m_Shader2)->Bind();
		std::dynamic_pointer_cast<Nexus::OpenGLShader>(m_Shader2)->UploadUniformFloat3("u_Color", m_SquareColor);


		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				glm::vec3 pos(i * 0.11f, j * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Nexus::Renderer::Submit(m_SquareVertexArray, m_Shader2, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();

		Nexus::Renderer::Submit(m_SquareVertexArray, textureShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		m_NexusLogoTexture->Bind();

		Nexus::Renderer::Submit(m_SquareVertexArray, textureShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		//Nexus::Renderer::Submit(m_VertexArray, m_Shader);

		Nexus::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");

		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));

		ImGui::End();
	}

	void OnEvent(Nexus::Event& event) override
	{
		m_CameraController.OnEvent(event);
	}


private:
	Nexus::ShaderLibrary m_ShaderLibrary;
	Nexus::Ref<Nexus::Shader> m_Shader;
	Nexus::Ref<Nexus::VertexArray> m_VertexArray;

	Nexus::Ref<Nexus::VertexArray> m_SquareVertexArray;
	Nexus::Ref<Nexus::Shader> m_Shader2;

	Nexus::Ref<Nexus::Texture2D> m_Texture, m_NexusLogoTexture;

	Nexus::OrthographicCameraController m_CameraController;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public Nexus::Application
{
public:
	Sandbox()
	{
		// PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}
	~Sandbox()
	{

	}
};

Nexus::Application* Nexus::CreateApplication()
{
	return new Sandbox();
}