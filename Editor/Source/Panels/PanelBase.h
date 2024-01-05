#pragma once

#include <Core/Types.h>

#include <imgui.h>

namespace Quantum
{
	class PanelBase
	{
	protected:
		friend class MainPanel;
	private:
		String m_Title;
		bool m_IsOpen = false;
		bool m_NeedsFocus = false;
	public:
		PanelBase(StringView title, bool isOpen = false, bool needsFocus = false)
			: m_Title(title)
			, m_IsOpen(isOpen)
			, m_NeedsFocus(needsFocus)
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
			auto state = ImGui::Begin(m_Title.c_str(), &m_IsOpen);
			ImGui::PopStyleVar();

			if (state)
				Draw();

			ImGui::End();
		};

		virtual void Draw() = 0;

		bool IsOpen() const { return m_IsOpen; };

		void Open(bool focus = true) { m_IsOpen = true; m_NeedsFocus = focus; };
		void Close() { m_IsOpen = false; m_NeedsFocus = false; };
	};
}
