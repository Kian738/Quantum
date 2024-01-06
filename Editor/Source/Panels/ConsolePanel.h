#pragma once

#include "EditorCore.h"

namespace Quantum
{
	// TODO: Eventually make this work with several log sinks
	class ConsolePanel : public PanelBase
	{
	protected:
		struct Message
		{
			LogLevel Level;
			String Message;
			int Count;

			String File;
			int Line;
			String Function;
		};
	private:
		bool m_AutoScroll;
		CircularBuffer<Message, 100> m_Messages;
	public:
		ConsolePanel();

		void Draw() override;
		void AddLog(LogLevel level, const String& message, const String& file, int line, const String& function);
	private:
		ImGuiKey GetToggleKey() const override { return ImGuiKey_C; };

		static ImVec4 GetLevelColor(LogLevel level);
	};
}
