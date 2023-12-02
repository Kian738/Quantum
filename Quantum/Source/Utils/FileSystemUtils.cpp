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

    String FileSystemUtils::GetFileName(StringView path)
    {
        return std::filesystem::path(path).filename().string();
    }

    std::ofstream FileSystemUtils::OpenFile(StringView path)
    {
        CreateParentDir(path);
        return std::ofstream(path.data());
    }

    String FileSystemUtils::ReadFile(StringView path)
    {
        String result;
        std::ifstream file(path.data(), std::ios::in | std::ios::binary);
        if (file.is_open())
		{
			file.seekg(0, std::ios::end);
			result.resize(file.tellg());
			file.seekg(0, std::ios::beg);
			file.read(&result[0], result.size());
			file.close();
		}
		return result;
    }
}
