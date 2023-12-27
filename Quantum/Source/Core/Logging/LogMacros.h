#pragma once

#include "Log.h"
#include "LogCategory.h"

#define DECLARE_LOG_CATEGORY(Name) \
	namespace Quantum \
	{ \
		struct LogCategory##Name : public LogCategory \
		{ \
			LogCategory##Name() : LogCategory("Log" #Name) {} \
		}; \
		extern LogCategory##Name Log##Name; \
	}

#define DEFINE_LOG_CATEGORY_STATIC(Name) \
	namespace Quantum \
	{ \
		static struct LogCategory##Name : public LogCategory \
		{ \
			LogCategory##Name() : LogCategory("Log" #Name) {} \
		} Log##Name; \
	}

#define DEFINE_LOG_CATEGORY(Name) \
	namespace Quantum \
	{ \
		LogCategory##Name Log##Name; \
	}

#define LOG(Level, Category, Message, ...) \
    Log::LogAsync(Level, Category, \
        [&]() { \
			if constexpr (std::initializer_list<const char*>{#__VA_ARGS__}.size() == 0) \
				return [&]() { return Message; }; \
			else \
				return [&]() { return std::format(Message, __VA_ARGS__); }; \
        }(), \
		__FILE__, __LINE__ \
	);

#define LOG_CHECK(Condition, Level, Category, Message, ...) \
	if (!(Condition)) \
		LOG(Level, Category, Message, __VA_ARGS__);
