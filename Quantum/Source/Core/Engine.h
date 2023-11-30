#pragma once

#include "Types.h"
#include "Window.h"

namespace Quantum
{
	class Engine
	{
	private:
		Scope<Window> m_Window;
		int m_ExitCode = EXIT_SUCCESS;
		bool m_IsRunning = false;
		bool m_IsMinimized = false;
	public:
		Engine();
		~Engine();

		int Run();
		void Stop(bool isCrash = false);
	};
}
