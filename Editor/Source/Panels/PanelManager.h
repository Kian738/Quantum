#pragma once

#include <Core/Types.h>

#include "PanelBase.h"

namespace Quantum
{
	class PanelManager
	{
	private:
		static inline List<PanelBase*> m_Panels;
	public:
		static void Register(PanelBase* panel);
		static void Unregister(PanelBase* panel);

		static void DrawAll();
		static void CheckToggleActions();

		static void DrawWindowMenuItems();
	private:
		static const char* GetShortcutName(PanelBase* panel);
	};
}
