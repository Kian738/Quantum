#include "StringUtils.h"

namespace Quantum
{
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
