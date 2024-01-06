#include "PanelManager.h"

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

	void PanelManager::UpdateAll()
	{
		for (auto panel : m_Panels)
			panel->Update();
	}
}

