#include "Environment.h"
#include <filesystem>
#include <ShlObj.h>

namespace Quantum
{
    String Environment::GetEnvironmentVariable(StringView name)
    {
        String result;
        auto size = GetEnvironmentVariableA(name.data(), nullptr, 0);
        if (size == 0)
            return result;
        result.resize(size);
        GetEnvironmentVariableA(name.data(), result.data(), size);
        return result;
    }

    String Environment::GetSpecialFolder(int id)
    {
        String result;
		char path[MAX_PATH];
		if (SHGetSpecialFolderPathA(nullptr, path, id, FALSE))
			result = path;
		return result;
    }

    String Environment::GetWorkingDirectory()
    {
        return std::filesystem::current_path().string();
    }

    String Environment::GetDesktopDirectory()
    {
        return GetSpecialFolder(CSIDL_DESKTOPDIRECTORY);
	}

    String Environment::GetDocumentsDirectory()
    {
        return GetSpecialFolder(CSIDL_MYDOCUMENTS);
    }

    String Environment::GetTempDirectory()
    {
		return GetEnvironmentVariable("TEMP");
	}

    String Environment::GetAppDataDirectory()
    {
		return GetSpecialFolder(CSIDL_APPDATA);
	}

    String Environment::GetLocalAppDataDirectory()
    {
        return GetSpecialFolder(CSIDL_LOCAL_APPDATA);
    }

    String Environment::GetUsername()
    {
		return GetEnvironmentVariable("USERNAME");
	}

    String Environment::GetComputerName()
    {
        return GetEnvironmentVariable("COMPUTERNAME");
    }
}

