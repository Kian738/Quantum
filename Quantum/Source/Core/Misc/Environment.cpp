#include "Environment.h"

#include "Core/Core.h"
#include <filesystem>
#include <ShlObj.h>

namespace Quantum
{
    bool Environment::IsDebug()
    {
#ifdef _DEBUG // TODO: Make a custom macro for this that applies to both debug and test builds
        return true;
#else
        return false;
#endif
    }

    String Environment::GetEnv(StringView name)
    {
        String result;
        auto size = GetEnvironmentVariableA(name.data(), nullptr, 0);
        if (size == 0)
            return result;
        result.resize(size);
        GetEnvironmentVariableA(name.data(), result.data(), size);
        return result;
    }

    String Environment::GetUsername()
    {
        return GetEnv("USERNAME");
    }

    String Environment::GetComputer()
    {
        return GetEnv("COMPUTERNAME");
    }

    String Environment::GetSpecialDir(int id)
    {
        String result;
        char path[MAX_PATH];
        if (SHGetSpecialFolderPathA(nullptr, path, id, FALSE))
            result = path;
        return result;
    }

    String Environment::GetWorkingDir()
    {
        return std::filesystem::current_path().string();
    }

    String Environment::GetDesktopDir()
    {
        return GetSpecialDir(CSIDL_DESKTOPDIRECTORY);
    }

    String Environment::GetDocumentsDir()
    {
        return GetSpecialDir(CSIDL_MYDOCUMENTS);
    }

    String Environment::GetTempDir()
    {
        return GetEnv("TEMP");
    }

    String Environment::GetAppDataDir()
    {
        return GetSpecialDir(CSIDL_APPDATA);
    }

    String Environment::GetLocalAppDataDir()
    {
        return GetSpecialDir(CSIDL_LOCAL_APPDATA);
    }

    String Environment::GetAppDir()
    {
        return FileSystemUtils::CombinePath(GetLocalAppDataDir(), Project::GetActive()->GetName());
    }

    String Environment::GetLogDir()
    {
        return FileSystemUtils::CombinePath(GetAppDir(), "Log");
    }

    String Environment::GetConfigDir()
    {
        return FileSystemUtils::CombinePath(GetAppDir(), "Config");
    }

    String Environment::GetExecutableName()
    {
        char fullPath[MAX_PATH];
        GetModuleFileNameA(NULL, fullPath, MAX_PATH);
        std::filesystem::path executablePath(fullPath);
        static auto executableName = executablePath.filename().string();
        return executableName;
    }
}

