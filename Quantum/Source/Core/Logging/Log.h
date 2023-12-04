#pragma once

#include "Console.h"
#include "Core/Core.h"
#include "LogCategory.h"
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

		// TODO: Pass a lambda to the log function to avoid the string formatting if the log level is disabled
		static void LogAsync(LogLevel level, const LogCategory& category, Func<String()> formatFunc, StringView file, int line);
	private:
		static void LogInternal(LogLevel level, const LogCategory& category, Func<String()> formatFunc, StringView file, int line);

		static const char* LevelToName(LogLevel level);
		static const char* LevelToColor(LogLevel level);

		static String PathToRelative(StringView path);

		static void PurgeLogFiles();
	};
}
