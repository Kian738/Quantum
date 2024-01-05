#include "StringUtils.h"

namespace Quantum
{
	String StringUtils::BeforeLast(StringView string, StringView delimiter)
	{
		auto result = String(string);
		UInt64 index = string.find_last_of(delimiter);
		if (index != StringView::npos)
			result = string.substr(0, index);
		return result;
	}

	List<String> StringUtils::Split(StringView string, StringView delimiter)
    {
		List<String> result;
		UInt64 start = 0;
		UInt64 end = string.find(delimiter);
		while (end != StringView::npos)
		{
			result.push_back(String(string.substr(start, end - start)));
			start = end + delimiter.size();
			end = string.find(delimiter, start);
		}
		result.push_back(String(string.substr(start, end)));
		return result;
    }
}
