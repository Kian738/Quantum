#include "ConfigFile.h"

#include "Core/Core.h"
#include <filesystem>

DEFINE_LOG_CATEGORY(Config);

namespace Quantum
{
	ConfigFile::ConfigFile(StringView name, bool isStatic)
		: m_Name(name)
		, m_IsStatic(isStatic)
	{
		Config::Register(this);
	}

	ConfigFile::~ConfigFile()
	{
		Save();
	}

	void ConfigFile::TryLoad()
	{
		try
		{
			auto defaultsDir = FileSystemUtils::CombinePath(Project::GetActive()->GetContentDir(), "Config");
			auto defaultsPath = FileSystemUtils::CombinePath(defaultsDir, std::format("Default{}", m_Name), "yaml");

			if (m_IsStatic)
			{
				m_Path = defaultsPath;
				Reload();
				return;
			}

			m_Path = FileSystemUtils::CombinePath(Environment::GetConfigDir(), m_Name, "yaml");
			
			auto defaults = YAML::LoadFile(defaultsPath);

			if (!FileSystemUtils::Exists(m_Path))
			{
				m_Data = defaults;
				Save();
				return;
			}

			Reload();

			if (YAMLUtils::MergeTo(m_Data, defaults))
				Save();
		}
		catch (const std::exception& e)
		{
			m_HasError = true;
			m_Exception = e.what();
		}
	}

	void ConfigFile::Reload()
	{
		m_Data = YAML::LoadFile(m_Path);
	}

	void ConfigFile::Save()
	{
		if (m_IsStatic)
			return;

		FileSystemUtils::OpenFile(m_Path) << m_Data;
	}
}
