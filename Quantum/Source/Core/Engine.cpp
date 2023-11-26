#include "Engine.h"

DEFINE_LOG_CATEGORY_STATIC(Core);

namespace Quantum
{
	Engine::Engine()
	{
		LOG(Info, LogCore, "Initializing Engine...");
	}

	Engine::~Engine()
	{
		LOG(Info, LogCore, "Shutting down Engine...");
	}

	void Engine::Run()
	{
		m_IsRunning = true;
		while (m_IsRunning)
		{
			// TODO: Do stuff
		}
	}
}
