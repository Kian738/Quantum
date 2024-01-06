#include "PanelManager.h"

#include "EditorCore.h"

namespace Quantum
{
	void PanelManager::Register(const Ref<PanelBase>& panel)
	{
		m_Panels.push_back(panel);
	}

	void PanelManager::DrawAll()
	{
		for (const auto& panel : m_Panels)
			panel->Update();
	}

	void PanelManager::CheckToggleActions()
	{
		for (const auto& panel : m_Panels)
			if (auto toggleKey = panel->GetToggleKey(); toggleKey && ImGuiUtils::IsCombinationPressed(toggleKey))
				panel->Toggle();
	}

	void PanelManager::DrawWindowMenuItems()
	{
		for (const auto& panel : m_Panels)
			if (ImGui::MenuItem(panel->m_Title.c_str(), GetShortcutName(panel), panel->IsOpen()))
				panel->Toggle();
	}

	const char* PanelManager::GetShortcutName(const Ref<PanelBase>& panel)
	{
		static auto shortcutCache = Dictionary<Ref<PanelBase>, String>();

		if (auto it = shortcutCache.find(panel); it != shortcutCache.end())
			return it->second.c_str();

		auto shortcut = panel->GetToggleKey();
		auto shortcutString = shortcut ? std::format("Ctrl+Alt+{}", ImGui::GetKeyName(shortcut)) : "";
		shortcutCache[panel] = shortcutString;

		return shortcutCache[panel].c_str();
	}
}

