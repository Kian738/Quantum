#pragma once

#include "Console.h"
#include "Core/Core.h"
#include "LogCategory.h"
#include <fstream>
#include <print>

namespace Quantum
{
	enum LogLevel : UInt8
	{
		Verbose,
		Debug,
		Info,
		Warning,
		Error,
		Fatal
	};

	class Log
	{
	private:
		static std::ofstream m_LogFile;
		static bool m_IsInitialized;
	public:
		static void Initialize();
		static void Shutdown();

		static void LogInternal(LogLevel level, const LogCategory& category, StringView formatedMessage, StringView file, int line);
	private:
		static const char* LevelToName(LogLevel level);
		static const char* LevelToColor(LogLevel level);

		static String PathToRelative(StringView path);

		static void PurgeLogFiles();
	};
}
