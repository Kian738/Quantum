#include "Engine.h"
#include "Core.h"

DEFINE_LOG_CATEGORY_STATIC(Core);

namespace Quantum
{
	Engine::Engine()
	{
		LOG(Info, LogCore, "Initializing Engine...");

		if (GEngineConfig["Graphics"]["Enabled"].as<bool>(true))
		{
			LOG(Info, LogCore, "Initializing Graphics...");

			auto windowConfig = GEngineConfig["Graphics"]["MainWindow"];
			auto windowSpec = WindowSpecification(
				windowConfig["Title"].as<String>(App::GetName()),
				windowConfig["Width"].as<UInt32>(1280),
				windowConfig["Height"].as<UInt32>(720),
				windowConfig["VSync"].as<bool>(true),
				windowConfig["Resizable"].as<bool>(true),
				windowConfig["Fullscreen"].as<bool>(false)
			);

			m_Window = CreateScope<Window>(windowSpec);
			m_Window->ResizeEvent += [=](UInt32 width, UInt32 height) { m_IsMinimized = width == 0 || height == 0; };
		}
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
			m_Window->OnUpdate();

			if (!m_IsMinimized)
			{
			}

			// TODO: Do stuff
		}
	}

	void Engine::Stop()
	{
		m_IsRunning = false;
	}
}
