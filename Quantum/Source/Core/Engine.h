#pragma once

#include "Types.h"
#include "Window.h"

namespace Quantum
{
	class Engine
	{
	private:
		Scope<Window> m_Window;
		bool m_IsRunning = false;
		bool m_IsMinimized = false;
	public:
		Engine();
		~Engine();

		void Run();
		void Stop();
	};
}
