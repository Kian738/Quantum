#include "PanelManager.h"

#include "EditorCore.h"

namespace Quantum
{
	void PanelManager::Register(PanelBase* panel)
	{
		m_Panels.push_back(panel);
	}

	void PanelManager::Unregister(PanelBase* panel)
	{
		m_Panels.erase(
			std::remove(m_Panels.begin(), m_Panels.end(), panel),
			m_Panels.end()
		);
	}

	void PanelManager::DrawAll()
	{
		for (auto panel : m_Panels)
			panel->Update();
	}

	void PanelManager::CheckToggleActions()
	{
		for (auto panel : m_Panels)
			if (auto toggleKey = panel->GetToggleKey(); toggleKey && ImGuiUtils::IsCombinationPressed(toggleKey))
				panel->Toggle();
	}

	void PanelManager::DrawWindowMenuItems()
	{
		for (auto panel : m_Panels)
			if (ImGui::MenuItem(panel->m_Title.c_str(), GetShortcutName(panel), panel->IsOpen()))
				panel->Toggle();
	}

	const char* PanelManager::GetShortcutName(PanelBase* panel)
	{
		static auto shortcutCache = Dictionary<PanelBase*, String>();

		if (auto it = shortcutCache.find(panel); it != shortcutCache.end())
			return it->second.c_str();

		auto shortcut = panel->GetToggleKey();
		auto shortcutString = shortcut ? std::format("Ctrl+Alt+{}", ImGui::GetKeyName(shortcut)) : "";
		shortcutCache[panel] = shortcutString;

		return shortcutString.c_str();
	}
}

