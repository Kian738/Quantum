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
