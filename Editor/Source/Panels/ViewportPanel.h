#pragma once

#include "EditorCore.h"

namespace Quantum
{
	class ViewportPanel : public PanelBase
	{
	public:
		ViewportPanel();

		void Draw() override;
	private:
		ImGuiWindowFlags GetWindowFlags() const override { return ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_MenuBar; };

		void SetStyleVars() const override;
		void ResetStyleVars() const override;
	};
}
