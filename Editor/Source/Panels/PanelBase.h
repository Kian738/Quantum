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

		virtual void Draw() = 0;

		bool IsOpen() const { return m_IsOpen; };

		void Open(bool focus = true);
		void Close();
		void Toggle();
	private:
		virtual ImGuiKey GetToggleKey() const { return ImGuiKey_None; };
		virtual ImGuiWindowFlags GetWindowFlags() const { return ImGuiWindowFlags_None; };

		virtual void SetStyleVars() const {};
		virtual void ResetStyleVars() const {};
	protected:
		void Update();

		friend class PanelManager;
	};
}
