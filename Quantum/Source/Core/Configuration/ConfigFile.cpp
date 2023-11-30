#include "ConfigFile.h"
#include "Core/Core.h"
#include <filesystem>

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

		if (YAMLUtils::MergeTo(m_Data, defaults))
			Save();
	}

	void ConfigFile::Reload()
	{
		m_Data = YAML::LoadFile(m_Path);
	}

	void ConfigFile::Save()
	{
		FileSystemUtils::OpenFileSafe(m_Path) << m_Data;
	}
}
