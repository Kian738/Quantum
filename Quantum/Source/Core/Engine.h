#pragma once

#include "Core.h"
#include "Window.h"

namespace Quantum
{
	class Engine
	{
	private:
		Scope<Window> m_Window;
		bool m_IsRunning = false;
	public:
		Engine();
		~Engine();

		void Run();
	};
}
