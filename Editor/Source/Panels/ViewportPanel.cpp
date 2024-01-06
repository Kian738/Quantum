#include "ViewportPanel.h"

#include <Graphics/Renderer.h>

#include "MainPanel.h"

namespace Quantum
{
	ViewportPanel::ViewportPanel(MainPanel* mainPanel)
		: PanelBase("Viewport", true)
		, m_MainPanel(mainPanel)
	{
	}

	void ViewportPanel::Draw()
	{
		static auto& window = GEngine->GetWindow();

		// TODO: Fix this not working properly
		/*auto isWindowHovered = ImGui::IsWindowHovered();
		if (m_IsMouseCaptured && !isWindowHovered)
		{
			m_IsMouseCaptured = false;
			window.SetCursorMode(CursorMode::Normal);
		}

		if (isWindowHovered)
		{
			window.SetCursorMode(CursorMode::Disabled);
			m_IsMouseCaptured = true;
		}*/

		if (ImGui::BeginMenuBar())
		{
			// TODO: Implement play/stop functionality and change the buttons accordingly
			if (ImGui::Button("Play"))
			{
			}
			if (ImGui::Button("Stop"))
			{
			}

			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 0, 0, 1));
			ImGui::Text("FPS: %.2f", ImGui::GetIO().Framerate);
			ImGui::PopStyleColor();

			ImGui::EndMenuBar();
		}

		auto viewportSize = ImGui::GetContentRegionAvail();
		auto frameBuffer = Renderer::GetFrameBuffer();
		frameBuffer->BindAsTexture();
		ImGui::Image((void*)frameBuffer->GetColorAttachment(), viewportSize, ImVec2(0, 1), ImVec2(1, 0));
	}

	void ViewportPanel::ApplyWindowSettings() const
	{
		// TODO: Put the viewport at its appropriate position
		ImGui::SetNextWindowSize({ 800, 450 });

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2());
	}

	void ViewportPanel::ResetWindowSettings() const
	{
		ImGui::PopStyleVar();
	}
}
