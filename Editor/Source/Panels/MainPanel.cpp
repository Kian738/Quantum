#include "MainPanel.h"

namespace Quantum
{
	MainPanel::MainPanel()
		: m_ConsolePanel(CreateRef<ConsolePanel>())
	{
	}

	void MainPanel::Update()
	{
		MainMenuBar();
		DockSpace();

		PanelManager::DrawAll();

		// TODO: Remove this test code
		ImGui::ShowDemoWindow();

		static auto num = 500;
		static auto swap = false;
		{
			if (num >= 70)
			{
				if (swap)
					m_ConsolePanel->AddLog(LogLevel::Info, "Bruh", __FILE__, __LINE__, __FUNCTION__);
				else
					m_ConsolePanel->AddLog(LogLevel::Warning, "Hello World!", __FILE__, __LINE__, __FUNCTION__);	
				swap = !swap;
				num = 0;
			}
			else
				num++;
		}
		// TODO: Test code end

		CheckToggleActions();
	}

	void MainPanel::CheckToggleActions()
	{
		if (ImGuiUtils::IsKeyPressed(ImGuiKey_F11))
			m_IsFullscreen = !m_IsFullscreen;

		PanelManager::CheckToggleActions();
	}

	void MainPanel::MainMenuBar()
	{
		// TODO: Add icons to menu items
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit", "Alt+F4"))
					GEngine->Stop();

				ImGui::EndMenu();
			}

			// TODO: Implement keyboard shortcuts
			if (ImGui::BeginMenu("Edit"))
			{
				if (ImGui::MenuItem("Undo", "Ctrl+Z"))
					LOG(Warning, LogCommon, "Undo not implemented");

				if (ImGui::MenuItem("Redo", "Ctrl+Y"))
					LOG(Warning, LogCommon, "Redo not implemented");

				ImGui::Separator();

				if (ImGui::MenuItem("Cut", "Ctrl+X"))
					LOG(Warning, LogEditor, "Cut not implemented");

				if (ImGui::MenuItem("Copy", "Ctrl+C"))
					LOG(Warning, LogCommon, "Copy not implemented");

				if (ImGui::MenuItem("Paste", "Ctrl+V"))
					LOG(Warning, LogCommon, "Paste not implemented");

				if (ImGui::MenuItem("Duplicate", "Ctrl+D"))
					LOG(Warning, LogCommon, "Duplicate not implemented");

				if (ImGui::MenuItem("Delete", "Del"))
					LOG(Warning, LogCommon, "Delete not implemented")

				ImGui::Separator();

				if (ImGui::MenuItem("Select All", "Ctrl+A"))
					LOG(Warning, LogCommon, "Select All not implemented");

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("View"))
			{
				// TODO: Make this work
				ImGui::MenuItem("Fullscreen", "F11", &m_IsFullscreen);

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Windows"))
			{
				PanelManager::DrawWindowMenuItems();

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

		ImGui::Begin("QuantumEngine", {}, windowFlags);

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
}