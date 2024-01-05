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

		static List<String> GetFiles(StringView directory);
		static List<String> GetFiles(StringView directory, StringView extension);

		static String GetFileName(StringView path);

		static OFStream OpenFile(StringView path);
		static String ReadFile(StringView path);

		static bool Exists(StringView path);
	};
}
