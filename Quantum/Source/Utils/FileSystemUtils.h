#pragma once

#include "Core/Types.h"

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
	};
}
