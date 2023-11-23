#pragma once

#include "Core/Types.h"

namespace Quantum
{
	class FileSystemUtils
	{
	public:
		static String GetParentDir(StringView path);

		static void CreateParentDirs(StringView path);
	};
}
