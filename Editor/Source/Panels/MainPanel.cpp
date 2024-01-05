#include "MainPanel.h"

namespace Quantum
{
	void MainPanel::Update()
	{
		MainMenuBar();
		DockSpace();

		m_ConsolePanel->Draw();

		CheckToggleActions();
	}

	void MainPanel::CheckToggleActions()
	{
		if (IsCombinationPressed(ImGuiKey_C))
			m_ConsolePanel->m_IsOpen = !m_ConsolePanel->m_IsOpen;

		if (IsKeyPressed(ImGuiKey_F11))
			m_IsFullscreen = !m_IsFullscreen;
	}

	void MainPanel::MainMenuBar()
	{
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit", "Alt+F4"))
					GEngine->Stop();

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Edit"))
			{
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("View"))
			{
				ImGui::MenuItem("Fullscreen", "F11", &m_IsFullscreen);

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Windows"))
			{
				ImGui::MenuItem("Console", "Ctrl+Alt+C", &m_ConsolePanel->m_IsOpen);

				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}
	}

	void MainPanel::DockSpace() const
	{
		auto dockSpaceFlags = ImGuiDockNodeFlags(ImGuiDockNodeFlags_None);
		auto windowFlags = ImGuiWindowFlags(ImGuiWindowFlags_NoDocking);

		if (m_IsFullscreen)
		{
			auto viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);

			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2());

			windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
			dockSpaceFlags &= ~ImGuiDockNodeFlags_PassthruCentralNode;

		if (dockSpaceFlags & ImGuiDockNodeFlags_PassthruCentralNode)
			windowFlags |= ImGuiWindowFlags_NoBackground;

		ImGui::Begin("QuantumEngine", {}, dockSpaceFlags);

		if (m_IsFullscreen)
			ImGui::PopStyleVar(3);

		auto& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			static auto dockSpaceID = ImGui::GetID("QuantumDockspace");
			ImGui::DockSpace(dockSpaceID, {}, dockSpaceFlags);
		}

		ImGui::End();
	}

	bool MainPanel::IsKeyPressed(ImGuiKey key)
	{
		return ImGui::IsKeyPressed(key, false);
	}

	bool MainPanel::IsCombinationPressed(ImGuiKey key)
	{
		return
			ImGui::IsKeyDown(ImGuiKey_LeftCtrl) &&
			ImGui::IsKeyDown(ImGuiKey_LeftAlt) &&
			IsKeyPressed(key);
	}
}