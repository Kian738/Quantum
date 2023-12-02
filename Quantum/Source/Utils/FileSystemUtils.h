#pragma once

#include "Core/Types.h"
#include <fstream>

namespace Quantum
{
	class FileSystemUtils
	{
	public:
		static String GetParentDir(StringView path);

		static void CreateDir(StringView path);
		static void CreateParentDir(StringView path);

		static String CombinePath(StringView directory, StringView path);
		static String CombinePath(StringView directory, StringView name, StringView extension);

		static String GetFileName(StringView path);

		static std::ofstream OpenFile(StringView path);
		static String ReadFile(StringView path);
	};
}
