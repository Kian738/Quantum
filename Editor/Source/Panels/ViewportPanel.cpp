#include "ViewportPanel.h"

#include <Graphics/Renderer.h>

namespace Quantum
{
	ViewportPanel::ViewportPanel() : PanelBase("Viewport", true)
	{
	}

	void ViewportPanel::Draw()
	{
		auto viewportSize = ImGui::GetContentRegionAvail();
		auto frameBuffer = Renderer::GetFrameBuffer();
		frameBuffer->BindAsTexture();
		ImGui::Image((void*)frameBuffer->GetColorAttachment(), viewportSize, ImVec2(0, 1), ImVec2(1, 0));

		// TODO: Mouse has to be disabled when interacting with the viewport
		if (ImGui::IsWindowHovered())
			GEngine->GetWindow().SetCursorMode(CursorMode::Disabled);
	}

	void ViewportPanel::SetStyleVars() const
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2());
	}

	void ViewportPanel::ResetStyleVars() const
	{
		ImGui::PopStyleVar();
	}
}
