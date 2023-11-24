#include "StringUtils.h"

namespace Quantum
{
	String StringUtils::BeforeLast(const char* string, const char* delimiter)
	{
		return BeforeLast<String>(string, delimiter);
	}

	String StringUtils::BeforeLast(String string, String delimiter)
	{
		return BeforeLast<String>(string, delimiter);
	}

	StringView StringUtils::BeforeLast(StringView string, StringView delimiter)
	{
		return BeforeLast<StringView>(string, delimiter);
	}

	List<String> StringUtils::Split(const char* string, const char* delimiter)
	{
		return Split<String>(string, delimiter);
	}

	List<String> StringUtils::Split(String string, String delimiter)
	{
		return Split<String>(string, delimiter);
	}

	List<StringView> StringUtils::Split(StringView string, StringView delimiter)
    {
		return Split<StringView>(string, delimiter);
    }
}
