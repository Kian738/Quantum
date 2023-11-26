#include "ConfigFile.h"
#include "Core/Core.h"
#include <filesystem>
#include <fstream>

DEFINE_LOG_CATEGORY_STATIC(Config);

namespace Quantum
{
	ConfigFile::ConfigFile(StringView name)
		: m_Name(name)
	{
		Config::Register(this);
	}

	ConfigFile::~ConfigFile()
	{
		Save();

		Config::Unregister(this);
	}

	void ConfigFile::Load()
	{
		m_Path = FileSystemUtils::CombinePath(Environment::GetConfigDir(), m_Name, "yaml");

		auto defaultsDir = FileSystemUtils::CombinePath(Project::GetActive()->GetContentDir(), "Config");
		auto defaultsPath = FileSystemUtils::CombinePath(defaultsDir, std::format("Default{}", m_Name), "yaml");
		auto defaults = YAML::LoadFile(defaultsPath);

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
