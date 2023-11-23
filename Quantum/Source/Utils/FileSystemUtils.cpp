#include "FileSystemUtils.h"
#include <filesystem>

namespace Quantum
{
    String FileSystemUtils::GetParentDir(StringView path)
    {
        return std::filesystem::path(path).parent_path().string();
    }

    void FileSystemUtils::CreateParentDirs(StringView path)
    {
        std::filesystem::create_directories(GetParentDir(path));
    }
}
