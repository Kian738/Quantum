#pragma once

#include "EditorCore.h"
#include "ConsolePanel.h"

namespace Quantum
{
	class MainPanel
	{
	private:
		Ref<ConsolePanel> m_ConsolePanel;
		bool m_IsFullscreen = true;
	public:
		MainPanel();

		void Update();
	private:
		void CheckToggleActions();

		void MainMenuBar();
		void DockSpace() const;

		bool IsKeyPressed(ImGuiKey key);
		bool IsCombinationPressed(ImGuiKey key);
	};
}
