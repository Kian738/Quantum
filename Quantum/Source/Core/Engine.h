#pragma once

#include "Types.h"
#include "Window.h"

namespace Quantum
{
	struct EngineConfig
	{
		bool IsGraphicsEnabled = true;
		// TODO: Impl: bool IsAudioEnabled = true;
	};

	class Engine
	{
	private:
		EngineConfig m_Config;

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
