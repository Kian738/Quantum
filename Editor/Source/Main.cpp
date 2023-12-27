#include <Core/Launch.h>
#include <Graphics/Camera/CameraController.h>
#include <Graphics/Renderer.h>
#include <Graphics/Resources/Model.h>

#include <imgui.h>

using namespace Quantum;

class EditorAppContext : public AppContext
{
private:
	Scope<CameraController> m_CameraController;
	float m_Fov = 45.0f;

	Ref<Model> m_HelicopterModel;
	Ref<Model> m_CarModel;
	Ref<Model> m_GasStationModel;
public:
	EditorAppContext() : AppContext("QuantumEngine")
	{
	}

	void Initialize() override
	{
		m_CameraController = CreateScope<CameraController>(Vector3(3.25f, 6.0f, -14.0f), Quaternion(0.0f, 0.0f, 0.0f, 1.0f));

		m_HelicopterModel = CreateRef<Model>("Models/Helicopter.fbx");
		m_CarModel = CreateRef<Model>("Models/Car.fbx");
		m_GasStationModel = CreateRef<Model>("Models/Gas_Station.fbx");

		auto& window = GEngine->GetWindow();
		window.SetCursorMode(CursorMode::Disabled);
		window.FocusEvent += [&](bool isFocused) { window.SetCursorMode(isFocused ? CursorMode::Disabled : CursorMode::Normal); };
	}

	void Update(float deltaTime) override
	{
		// TODO: Should be some sort of Actor so I dont have to call OnUpdate manually
		m_CameraController->OnUpdate(deltaTime);

		// TODO: Add Input lock to these
		if (Input::IsKeyPressed(Key::R)) // TODO: Fix shaders reloading 10 times
			Renderer::GetShaderLibrary()->ReloadAll();

		if (Input::IsKeyPressed(Key::F10))
			GEngine->Stop();

		static auto& window = GEngine->GetWindow();
		auto cursorMode = window.GetCursorMode();
		if (cursorMode == CursorMode::Disabled)
		{
			if (Input::IsKeyPressed(Key::Escape))
				window.SetCursorMode(CursorMode::Normal);
		}
		else if (Input::IsMouseButtonPressed(Mouse::ButtonLeft))
			window.SetCursorMode(CursorMode::Disabled);
	}

	// TODO: Move to seperate thread or something
	void Render() override
	{
		Renderer::Clear();
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
		auto& camera = m_CameraController->GetCamera();
		auto& cameraPosition = camera.GetPosition();
		auto& cameraRotation = camera.GetRotation();

		ImGui::Begin("QuantumEngine");
		ImGui::Text("FPS: %f", ImGui::GetIO().Framerate);
		ImGui::Text("Camera Position: %f, %f, %f", cameraPosition.x, cameraPosition.y, cameraPosition.z);
		ImGui::Text("Camera Rotation: %f, %f, %f", cameraRotation.x, cameraRotation.y, cameraRotation.z);
		ImGui::Text("Camera Fov: %f", m_Fov);
		ImGui::End();
	}

	void Shutdown() override
	{
	}
};

AppContext* GetAppContext()
{
	return new EditorAppContext;
}
