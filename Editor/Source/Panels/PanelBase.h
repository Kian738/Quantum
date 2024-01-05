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
		PanelBase(StringView title)
			: m_Title(title)
		{};

		virtual void Update(float deltaTime)
		{
			if (!m_IsOpen)
			{
				m_NeedsFocus = true;
				return;
			}

			if (m_NeedsFocus)
			{
				ImGui::SetNextWindowFocus();
				m_NeedsFocus = false;
			}

			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 5));
			ImGui::Begin(m_Title.c_str(), &m_IsOpen);
		}

		virtual void OnImGuiRender() = 0;

		void Open(bool focus = true) { m_IsOpen = true; m_NeedsFocus = focus; };
		void Close() { m_IsOpen = false; m_NeedsFocus = false; }
	};
}
