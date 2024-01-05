#pragma once

#include <Core/Core.h>

#include "PanelBase.h"

namespace Quantum
{
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
		ConsolePanel()
			: PanelBase("Console")
			, m_AutoScroll(true)
		{};

		void Draw() override;
		void AddLog(LogLevel level, const String& message, const String& file, int line, const String& function);
	private:
		static ImVec4 GetLevelColor(LogLevel level);
	};
}
