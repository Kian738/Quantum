#include "Engine.h"

#include "Core.h"
#include "Graphics/RenderCommand.h"
#include "Graphics/Renderer.h"

#undef GetCurrentTime

DEFINE_LOG_CATEGORY_STATIC(Core);

namespace Quantum
{
	Engine::Engine(AppContext* appContext)
		: m_AppContext(appContext)
	{
		m_Config.IsGraphicsEnabled = GEngineConfig["Graphics"]["Enabled"].as<bool>(true);
	}

	Engine::~Engine()
	{
		LOG(Info, LogCore, "Shutting down Engine...");

		m_AppContext->Shutdown();

		if (m_Config.IsGraphicsEnabled)
		{
			LOG(Info, LogCore, "Shutting down Graphics...");

			Renderer::Shutdown();

			Input::Shutdown();
		}
	}

	void Engine::Initialize()
	{
		LOG(Info, LogCore, "Initializing Engine...");

		if (m_Config.IsGraphicsEnabled)
		{
			LOG(Info, LogCore, "Initializing Graphics...");

			auto windowConfig = GEngineConfig["Graphics"]["MainWindow"];
			auto windowSpec = WindowSpecification(
				windowConfig["Title"].as<String>(std::format(
					"{}{}",
					App::GetName(),
					Environment::IsDebug() ? " (Debug)" : ""
				)),
				windowConfig["Width"].as<UInt32>(0),
				windowConfig["Height"].as<UInt32>(0),
				windowConfig["VSync"].as<bool>(true),
				windowConfig["Resizable"].as<bool>(true),
				windowConfig["Fullscreen"].as<bool>(false)
				// TODO: CursorMode
			); // TODO: Check why values arent loaded correctly

			m_Window = CreateScope<Window>(windowSpec);
			m_Window->MinimizeEvent += [this](bool isMinimized) { m_IsMinimized = isMinimized; };
			m_Window->CloseEvent += [this]() { Stop(); };

			Input::Initialize();

			Renderer::Initialize();
		}

		m_AppContext->Initialize();
	}

	void Engine::Run()
	{
		auto lastTime = GetCurrentTime();

		m_IsRunning = true;
		while (m_IsRunning)
		{
			auto currentTime = GetCurrentTime();
			auto deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
			lastTime = currentTime;

			if (m_Config.IsGraphicsEnabled)
			{
				Input::OnUpdate();

				m_Window->OnUpdate();

				m_AppContext->Update(deltaTime);

				if (!m_IsMinimized)
				{
					m_AppContext->Render();
					m_Window->OnRender();
				}
			}
		}
	}

	void Engine::Stop()
	{
		m_IsRunning = false;

		LOG(Info, LogCore, "Exiting with code: {}", GetExitCode());
	}

	void Engine::Crash()
	{
		m_HasCrashed = true;
		Stop();
	}

	Engine::Clock::time_point Engine::GetCurrentTime()
	{
		return Clock::now();
	}
}
