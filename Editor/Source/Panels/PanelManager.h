#pragma once

#include <Core/Types.h>

#include "PanelBase.h"

namespace Quantum
{
	class PanelManager
	{
	private:
		static inline List<Ref<PanelBase>> m_Panels;
	public:
		static void Register(const Ref<PanelBase>& panel);

		static void DrawAll();
		static void CheckToggleActions();

		static void DrawWindowMenuItems();

		template <typename T, typename... Args>
		static Ref<T> Create(Args&&... args)
		{
			auto panel = CreateRef<T>(std::forward<Args>(args)...);
			Register(panel);
			return panel;
		}
	private:
		static const char* GetShortcutName(const Ref<PanelBase>& panel);
	};
}
