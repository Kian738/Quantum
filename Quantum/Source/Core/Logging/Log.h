#pragma once

#include "Core/Core.h"
#include "Console.h"
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
		static void PurgeLogFiles(StringView directory);
	};
}
