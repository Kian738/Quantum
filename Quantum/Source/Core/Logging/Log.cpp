#include "Log.h"

#include "LogMacros.h"
#include <filesystem>
#include <iostream>
#include <thread>

namespace Quantum
{
	void Log::Initialize()
	{
		auto consoleConfig = GEngineConfig["Console"];

		if (consoleConfig["Enabled"].as<bool>(Environment::IsDebug()))
			Console::Allocate();

		s_LogLevel = COALESCE(
			GetLevel(consoleConfig["LogLevel"].as<String>("").c_str()),
			LogLevel::Verbose
		);

		// TODO: Implement log file stacking with -1, -2, -3, etc.
		auto logFilePath = FileSystemUtils::CombinePath(
			Environment::GetLogsDir(),
			DateTime::Now().GetDate(),
			"log"
		);
		FileSystemUtils::CreateParentDir(logFilePath);
		s_LogFile.open(logFilePath);

		s_IsInitialized = true;

		LOG_CHECK(s_LogFile.is_open(), Error, LogCommon, "Failed to open log file: {}", logFilePath);
	}

	void Log::Shutdown()
	{
		s_LogFile.close();

		Console::Free();

		s_IsInitialized = false;
	}

	void Log::LogAsync(LogLevel level, const LogCategory& category, Func<String()> formatFunc, StringView file, int line)
	{
		if (!s_IsInitialized || level < s_LogLevel)
			return;

		auto message = formatFunc();
		AsyncHelper::Run([&] { LogInternal(level, category, message, file, line); });
	}

	const char* Log::GetLevelName(LogLevel level)
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

	void Log::LogInternal(LogLevel level, const LogCategory& category, String message, StringView file, int line)
	{
		auto defaultColor = "\33[0m";
		auto fatalColor = "\33[37;41m";

		auto currentTime = DateTime::Now().GetTime();
		auto levelName = GetLevelName(level);
		auto categoryName = category.GetName();

		Lock<> lock(s_LogFileMutex);

		if (level < LogLevel::Fatal)
		{
			auto levelColor = GetLevelColor(level);
			auto levelString = std::format("{}{}{}", levelColor, levelName, defaultColor); // TODO: Could be precomputed

			auto plainMessage = std::format("[{}]: {}", categoryName, message);
			if (Console::IsAllocated()) std::println("[{}]: {}", levelString, plainMessage);
			std::println(s_LogFile, "[{}]: [{}]: {}", currentTime, levelName, plainMessage);

			return;
		}

		auto relativeFile = PathToRelative(file);

		auto plainMessage = std::format("[{}]: [{}]: [{}:{}]: {}", levelName, categoryName, relativeFile, line, message);
		if (Console::IsAllocated()) std::println("{}{}{}", fatalColor, plainMessage, defaultColor);
		std::println(s_LogFile, "[{}]: {}", currentTime, plainMessage);

		std::this_thread::sleep_for(std::chrono::seconds(5));
		if (GEngine)
			GEngine->Crash();
		else
			std::exit(1);
	}

	LogLevel Log::GetLevel(const char* name)
	{
		static Dictionary<const char*, LogLevel> logLevels = {
			{ "Verbose", LogLevel::Verbose },
			{ "Debug", LogLevel::Debug },
			{ "Info", LogLevel::Info },
			{ "Warning", LogLevel::Warning },
			{ "Error", LogLevel::Error },
			{ "Fatal", LogLevel::Fatal }
		};

		return logLevels[name];
	}

	const char* Log::GetLevelColor(LogLevel level)
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
				if (auto path = entry.path().string(); path.ends_with(".log"))
					logFiles.push_back(path);

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
