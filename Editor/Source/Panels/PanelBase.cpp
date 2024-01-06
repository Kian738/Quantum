#include "PanelBase.h"

#include "PanelManager.h"

namespace Quantum
{
	PanelBase::PanelBase(StringView title, bool isOpen, bool needsFocus)
		: m_Title(title)
		, m_IsOpen(isOpen)
		, m_NeedsFocus(needsFocus)
	{
	}

	void PanelBase::Open(bool focus)
	{
		m_IsOpen = true;
		m_NeedsFocus = focus;
	}

	void PanelBase::Close()
	{
		m_IsOpen = false;
		m_NeedsFocus = false;
	}

	void PanelBase::Toggle()
	{
		m_IsOpen = !m_IsOpen;
		m_NeedsFocus = m_IsOpen;
	}

	void PanelBase::Update()
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

		ApplyWindowSettings();
		auto state = ImGui::Begin(m_Title.c_str(), &m_IsOpen, GetWindowFlags());
		ResetWindowSettings();

		if (state)
			Draw();

		ImGui::End();
	}
}
