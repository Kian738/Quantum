#include "ImGuiContext.h"

#include "Core/Core.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

namespace Quantum
{
	ImGuiContext::ImGuiContext()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		auto& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleFonts;
		io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleViewports;

		// TODO: See if I should enable this or not: io.ConfigViewportsNoAutoMerge = true;

		io.IniFilename = nullptr;
		io.LogFilename = nullptr;

		ImGui::StyleColorsDark();

		SetTheme();

		auto& window = GEngine->GetWindow();

		ImGui_ImplGlfw_InitForOpenGL(window.GetNativeWindow(), true);
		ImGui_ImplOpenGL3_Init("#version 460");

		window.ResizeEvent += [&](UInt32 width, UInt32 height)
			{
				ImGui::GetIO().DisplaySize = ImVec2(width, height);
			};
	}

	ImGuiContext::~ImGuiContext()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiContext::BeginFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiContext::EndFrame()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		static auto& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			auto backupCurrentContext = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backupCurrentContext);
		}
	}

	void ImGuiContext::SetTheme()
	{
		auto& style = ImGui::GetStyle();
		style.WindowPadding = { 8.0f, 8.0f };
		style.WindowRounding = 1.0f;

		style.FramePadding = { 4.0f, 3.0f };
		style.FrameRounding = 1.0f;

		style.ItemSpacing = { 8.0f, 4.0f };
		style.ItemInnerSpacing = { 4.0f, 4.0f };

		style.IndentSpacing = 21.0f;

		style.ScrollbarSize = 14.0f;
		style.ScrollbarRounding = 1.0f;

		style.GrabMinSize = 8.0f;
		style.GrabRounding = 1.0f;

		style.TabRounding = 1.0f;

		style.WindowTitleAlign = { 0.0f, 0.5f };

		style.DisplaySafeAreaPadding = { 3.0f, 3.0f };

		style.AntiAliasedLines = true;
		style.AntiAliasedFill = true;

		style.WindowBorderSize = 1.0f;
		style.ChildBorderSize = 1.0f;
		style.PopupBorderSize = 1.0f;
		style.FrameBorderSize = 1.0f;
		style.TabBorderSize = 1.0f;

		style.WindowMenuButtonPosition = ImGuiDir_Right;
		
		auto& colors = style.Colors;
		colors[ImGuiCol_Text] = { 0.90f, 0.90f, 0.90f, 1.00f };
		colors[ImGuiCol_TextDisabled] = { 0.60f, 0.60f, 0.60f, 1.00f };

		colors[ImGuiCol_WindowBg] = { 0.10f, 0.10f, 0.10f, 1.00f };
		colors[ImGuiCol_ChildBg] = { 0.10f, 0.10f, 0.10f, 1.00f };
		colors[ImGuiCol_PopupBg] = { 0.10f, 0.10f, 0.10f, 1.00f };

		colors[ImGuiCol_Border] = { 0.50f, 0.50f, 0.50f, 0.50f };
		colors[ImGuiCol_BorderShadow] = { 0.00f, 0.00f, 0.00f, 0.00f };

		colors[ImGuiCol_FrameBg] = { 0.30f, 0.30f, 0.30f, 0.54f };
		colors[ImGuiCol_FrameBgHovered] = { 0.40f, 0.40f, 0.40f, 0.40f };
		colors[ImGuiCol_FrameBgActive] = { 0.45f, 0.45f, 0.45f, 0.67f };

		colors[ImGuiCol_TitleBg] = { 0.27f, 0.27f, 0.54f, 0.83f };
		colors[ImGuiCol_TitleBgActive] = { 0.32f, 0.32f, 0.63f, 0.87f };
		colors[ImGuiCol_TitleBgCollapsed] = { 0.40f, 0.40f, 0.80f, 0.20f };

		colors[ImGuiCol_MenuBarBg] = { 0.40f, 0.40f, 0.55f, 0.80f };

		colors[ImGuiCol_ScrollbarBg] = { 0.20f, 0.25f, 0.30f, 0.60f };
		colors[ImGuiCol_ScrollbarGrab] = { 0.40f, 0.40f, 0.80f, 0.30f };
		colors[ImGuiCol_ScrollbarGrabHovered] = { 0.40f, 0.40f, 0.80f, 0.40f };
		colors[ImGuiCol_ScrollbarGrabActive] = { 0.41f, 0.39f, 0.80f, 0.60f };

		colors[ImGuiCol_CheckMark] = { 0.90f, 0.90f, 0.90f, 0.50f };

		colors[ImGuiCol_SliderGrab] = { 0.40f, 0.40f, 0.80f, 0.30f };
		colors[ImGuiCol_SliderGrabActive] = { 0.41f, 0.39f, 0.80f, 0.60f };

		colors[ImGuiCol_Button] = { 0.35f, 0.40f, 0.61f, 0.62f };
		colors[ImGuiCol_ButtonHovered] = { 0.40f, 0.48f, 0.71f, 0.79f };
		colors[ImGuiCol_ButtonActive] = { 0.46f, 0.54f, 0.80f, 1.00f };

		colors[ImGuiCol_Header] = { 0.40f, 0.40f, 0.90f, 0.45f };
		colors[ImGuiCol_HeaderHovered] = { 0.45f, 0.45f, 0.90f, 0.80f };
		colors[ImGuiCol_HeaderActive] = { 0.53f, 0.53f, 0.87f, 0.80f };

		colors[ImGuiCol_Separator] = { 0.50f, 0.50f, 0.50f, 0.60f };
		colors[ImGuiCol_SeparatorHovered] = { 0.60f, 0.60f, 0.70f, 0.70f };
		colors[ImGuiCol_SeparatorActive] = { 0.70f, 0.70f, 0.90f, 0.80f };

		colors[ImGuiCol_ResizeGrip] = { 0.50f, 0.50f, 0.50f, 0.60f };
		colors[ImGuiCol_ResizeGripHovered] = { 0.60f, 0.60f, 0.70f, 0.70f };
		colors[ImGuiCol_ResizeGripActive] = { 0.70f, 0.70f, 0.90f, 0.80f };

		colors[ImGuiCol_Tab] = { 0.40f, 0.40f, 0.90f, 0.45f };
		colors[ImGuiCol_TabHovered] = { 0.45f, 0.45f, 0.90f, 0.80f };
		colors[ImGuiCol_TabActive] = { 0.53f, 0.53f, 0.87f, 0.80f };
		colors[ImGuiCol_TabUnfocused] = { 0.40f, 0.40f, 0.90f, 0.45f };
		colors[ImGuiCol_TabUnfocusedActive] = { 0.53f, 0.53f, 0.87f, 0.80f };

		colors[ImGuiCol_DockingPreview] = { 0.26f, 0.59f, 0.98f, 0.70f };
		colors[ImGuiCol_DockingEmptyBg] = { 0.20f, 0.20f, 0.20f, 1.00f };

		colors[ImGuiCol_PlotLines] = { 0.61f, 0.61f, 0.61f, 1.00f };
		colors[ImGuiCol_PlotLinesHovered] = { 1.00f, 0.43f, 0.35f, 1.00f };
		colors[ImGuiCol_PlotHistogram] = { 0.90f, 0.70f, 0.00f, 1.00f };
		colors[ImGuiCol_PlotHistogramHovered] = { 1.00f, 0.60f, 0.00f, 1.00f };

		colors[ImGuiCol_TableHeaderBg] = { 0.27f, 0.27f, 0.54f, 0.85f };
		colors[ImGuiCol_TableBorderStrong] = { 0.31f, 0.31f, 0.70f, 1.00f };
		colors[ImGuiCol_TableBorderLight] = { 0.26f, 0.26f, 0.26f, 1.00f };
		colors[ImGuiCol_TableRowBg] = { 0.00f, 0.00f, 0.00f, 0.00f };
		colors[ImGuiCol_TableRowBgAlt] = { 1.00f, 1.00f, 1.00f, 0.07f };

		colors[ImGuiCol_TextSelectedBg] = { 0.26f, 0.59f, 0.98f, 0.35f };

		colors[ImGuiCol_DragDropTarget] = { 1.00f, 1.00f, 0.00f, 0.90f };

		colors[ImGuiCol_NavHighlight] = { 0.26f, 0.59f, 0.98f, 1.00f };
		colors[ImGuiCol_NavWindowingHighlight] = { 1.00f, 1.00f, 1.00f, 0.70f };
		colors[ImGuiCol_NavWindowingDimBg] = { 0.80f, 0.80f, 0.80f, 0.20f };

		colors[ImGuiCol_ModalWindowDimBg] = { 0.80f, 0.80f, 0.80f, 0.35f };
	}
}
