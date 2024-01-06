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

		bool IsPlaying() const { return false; }; // TODO: Implement
	private:
		void CheckToggleActions();

		void MainMenuBar();
		void DockSpace() const;
	};
}
