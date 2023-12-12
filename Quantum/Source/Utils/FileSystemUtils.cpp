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

    List<String> FileSystemUtils::GetFiles(StringView directory)
    {
        List<String> result;
        for (const auto& entry : std::filesystem::directory_iterator(directory))
			if (entry.is_regular_file())
			    result.push_back(entry.path().string());
		return result;
    }

    List<String> FileSystemUtils::GetFiles(StringView directory, StringView extension)
    {
        List<String> result;
        for (const auto& entry : std::filesystem::directory_iterator(directory))
        {
            auto& entryPath = entry.path();
            if (entry.is_regular_file() && entryPath.extension() == extension)
			    result.push_back(entryPath.string());
        }
        return result;
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
