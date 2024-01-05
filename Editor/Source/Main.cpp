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
		auto windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		auto dockspaceFlags = ImGuiDockNodeFlags_None;
		
		auto viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);

		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2());

		if (dockspaceFlags & ImGuiDockNodeFlags_PassthruCentralNode)
			windowFlags |= ImGuiWindowFlags_NoBackground;

		ImGui::Begin("Quantum", nullptr, windowFlags);

		ImGui::PopStyleVar(3);

		auto& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			auto dockspaceID = ImGui::GetID("QuantumDockspace");
			ImGui::DockSpace(dockspaceID, {}, dockspaceFlags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit"))
					GEngine->Stop();

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::Begin("Stats");
		ImGui::Text("FPS: %.1f", io.Framerate);
		ImGui::Text("Frame Time: %.3f ms", 1000.0f / io.Framerate);
		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2());
		ImGui::Begin("Viewport");

		auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
		auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
		auto viewportOffset = ImGui::GetWindowPos();
		m_ViewportBounds[0] = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
		m_ViewportBounds[1] = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };
		
		auto viewportSize = ImGui::GetContentRegionAvail();
		m_ViewportSize = { viewportSize.x, viewportSize.y };

		auto frameBuffer = Renderer::GetFrameBuffer();
		frameBuffer->BindAsTexture();
		ImGui::Image(reinterpret_cast<void*>(frameBuffer->GetColorAttachment()), viewportSize, { 0, 1 }, { 1, 0 });

		ImGui::End();
		ImGui::PopStyleVar();

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
