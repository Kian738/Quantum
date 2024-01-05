#include "ConsolePanel.h"

namespace Quantum
{
	void ConsolePanel::Draw()
	{
		if (ImGui::Button("Clear"))
			m_Messages.Clear();
		ImGui::SameLine();
		ImGui::Checkbox("Auto Scroll", &m_AutoScroll);

		ImGui::Separator();

		auto height = ImGui::GetContentRegionAvail().y - ImGui::GetTextLineHeightWithSpacing(); // TODO: Up to the test
		ImGui::BeginChild("ScrollingRegion", { 0, -height }, false, ImGuiWindowFlags_HorizontalScrollbar);

		for (const auto& message : m_Messages)
		{
			auto level = message.Level;
			auto levelName = Log::GetLevelName(level);
			auto levelColor = GetLevelColor(level);

			// TODO: Put icon here
			ImGui::PushStyleColor(ImGuiCol_Text, levelColor);
			ImGui::TextWrapped("[%s] %s", levelName, message.Message.c_str());
			ImGui::PopStyleColor();

			if (message.Count > 1)
			{
				ImGui::SameLine();
				ImGui::PushStyleColor(ImGuiCol_Text, { 0.6f, 0.6f, 0.6f, 1.0f });
				ImGui::TextWrapped(" (%d)", message.Count);
				ImGui::PopStyleColor();
			}

			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::TextWrapped("Location: %s:%d", message.File.c_str(), message.Line);
				ImGui::TextWrapped("Function: %s", message.Function.c_str());
				ImGui::EndTooltip();
			}

			ImGui::Separator();

			if (m_AutoScroll)
				ImGui::SetScrollHereY(1.0f);
		}

		ImGui::EndChild();
	}

	void ConsolePanel::AddLog(LogLevel level, const String& message, const String& file, int line, const String& function)
	{
		static auto hasher = std::hash<String>();
		static UInt64 previousHash;

		auto hash = hasher(message);
		if (hash == previousHash)
		{
			m_Messages.GetBack().Count++;
			return;
		}

		previousHash = hash;

		m_Messages.Emplace({ level, message, 1, file, line, function });
	}

	ImVec4 ConsolePanel::GetLevelColor(LogLevel level)
	{
		switch (level)
		{
		case LogLevel::Verbose:
			return { 0.5f, 0.5f, 0.5f, 1.0f };
		case LogLevel::Debug:
			return { 0.0f, 0.5f, 1.0f, 1.0f };
		case LogLevel::Info:
			return { 0.0f, 1.0f, 0.0f, 1.0f };
		case LogLevel::Warning:
			return { 1.0f, 1.0f, 0.0f, 1.0f };
		case LogLevel::Error:
			return { 1.0f, 0.0f, 0.0f, 1.0f };
		}

		return { 1.0f, 1.0f, 1.0f, 1.0f };
	}
}
