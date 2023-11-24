#pragma once

#include "Core/Types.h"

namespace Quantum
{
	class StringUtils
	{
	public:
		static String BeforeLast(const char* string, const char* delimiter);
		static String BeforeLast(String string, String delimiter);
		static StringView BeforeLast(StringView string, StringView delimiter);

		static List<String> Split(const char* string, const char* delimiter);
		static List<String> Split(String string, String delimiter);
		static List<StringView> Split(StringView string, StringView delimiter);
	private:
		template <typename T>
		static T BeforeLast(T string, T delimiter)
		{
			UInt64 index = string.find_last_of(delimiter);
			if (index != T::npos)
				return string.substr(0, index);
			return string;
		};

		template <typename T>
		static List<T> Split(T string, T delimiter)
		{
			List<T> result;
			UInt64 start = 0;
			UInt64 end = string.find(delimiter);
			while (end != T::npos)
			{
				result.push_back(string.substr(start, end - start));
				start = end + delimiter.size();
				end = string.find(delimiter, start);
			}
			result.push_back(string.substr(start, end));
			return result;
		};
	};
}
