#pragma once

#include "Types.h"
#include "Window.h"
#include "Graphics/Camera/CameraController.h"

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
		Scope<CameraController> m_CameraController;

		int m_ExitCode = EXIT_SUCCESS;

		bool m_IsRunning = false;
		bool m_IsMinimized = false;
	public:
		Engine();
		~Engine();

		Window& GetWindow() { return *m_Window; };

		int Run();
		void Stop();
		void Crash();
	};
}
