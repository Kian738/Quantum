#pragma once

#include "Types.h"
#include "Window.h"
#include "App/AppContext.h"

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
		AppContext* m_AppContext;

		Scope<Window> m_Window;

		bool m_HasCrashed = false;

		bool m_IsRunning = false;
		bool m_IsMinimized = false;

		using Clock = std::chrono::high_resolution_clock;
	public:
		Engine(AppContext* appContext);
		~Engine();

		int GetExitCode() const { return static_cast<int>(m_HasCrashed); };
		Window& GetWindow() const { return *m_Window; };

		void Initialize();
		void Run();
		void Stop();
		void Crash();
	private:
		Clock::time_point GetCurrentTime();
	};
}
