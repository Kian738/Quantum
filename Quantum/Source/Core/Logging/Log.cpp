#include "Log.h"
#include "LogMacros.h"
#include "Core/Config.h"
#include "Core/DateTime.h"
#include <iostream>
#include <filesystem>

// TODO: Async logging
namespace Quantum
{
	std::ofstream Log::m_LogFile = {};
	bool Log::m_IsInitialized = false;

	namespace Utils
	{
		static const char* LevelToName(LogLevel level)
		{
			switch (level)
			{
			case LogLevel::Verbose:
				return "Verbose";
			case LogLevel::Debug:
				return "Debug";
			case LogLevel::Info:
				return "Info";
			case LogLevel::Warning:
				return "Warning";
			case LogLevel::Error:
				return "Error";
			case LogLevel::Fatal:
				return "Fatal";
			default:
				return "Unknown";
			}
		}

		static const char* LevelToColor(LogLevel level)
		{
			switch (level)
			{
			case Verbose:
				return "\33[1;30m";
			case Debug:
				return "\33[34m";
			case Info:
				return "\33[32m";
			case Warning:
				return "\33[33m";
			case Error:
				return "\33[31m";
			default:
				return "";
			}
		}

		static String PathToRelative(StringView path)
		{
			auto position = path.rfind("Source");
			return String((position != String::npos) ? path.substr(position) : path);
		}
	}

	void Log::Initialize()
	{
		if (m_IsInitialized)
			return;

		if (GConfig->ShouldUseConsole())
			Console::Allocate();

		char* localAppDataDir = nullptr;
		_dupenv_s(&localAppDataDir, nullptr, "LOCALAPPDATA");

		auto logDirectory = std::format("{}\\{}\\Logs", localAppDataDir, GConfig->GetName());
		std::filesystem::create_directories(logDirectory);

		auto currentDateTime = DateTime::Now();
		auto logFilePath = std::format("{}\\{}.log", logDirectory, currentDateTime.GetDate());
		m_LogFile.open(logFilePath);

		free(localAppDataDir);

		LOG_CHECK(m_LogFile.is_open(), Error, LogCommon, "Failed to open log file: {}", logFilePath);

		// Delete log files older than 5 days (using file creation time)
		List<String> logFiles;
		for (const auto& entry : std::filesystem::directory_iterator(logDirectory))
			if (entry.is_regular_file())
			{
				auto path = entry.path().string();
				if (path.ends_with(".log"))
					logFiles.push_back(path);
			}

		if (logFiles.size() > 5)
		{
			std::sort(logFiles.begin(), logFiles.end(), [](StringView a, const StringView b)
				{
					return DateTime::FromFileCreationTime(a) < DateTime::FromFileCreationTime(b);
				});

			for (auto i = 0; i < logFiles.size() - 5; i++)
				std::filesystem::remove(logFiles[i]);
		}

		m_IsInitialized = true;
	}

	void Log::Shutdown()
	{
		if (!m_IsInitialized)
			return;

		m_LogFile.close();

		Console::Free();

		m_IsInitialized = false;
	}

	void Log::LogInternal(LogLevel level, const LogCategory& category, StringView formatedMessage, StringView file, int line)
	{
		if (!m_IsInitialized)
			return;

		auto defaultColor = "\33[0m";
		auto fatalColor = "\33[37;41m";

		auto currentTime = DateTime::Now().GetTime();
		auto levelName = Utils::LevelToName(level);
		auto& categoryName = category.GetName();

		if (level < LogLevel::Fatal)
		{
			auto levelColor = Utils::LevelToColor(level);
			auto levelString = std::format("{}{}{}", levelColor, levelName, defaultColor);

			if (Console::IsAllocated())
				std::println("[{}]: [{}]: {}", levelString, categoryName, formatedMessage);
			std::println(m_LogFile, "[{}]: [{}]: [{}]: {}", currentTime, levelName, categoryName, formatedMessage);

			return;
		}

		auto relativeFile = Utils::PathToRelative(file);

		if (Console::IsAllocated())
			std::println("{}[{}]: [{}] [{}:{}]: {}{}", fatalColor, levelName, categoryName, relativeFile, line, formatedMessage, defaultColor);
		std::println(m_LogFile, "[{}]: [{}]: [{}]: [{}:{}]: {}", currentTime, levelName, categoryName, relativeFile, line, formatedMessage);

		std::this_thread::sleep_for(std::chrono::seconds(5));
		std::abort();
	}
}
