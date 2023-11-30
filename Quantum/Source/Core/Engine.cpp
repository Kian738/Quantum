#include "Engine.h"
#include "Core.h"
#include "Graphics/Renderer.h"

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
				windowConfig["Width"].as<UInt32>(0),
				windowConfig["Height"].as<UInt32>(0),
				windowConfig["VSync"].as<bool>(true),
				windowConfig["Resizable"].as<bool>(true),
				windowConfig["Fullscreen"].as<bool>(false)
			);

			m_Window = CreateScope<Window>(windowSpec);
			m_Window->MinimizeEvent += [=](bool isMinimized) { m_IsMinimized = isMinimized; };
			m_Window->CloseEvent += [=]() { Stop(); };

			Renderer::Initialize();
		}
	}

	Engine::~Engine()
	{
		LOG(Info, LogCore, "Shutting down Engine...");
	}

	int Engine::Run()
	{
		m_IsRunning = true;
		while (m_IsRunning)
		{
			m_Window->OnUpdate();

			if (!m_IsMinimized)
			{
				// TODO: OnUpdate and ImGui render for layers
			}

			m_Window->OnRender();
		}

		return m_ExitCode;
	}

	void Engine::Stop(bool isCrash)
	{
		if (isCrash)
			m_ExitCode = EXIT_FAILURE;

		m_IsRunning = false;
	}
}
