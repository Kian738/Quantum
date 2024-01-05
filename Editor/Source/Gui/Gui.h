#pragma once

#include <Core/Core.h>
#include <imgui.h>

namespace Quantum
{
	class EditorGui
	{
	private:

		bool m_IsViewportShowing = false;
		bool m_IsStatsShowing = false;

	public:

		void RenderGui();


	};
}