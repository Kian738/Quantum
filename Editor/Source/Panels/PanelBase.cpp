#include "PanelBase.h"

#include "PanelManager.h"

namespace Quantum
{
	PanelBase::PanelBase(StringView title, bool isOpen, bool needsFocus)
		: m_Title(title)
		, m_IsOpen(isOpen)
		, m_NeedsFocus(needsFocus)
	{
		PanelManager::Register(this);
	}

	PanelBase::~PanelBase()
	{
		PanelManager::Unregister(this);
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

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 5));
		auto state = ImGui::Begin(m_Title.c_str(), &m_IsOpen);
		ImGui::PopStyleVar();

		if (state)
			Draw();

		ImGui::End();
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
}
