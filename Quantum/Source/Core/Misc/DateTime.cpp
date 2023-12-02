#include "DateTime.h"

#include <ctime>
#include <filesystem>

namespace Quantum
{
	DateTime::DateTime(const std::tm& time)
		: m_Time(time)
	{
	}

	std::tm DateTime::Get() const
	{
		return m_Time;
	}

	String DateTime::GetDate() const
	{
		char buffer[11];
		std::strftime(buffer, sizeof(buffer), "%d.%m.%Y", &m_Time);
		return buffer;
	}

	String DateTime::GetTime() const
	{
		char buffer[9];
		std::strftime(buffer, sizeof(buffer), "%H:%M:%S", &m_Time);
		return buffer;
	}

	Pair<String, String> DateTime::GetDateTime() const
	{
		return { GetDate(), GetTime() };
	}

	bool DateTime::operator==(const DateTime& other) const
	{
		return m_Time.tm_year == other.m_Time.tm_year &&
			m_Time.tm_mon == other.m_Time.tm_mon &&
			m_Time.tm_mday == other.m_Time.tm_mday &&
			m_Time.tm_hour == other.m_Time.tm_hour &&
			m_Time.tm_min == other.m_Time.tm_min &&
			m_Time.tm_sec == other.m_Time.tm_sec;
	}

	bool DateTime::operator!=(const DateTime& other) const
	{
		return !(*this == other);
	}

	bool DateTime::operator<(const DateTime& other) const
	{
		return m_Time.tm_year < other.m_Time.tm_year ||
			m_Time.tm_mon < other.m_Time.tm_mon ||
			m_Time.tm_mday < other.m_Time.tm_mday ||
			m_Time.tm_hour < other.m_Time.tm_hour ||
			m_Time.tm_min < other.m_Time.tm_min ||
			m_Time.tm_sec < other.m_Time.tm_sec;
	}

	bool DateTime::operator>(const DateTime& other) const
	{
		return m_Time.tm_year > other.m_Time.tm_year ||
			m_Time.tm_mon > other.m_Time.tm_mon ||
			m_Time.tm_mday > other.m_Time.tm_mday ||
			m_Time.tm_hour > other.m_Time.tm_hour ||
			m_Time.tm_min > other.m_Time.tm_min ||
			m_Time.tm_sec > other.m_Time.tm_sec;
	}

	bool DateTime::operator<=(const DateTime& other) const
	{
		return !(*this > other);
	}

	bool DateTime::operator>=(const DateTime& other) const
	{
		return !(*this < other);
	}

	DateTime DateTime::FromCompileTime()
	{
		const char* compileDate = __DATE__;
		const char* compileTime = __TIME__;

		std::tm tm = {};
		char monthAbbreviation[5];
		int year;
		sscanf_s(compileDate, "%s %d %d", monthAbbreviation, static_cast<UInt32>(sizeof(monthAbbreviation)), &tm.tm_mday, &year);
		sscanf_s(compileTime, "%d:%d:%d", &tm.tm_hour, &tm.tm_min, &tm.tm_sec);

		tm.tm_year = year - 1900;
		tm.tm_mon = GetMonthFromAbbreviation(monthAbbreviation) - 1;

		return { tm };
	}

	DateTime DateTime::FromFileCreationTime(StringView path)
	{
		std::tm tm = {};
		const auto fileTime = std::filesystem::last_write_time(path);
		const auto systemTime = std::chrono::clock_cast<std::chrono::system_clock>(fileTime);
		const auto time = std::chrono::system_clock::to_time_t(systemTime);
		localtime_s(&tm, &time);
		return { tm };
	}

	DateTime DateTime::Now()
	{
		std::time_t now = std::time(nullptr);
		std::tm tm = {};
		localtime_s(&tm, &now);
		return { tm };
	}

	int DateTime::GetMonthFromAbbreviation(const char* monthAbbreviation)
	{
		static const char* monthNames[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
		for (int i = 0; i < 12; i++)
			if (strcmp(monthAbbreviation, monthNames[i]) == 0)
				return i + 1;
		return 0;
	}
}
