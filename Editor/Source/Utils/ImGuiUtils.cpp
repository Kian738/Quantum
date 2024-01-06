#include "ImGuiUtils.h"

namespace Quantum
{
	bool ImGuiUtils::IsKeyPressed(ImGuiKey key)
	{
		return ImGui::IsKeyPressed(key, false);
	}

	bool ImGuiUtils::IsCombinationPressed(ImGuiKey key)
	{
		return
			ImGui::IsKeyDown(ImGuiKey_LeftCtrl) &&
			ImGui::IsKeyDown(ImGuiKey_LeftAlt) &&
			IsKeyPressed(key);
	}
}
