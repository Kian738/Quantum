#include "Gui.h"

void Quantum::EditorGui::RenderGui()
{
	auto windowFlags = ImGuiWindowFlags_NoMouseInputs | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	auto dockSpaceFlags = ImGuiDockNodeFlags_PassthruCentralNode;

	auto viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2());

	ImGui::Begin("Quantum", nullptr, windowFlags);

	ImGui::PopStyleVar(3);

	static auto& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		static auto dockSpaceID = ImGui::GetID("QuantumDockspace");
		ImGui::DockSpace(dockSpaceID, {}, dockSpaceFlags);
	}

	ImGui::End();

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit"))
				GEngine->Stop();

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("View"))
		{
			if (ImGui::MenuItem("Viewport", nullptr, &m_IsViewportShowing))
			{
				ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2());

				if (ImGui::Begin("Viewport", &m_IsViewportShowing))
				{
					ImGui::End();
				}

				ImGui::PopStyleVar();
			}

			if (ImGui::MenuItem("Stats", nullptr, &m_IsStatsShowing))
			{
				if (ImGui::Begin("Stats", &m_IsStatsShowing))
				{
					ImGui::Text("FPS: %.1f", io.Framerate);
					ImGui::Text("Frame Time: %.3f ms", 1000.0f / io.Framerate);
					ImGui::End();
				}
			}

			ImGui::EndMenu();
		}

		ImGui::BeginMainMenuBar();
	}
}
