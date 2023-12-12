#include "Engine.h"

#include "Core.h"
#include "Graphics/RenderCommand.h"
#include "Graphics/Renderer.h"

#undef GetCurrentTime

DEFINE_LOG_CATEGORY_STATIC(Core);

namespace Quantum
{
	Engine::Engine()
	{
		m_Config.IsGraphicsEnabled = GEngineConfig["Graphics"]["Enabled"].as<bool>(true);
	}

	Engine::~Engine()
	{
		LOG(Info, LogCore, "Shutting down Engine...");

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
				windowConfig["Title"].as<String>(App::GetName()),
				windowConfig["Width"].as<UInt32>(0),
				windowConfig["Height"].as<UInt32>(0),
				windowConfig["VSync"].as<bool>(true),
				windowConfig["Resizable"].as<bool>(true),
				windowConfig["Fullscreen"].as<bool>(false)
			);

			m_Window = CreateScope<Window>(windowSpec);
			m_Window->MinimizeEvent += [this](bool isMinimized) { m_IsMinimized = isMinimized; };
			m_Window->CloseEvent += [this]() { Stop(); };

			Input::Initialize();

			Renderer::Initialize();

			m_CameraController = CreateScope<CameraController>();
		}
	}

	void Engine::Run()
	{
		// TODO: Remove this
		auto model = CreateRef<Model>("Models/Test.fbx");

		auto lastTime = GetCurrentTime();

		m_IsRunning = true;
		while (m_IsRunning)
		{
			auto currentTime = GetCurrentTime();
			auto deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
			lastTime = currentTime;

			if (m_Config.IsGraphicsEnabled)
			{
				m_Window->OnUpdate();

				m_CameraController->OnUpdate(deltaTime);

				RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
				RenderCommand::Clear();

				if (!m_IsMinimized)
				{
					Renderer::BeginScene(m_CameraController->GetCamera());
					
					// TODO: Render models from scene
					{
						auto modelTransform = glm::translate(Matrix4D(1.0f), Vector3D(0.0f));
						Renderer::Submit(*model, modelTransform);
					}

					Renderer::EndScene();
				}

				m_Window->OnRender();
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
