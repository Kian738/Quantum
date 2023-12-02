#include "Engine.h"

#include "Core.h"
#include "Graphics/RenderCommand.h"
#include "Graphics/Renderer.h"

DEFINE_LOG_CATEGORY_STATIC(Core);

namespace Quantum
{
	Engine::Engine()
	{
		LOG(Info, LogCore, "Initializing Engine...");

		m_Config.IsGraphicsEnabled = GEngineConfig["Graphics"]["Enabled"].as<bool>(true);
		if (m_Config.IsGraphicsEnabled)
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

			m_CameraController = CreateScope<CameraController>();
		}
	}

	Engine::~Engine()
	{
		LOG(Info, LogCore, "Shutting down Engine...");

		if (m_Config.IsGraphicsEnabled)
		{
			LOG(Info, LogCore, "Shutting down Graphics...");

			Renderer::Shutdown();
		}
	}

	int Engine::Run()
	{
		m_IsRunning = true;
		while (m_IsRunning)
		{
			if (m_Config.IsGraphicsEnabled)
			{
				m_Window->OnUpdate();

				RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
				RenderCommand::Clear();

				if (!m_IsMinimized)
				{
					Renderer::BeginScene(m_CameraController->GetCamera());
					// TODO: OnUpdate and ImGui render for modules
					Renderer::EndScene();
				}

				m_Window->OnRender();
			}
		}

		return m_ExitCode;
	}

	void Engine::Stop()
	{
		m_IsRunning = false;

		LOG(Info, LogCore, "Exiting with code: {}", m_ExitCode);
	}

	void Engine::Crash()
	{
		m_ExitCode = EXIT_FAILURE;
		Stop();
	}
}
