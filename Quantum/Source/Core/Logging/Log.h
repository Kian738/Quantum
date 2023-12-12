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
		static inline std::ofstream s_LogFile;
		static inline Mutex s_LogFileMutex;
		static inline LogLevel s_LogLevel = LogLevel::Verbose;
		static inline bool s_IsInitialized = false;
	public:
		static void Initialize();
		static void Shutdown();

		static void LogAsync(LogLevel level, const LogCategory& category, Func<String()> formatFunc, StringView file, int line);
	private:
		static void LogInternal(LogLevel level, const LogCategory& category, String message, StringView file, int line);

		static LogLevel NameToLevel(const char* name);
		static const char* LevelToName(LogLevel level);
		static const char* LevelToColor(LogLevel level);

		static String PathToRelative(StringView path);

		static void PurgeLogFiles();
	};
}
