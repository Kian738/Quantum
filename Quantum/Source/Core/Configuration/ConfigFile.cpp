#include "ConfigFile.h"
#include "Core/Core.h"
#include <filesystem>
#include <fstream>

namespace Quantum
{
	ConfigFile::ConfigFile(StringView name)
	{
		m_Path = std::format("{}/{}.yaml", Environment::GetConfigDir(), name);
		auto defaults = YAML::LoadFile(std::format("{}/Config/Default{}.yaml", Environment::GetContentDir(), name));

		if (!std::filesystem::exists(m_Path))
		{
			m_Data = defaults;
			Save();
			return;
		}
		
		Reload();

		bool isDirty = false;
		for (auto it : defaults)
			if (!m_Data[it.first])
			{
				m_Data[it.first] = it.second;
				isDirty = true;
			}

		if (isDirty)
			Save();
	}

	ConfigFile::~ConfigFile()
	{
		Save();
	}

	void ConfigFile::Reload()
	{
		m_Data = YAML::LoadFile(m_Path);
	}

	void ConfigFile::Save()
	{
		FileSystemUtils::CreateParentDir(m_Path);
		std::ofstream file(m_Path);
		file << m_Data;
		file.close();
	}
}
