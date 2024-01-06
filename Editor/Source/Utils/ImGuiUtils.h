#pragma once

#include <imgui.h>

namespace Quantum
{
	class ImGuiUtils
	{
	public:
		static bool IsKeyPressed(ImGuiKey key);
		static bool IsCombinationPressed(ImGuiKey key);
	};
}
