#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

static const uint32_t s_MapWidth = 24;
static const char* s_MapTiles =
"WWWWWWWWWWWWWWWWWWWWWWWW"
"WWWWWWWDDDDWWWWWWWWWWWWW"
"WWWWWWWWWWWDDDDWWWWWWWWW"
"WWWWWDDDDDDDDDDDDDWWWWWW"
"WWWWWDDDDDWWWWWWWWWWWWWW"
"WWWWWWWWWWWDDDDDWWWWWWWW"
"WWWWWWDDDDWWWWWWDDDDDDWW"
"WWWWWWWDDDDDDDDDWWWWWWWW"
"WWWDDDDDDDDWWWWWWWWWWWWW"
"WWWWWWWWWDDDDDDDDWWWWWWW"
"WWWWWWWDDDWWWWWWWWWWWWWW"
"WWWWWWDDDDDDDDDDDWWWWWWW"
"WWWWWWWDDDDDDDDWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWWWWWW"
;

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{

}

void Sandbox2D::OnAttach()
{
	m_CheckerboardTexture = Nexus::Texture2D::Create("assets/textures/Checkerboard.png");

	m_SpriteSheet = Nexus::Texture2D::Create("assets/game/textures/RPGpack_sheet_2X.png");

	m_TextureStairs = Nexus::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 7, 6 }, { 128, 128 });
	m_TextureTree = Nexus::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 2, 1 }, { 128, 128 }, { 1, 2 });

	m_MapWidth = s_MapWidth;
	m_MapHeight = strlen(s_MapTiles) / s_MapWidth;

	s_TextureMap['D'] = Nexus::SubTexture2D::CreateFromCoords(m_SpriteSheet, {6, 11}, {128, 128});
	s_TextureMap['W'] = Nexus::SubTexture2D::CreateFromCoords(m_SpriteSheet, {11, 11}, {128, 128});
	
}
 
void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Nexus::Timestep ts)
{
	NX_PROFILE_FUNCTION();

	{ 
		NX_PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(ts);
	}
	
	Nexus::Renderer2D::ResetStats();

	{
		NX_PROFILE_SCOPE("Renderer Prep");
		Nexus::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Nexus::RenderCommand::Clear();
	}

	{
		NX_PROFILE_SCOPE("Renderer Draw");

#if 1
		Nexus::Renderer2D::BeginScene(m_CameraController.GetCamera());

		//Nexus::Renderer2D::DrawRotatedQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, glm::radians(-45.0f), { 0.8f, 0.2f, 0.3f, 1.0f });
		//Nexus::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Nexus::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f }); 
		Nexus::Renderer2D::DrawQuad({ -1.0f, -0.5f }, { 0.5f, 0.5f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Nexus::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f}, { 10.0f, 10.0f }, m_CheckerboardTexture, 10.0f);
		Nexus::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f}, { 1.0f, 1.0f }, 45.0f,m_CheckerboardTexture, 20.0f);

		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.5f };
				Nexus::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
			}
		}

		Nexus::Renderer2D::EndScene();

#endif

#if 0
		Nexus::Renderer2D::BeginScene(m_CameraController.GetCamera());

		for (uint32_t i = 0; i < m_MapHeight; i++)
		{
			for (uint32_t j = 0; j < m_MapWidth; j++)
			{
				char tileType = s_MapTiles[j + i * m_MapWidth];
				Nexus::Ref<Nexus::SubTexture2D> texture;

				if (s_TextureMap.find(tileType) != s_TextureMap.end())
				{
					texture = s_TextureMap[tileType];
				}
				else
				{
					texture = m_TextureStairs;
				}

				Nexus::Renderer2D::DrawQuad({i - m_MapWidth / 2.0f,j - m_MapHeight / 2.0f, 0.5f }, { 1.0f, 1.0f }, texture);
			}
		}

		//Nexus::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, m_TextureStairs);
		//Nexus::Renderer2D::DrawQuad({ 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, m_TextureBarrel);
		//Nexus::Renderer2D::DrawQuad({ -1.0f, 0.0f, 0.0f }, { 1.0f, 2.0f }, m_TextureTree);

		Nexus::Renderer2D::EndScene();
#endif
	}
}

void Sandbox2D::OnImGuiRender()
{
	NX_PROFILE_FUNCTION();

	static bool dockspaceOpen = true;

    static bool opt_fullscreen = true;
    static bool opt_padding = false;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }
    else
    {
        dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
    }

    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    if (!opt_padding)
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
    if (!opt_padding)
        ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    // Submit the DockSpace
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {

			if (ImGui::MenuItem("Exit", ""))
				Nexus::Application::Get().Close();

            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

	ImGui::Begin("Settings");

	auto stats = Nexus::Renderer2D::GetStats();

	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quad Count: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());


	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	ImGui::End();

	ImGui::End();
}

void Sandbox2D::OnEvent(Nexus::Event& event)
{
	m_CameraController.OnEvent(event);
}
