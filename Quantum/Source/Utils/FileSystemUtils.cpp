#include "FileSystemUtils.h"
#include <filesystem>

namespace Quantum
{
    String FileSystemUtils::GetParentDir(StringView path)
    {
        return std::filesystem::path(path).parent_path().string();
    }

    void FileSystemUtils::CreateDir(StringView path)
    {
        std::filesystem::create_directories(path);
    }

    void FileSystemUtils::CreateParentDir(StringView path)
    {
        CreateDir(GetParentDir(path));
    }

    String FileSystemUtils::CombinePath(StringView directory, StringView path)
    {
        return std::format("{}\\{}", directory, path);
    }

    String FileSystemUtils::CombinePath(StringView directory, StringView name, StringView extension)
    {
        return std::format("{}\\{}.{}", directory, name, extension);
    }
}
