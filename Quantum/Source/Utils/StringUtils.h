#pragma once

#include "Core/Types.h"

namespace Quantum
{
	class StringUtils
	{
	public:
		static String BeforeLast(StringView string, StringView delimiter);
		static List<String> Split(StringView string, StringView delimiter);
	};
}
