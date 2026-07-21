#pragma once

#include "Nexus.h"

class Sandbox2D : public Nexus::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Nexus::Timestep ts) override;
	void OnImGuiRender() override;
	void OnEvent(Nexus::Event& event) override;
private:
	Nexus::OrthographicCameraController m_CameraController;

	Nexus::Ref<Nexus::VertexArray> m_SquareVertexArray;

	Nexus::Ref<Nexus::Shader> m_FlatColorShader;

	Nexus::Ref<Nexus::Texture2D> m_CheckerboardTexture;
	Nexus::Ref<Nexus::Texture2D> m_SpriteSheet;
	Nexus::Ref<Nexus::SubTexture2D> m_TextureStairs,m_TextureBarrel,m_TextureTree;

	Nexus::Ref<Nexus::FrameBuffer> m_FrameBuffer;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

	std::unordered_map<char, Nexus::Ref<Nexus::SubTexture2D>> s_TextureMap;

	uint32_t m_MapWidth, m_MapHeight;
};