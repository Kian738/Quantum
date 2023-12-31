#pragma once

#include "Core/Types.h"

namespace Quantum
{
	class Environment
	{
	public:
		static bool IsDebug();

		static String GetEnv(StringView name);

		static String GetUsername();
		static String GetComputer();

		static String GetSpecialDir(int id);

		static String GetWorkingDir();

		static String GetDesktopDir();
		static String GetDocumentsDir();
		static String GetTempDir();

		static String GetAppDataDir();
		static String GetLocalAppDataDir();

		static String GetAppDir();
		static String GetLogsDir();
		static String GetConfigDir();

		static String GetExecutableName();
	};
}
