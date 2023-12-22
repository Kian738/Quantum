#include <Core/Launch.h>
#include <Graphics/Camera/CameraController.h>
#include <Graphics/Renderer.h>
#include <Graphics/Resources/Model.h>

using namespace Quantum;

class EditorAppContext : public AppContext
{
private:
	Scope<CameraController> m_CameraController;

	Ref<Model> m_HelicopterModel;
	Ref<Model> m_CarModel;
	Ref<Model> m_GasStationModel;
public:
	EditorAppContext() : AppContext("QuantumEngine")
	{
	}

	void Initialize() override
	{
		m_CameraController = CreateScope<CameraController>();

		m_HelicopterModel = CreateRef<Model>("Models/Helicopter.fbx");
		m_CarModel = CreateRef<Model>("Models/Car.fbx");
		m_GasStationModel = CreateRef<Model>("Models/Gas_Station.fbx");
	}

	void Update(float deltaTime) override
	{
		m_CameraController->OnUpdate(deltaTime);

		if (Input::IsKeyPressed(Key::R)) // TODO: Fix shaders reloading 10 times
			Renderer::GetShaderLibrary()->ReloadAll();

		if (Input::IsKeyPressed(Key::Escape))
			GEngine->Stop();

		if (Input::IsKeyDown(Key::Minus))
			m_CameraController->SetFov(m_CameraController->GetFov() - 0.3f);
		if (Input::IsKeyDown(Key::Equal))
			m_CameraController->SetFov(m_CameraController->GetFov() + 0.3f);
	}

	void Render() override
	{
		Renderer::Clear();
		Renderer::BeginScene(m_CameraController->GetCamera());

		static auto baseTransform = Matrix4D(1.0f);

		static auto helicopterTransform = glm::scale(glm::translate(baseTransform, { 0.0f, 0.0f, 0.0f }), Vector3D(0.01f));
		static auto carTransform = glm::translate(
			baseTransform,
			{ 5.0f, 0.0f, 0.0f }
		) * glm::rotate(
			baseTransform,
			glm::radians(-90.0f),
			{ 1.0f, 0.0f, 0.0f }
		);
		static auto gasStationTransform = glm::scale(glm::translate(baseTransform, { -5.0f, 0.0f, 0.0f }), Vector3D(0.01f));

		Renderer::Submit(*m_HelicopterModel, helicopterTransform);
		Renderer::Submit(*m_CarModel, carTransform);
		Renderer::Submit(*m_GasStationModel, gasStationTransform);

		Renderer::EndScene();
	}

	void Shutdown() override
	{
	}
};

AppContext* GetAppContext()
{
	return new EditorAppContext;
}
