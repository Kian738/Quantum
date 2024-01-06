#include <Core/Launch.h>
#include <Graphics/Camera/CameraController.h>
#include <Graphics/Renderer.h>
#include <Graphics/Resources/Model.h>

#include "Panels/MainPanel.h"

namespace Quantum
{
	class EditorAppContext : public AppContext
	{
	private:
		Scope<MainPanel> m_MainPanel;
		Scope<CameraController> m_CameraController;

		Ref<Model> m_HelicopterModel;
		Ref<Model> m_CarModel;
		Ref<Model> m_GasStationModel;

		Vector2 m_ViewportBounds[2] = {};
		Vector2 m_ViewportSize = {};
	public:
		EditorAppContext() : AppContext("QuantumEngine")
		{
		}

		void Initialize() override
		{
			m_MainPanel = CreateScope<MainPanel>();
			m_CameraController = CreateScope<CameraController>(Vector3(3.25f, 3.0f, -6.0f), Quaternion(0.0f, 0.0f, 0.0f, 1.0f));

			m_HelicopterModel = CreateRef<Model>("Models/Helicopter.fbx");
			m_CarModel = CreateRef<Model>("Models/Car.fbx");
			m_GasStationModel = CreateRef<Model>("Models/Gas_Station.fbx");

			// TODO: Check if its focusing the viewport
			/*auto& window = GEngine->GetWindow();
			window.SetCursorMode(CursorMode::Disabled);
			window.FocusEvent += [&](bool isFocused) { window.SetCursorMode(isFocused ? CursorMode::Disabled : CursorMode::Normal); };*/ // TODO: InputManager should handle this
		}

		void Update(float deltaTime) override
		{
			// TODO: Should be some sort of Actor so I dont have to call OnUpdate manually
			m_CameraController->OnUpdate(deltaTime);

			// TODO: Add Input lock to these | Or just move to imgui
			if (Input::IsKeyPressed(Key::R)) // TODO: Fix shaders reloading 10 times
				Renderer::GetShaderLibrary()->ReloadAll();

			// TODO: Move to InputManager (Lock and normal mode)
			/*static auto& window = GEngine->GetWindow();
			auto cursorMode = window.GetCursorMode();
			if (cursorMode == CursorMode::Disabled)
			{
				if (Input::IsKeyPressed(Key::Escape))
					window.SetCursorMode(CursorMode::Normal);
			}
			else if (Input::IsMouseButtonPressed(Mouse::ButtonLeft))
				window.SetCursorMode(CursorMode::Disabled);*/
		}

		// TODO: Move to seperate thread or something | Use SceneRenderer class
		void Render() override
		{
			Renderer::BeginScene(m_CameraController->GetCamera());

			static auto baseTransform = Matrix4(1.0f);

			static auto helicopterTransform = glm::scale(glm::translate(baseTransform, { 0.0f, 0.0f, 0.0f }), Vector3(0.01f));
			static auto carTransform = glm::translate(
				baseTransform,
				{ 5.0f, 0.0f, 0.0f }
			) * glm::rotate(
				baseTransform,
				glm::radians(-90.0f),
				{ 1.0f, 0.0f, 0.0f }
			);
			static auto gasStationTransform = glm::scale(glm::translate(baseTransform, { -5.0f, 0.0f, 0.0f }), Vector3(0.01f));

			Renderer::Submit(*m_HelicopterModel, helicopterTransform);
			Renderer::Submit(*m_CarModel, carTransform);
			Renderer::Submit(*m_GasStationModel, gasStationTransform);

			Renderer::EndScene();
		}

		void RenderImGui() override
		{
			m_MainPanel->Update();
		}

		void Shutdown() override
		{
		}
	};
}

Quantum::AppContext* GetAppContext()
{
	return new Quantum::EditorAppContext;
}
