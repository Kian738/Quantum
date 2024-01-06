#pragma once

#include <Core/Types.h>

#include <imgui.h>

namespace Quantum
{
	class PanelBase
	{
	private:
		String m_Title;
		bool m_IsOpen = false;
		bool m_NeedsFocus = false;
	public:
		PanelBase(StringView title, bool isOpen = false, bool needsFocus = false);
		virtual ~PanelBase();

		void Update();

		virtual void Draw() = 0;

		bool IsOpen() const { return m_IsOpen; };

		void Open(bool focus = true);
		void Close();
		void Toggle();
	};
}
