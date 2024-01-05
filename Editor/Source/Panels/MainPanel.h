#pragma once

#include <Core/Types.h>

#include "PanelBase.h"
#include "ConsolePanel.h"

namespace Quantum
{
	class MainPanel
	{
	private:
		Scope<ConsolePanel> m_ConsolePanel;
		bool m_IsFullscreen = true;
	public:
		MainPanel()
			: m_ConsolePanel(CreateScope<ConsolePanel>())
		{};

		void Update();
	private:
		void CheckToggleActions();

		void MainMenuBar();
		void DockSpace() const;

		bool IsKeyPressed(ImGuiKey key);
		bool IsCombinationPressed(ImGuiKey key);
	};
}
