#pragma once

#include "Core/Types.h"

namespace Quantum
{
	class ImGuiContext
	{
	public:
		ImGuiContext();
		~ImGuiContext();

		void BeginFrame();
		void EndFrame();
	};
}
