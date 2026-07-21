#pragma once

#include "Nexus.h"

namespace Nexus {
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(Timestep ts) override;
		void OnImGuiRender() override;
		void OnEvent(Event& event) override;
	private:
		OrthographicCameraController m_CameraController;

		Ref<VertexArray> m_SquareVertexArray;

		Ref<Shader> m_FlatColorShader;

		Ref<Texture2D> m_CheckerboardTexture;
		Ref<Texture2D> m_SpriteSheet;
		Ref<SubTexture2D> m_TextureStairs, m_TextureBarrel, m_TextureTree;

		Ref<FrameBuffer> m_FrameBuffer;

		glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

		std::unordered_map<char, Ref<SubTexture2D>> s_TextureMap;

		glm::vec2 m_ViewportSize;

		uint32_t m_MapWidth, m_MapHeight;

		bool m_ViewportFocused = false, m_ViewportHovered = false;
	};
}