#pragma once

#include "Core/Core.h"

namespace Quantum
{
	class Environment
	{
	public:
		static String GetEnvironmentVariable(StringView name);
		static String GetSpecialFolder(int id);

		static String GetWorkingDirectory();

		static String GetDesktopDirectory();
		static String GetDocumentsDirectory();
		static String GetTempDirectory();

		static String GetAppDataDirectory();
		static String GetLocalAppDataDirectory();

		static String GetUsername();
		static String GetComputerName();
	};
}
