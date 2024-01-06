#pragma once

#include "EditorCore.h"

namespace Quantum
{
	class MainPanel;

	class ViewportPanel : public PanelBase
	{
	private:
		MainPanel* m_MainPanel;
		bool m_IsMouseCaptured = false;
	public:
		ViewportPanel(MainPanel* mainPanel);

		void Draw() override;
	private:
		ImGuiWindowFlags GetWindowFlags() const override { return ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_MenuBar; };

		void ApplyWindowSettings() const override;
		void ResetWindowSettings() const override;
	};
}
