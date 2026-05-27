#include "Nexus.h"
#include <imgui/imgui.h>

class ExampleLayer : public Nexus::Layer
{
public:
	ExampleLayer() : Layer("Example"), m_Camera(-2.0f, 2.0f, -2.0f, 2.0f), m_CameraPosition(0.0f, 0.0f, 0.0f)
	{
		m_VertexArray.reset(Nexus::VertexArray::Create());

		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		std::shared_ptr<Nexus::VertexBuffer> vertexBuffer(Nexus::VertexBuffer::Create(vertices, sizeof(vertices)));

		Nexus::BufferLayout layout = {
			{ Nexus::ShaderDataType::Float3, "a_Position" }
		};

		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = {
			0, 1, 2
		};

		std::shared_ptr<Nexus::IndexBuffer> indexBuffer(Nexus::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVertexArray.reset(Nexus::VertexArray::Create());

		float squareVerticies[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<Nexus::VertexBuffer> squareVB(Nexus::VertexBuffer::Create(squareVerticies, sizeof(squareVerticies)));

		Nexus::BufferLayout squareLayout = {
			{ Nexus::ShaderDataType::Float3, "a_Position" }
		};

		squareVB->SetLayout(squareLayout);

		m_SquareVertexArray->AddVertexBuffer(squareVB);

		uint32_t squareInices[6] = {
			0, 1, 2, 2, 3, 0
		};

		std::shared_ptr<Nexus::IndexBuffer> squareVA(Nexus::IndexBuffer::Create(squareInices, sizeof(squareInices) / sizeof(uint32_t)));

		m_SquareVertexArray->SetIndexBuffer(squareVA);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			void main()
			{
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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

		m_Shader.reset(new Nexus::Shader(vertexSrc, fragmentSrc));


		std::string vertexSrc2 = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			
			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc2 = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5,1.0);
			}
		)";

		m_Shader2.reset(new Nexus::Shader(vertexSrc2, fragmentSrc2));
	
	}

	void OnUpdate() override
	{
		if (Nexus::Input::IsKeyPressed(NX_KEY_LEFT))
		{
			m_CameraPosition.x -= m_CameraSpeed;
		}

		else if (Nexus::Input::IsKeyPressed(NX_KEY_RIGHT))
		{
			m_CameraPosition.x += m_CameraSpeed;
		}

		if (Nexus::Input::IsKeyPressed(NX_KEY_DOWN))
		{
			m_CameraPosition.y -= m_CameraSpeed;
		}

		else if (Nexus::Input::IsKeyPressed(NX_KEY_UP))
		{
			m_CameraPosition.y += m_CameraSpeed;
		}

		if (Nexus::Input::IsKeyPressed(NX_KEY_A))
		{
			m_CameraRotation += m_CameraSpeed;
		}
		else if (Nexus::Input::IsKeyPressed(NX_KEY_D))
		{
			m_CameraRotation -= m_CameraSpeed;
		}

		Nexus::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Nexus::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Nexus::Renderer::BeginScene(m_Camera);

		Nexus::Renderer::Submit(m_SquareVertexArray, m_Shader2);

		Nexus::Renderer::Submit(m_VertexArray, m_Shader);

		Nexus::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{

	}

	void OnEvent(Nexus::Event& event) override
	{
		
	}


private:
	std::shared_ptr<Nexus::Shader> m_Shader;
	std::shared_ptr<Nexus::VertexArray> m_VertexArray;

	std::shared_ptr<Nexus::VertexArray> m_SquareVertexArray;
	std::shared_ptr<Nexus::Shader> m_Shader2;

	Nexus::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraSpeed = 0.1f;
	float m_CameraRotation = 0.0f;
};

class Sandbox : public Nexus::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox()
	{

	}
};

Nexus::Application* Nexus::CreateApplication()
{
	return new Sandbox();
}