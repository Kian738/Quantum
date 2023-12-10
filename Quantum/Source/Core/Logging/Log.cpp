#include "Log.h"

#include "LogMacros.h"
#include <filesystem>
#include <iostream>
#include <thread>

// TODO: Add async logging
namespace Quantum
{
	std::ofstream Log::m_LogFile = {};
	bool Log::m_IsInitialized = false;

	void Log::Initialize()
	{
		if (m_IsInitialized)
			return;

		if (GEngineConfig["Console"]["Enabled"].as<bool>(Environment::IsDebug()))
			Console::Allocate();

		auto logFilePath = FileSystemUtils::CombinePath(
			Environment::GetLogsDir(),
			DateTime::Now().GetDate(),
			"log"
		);

		FileSystemUtils::CreateParentDir(logFilePath);
		m_LogFile.open(logFilePath);

		m_IsInitialized = true;

		LOG_CHECK(m_LogFile.is_open(), Error, LogCommon, "Failed to open log file: {}", logFilePath);
	}

	void Log::Shutdown()
	{
		if (!m_IsInitialized)
			return;

		m_LogFile.close();

		Console::Free();

		m_IsInitialized = false;
	}

	void Log::LogAsync(LogLevel level, const LogCategory& category, Func<String()> formatFunc, StringView file, int line)
	{
		if (!m_IsInitialized)
			return;

		static auto minLevel = LogLevel::Verbose; // TODO: GEngineConfig["Logging"]["MinLevel"].as<LogLevel>(LogLevel::Info);
		if (level < minLevel)
			return;

		auto message = formatFunc();

		AsyncHelper::Run([&] { LogInternal(level, category, message, file, line); });
	}

	void Log::LogInternal(LogLevel level, const LogCategory& category, String message, StringView file, int line)
	{
		auto defaultColor = "\33[0m";
		auto fatalColor = "\33[37;41m";

		auto currentTime = DateTime::Now().GetTime();
		auto levelName = LevelToName(level);
		auto categoryName = category.GetName();

		if (level < LogLevel::Fatal)
		{
			auto levelColor = LevelToColor(level);
			auto levelString = std::format("{}{}{}", levelColor, levelName, defaultColor); // TODO: Could be precomputed

			if (Console::IsAllocated()) std::println("[{}]: [{}]: {}", levelString, categoryName, message);
			std::println(m_LogFile, "[{}]: [{}]: [{}]: {}", currentTime, levelName, categoryName, message);

			return;
		}

		auto relativeFile = PathToRelative(file);

		if (Console::IsAllocated()) std::println("{}[{}]: [{}] [{}:{}]: {}{}", fatalColor, levelName, categoryName, relativeFile, line, message, defaultColor);
		std::println(m_LogFile, "[{}]: [{}]: [{}]: [{}:{}]: {}", currentTime, levelName, categoryName, relativeFile, line, message);

		std::this_thread::sleep_for(std::chrono::seconds(5));
		GEngine->Crash();
	}

	const char* Log::LevelToName(LogLevel level)
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

	const char* Log::LevelToColor(LogLevel level)
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

	String Log::PathToRelative(StringView path)
	{
		auto position = path.rfind("Source");
		return String((position != String::npos) ? path.substr(position) : path);
	}

	void Log::PurgeLogFiles()
	{
		List<String> logFiles;
		for (const auto& entry : std::filesystem::directory_iterator(Environment::GetLogsDir()))
			if (entry.is_regular_file())
			{
				auto path = entry.path().string();
				if (path.ends_with(".log"))
					logFiles.push_back(path);
			}

		// TODO: Maybe I should sort by file size instead of creation time or use the file name as a timestamp
		if (logFiles.size() > 5)
		{
			std::sort(logFiles.begin(), logFiles.end(), [](StringView a, const StringView b)
				{
					return DateTime::FromFileCreationTime(a) < DateTime::FromFileCreationTime(b);
				});

			for (auto i = 0; i < logFiles.size() - 5; i++)
				std::filesystem::remove(logFiles[i]);
		}
	}
}
