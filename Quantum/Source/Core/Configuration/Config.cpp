#include "Config.h"

#include "Core/Core.h"

namespace Quantum
{
	void Config::Initialize()
	{
		for (auto configFile : s_ConfigFiles)
			configFile->TryLoad();
	}

	void Config::Register(ConfigFile* configFile)
	{
		s_ConfigFiles.push_back(configFile);
	}

	void Config::PrintStatus()
	{
		for (auto configFile : s_ConfigFiles)
			LOG_CHECK(!configFile->m_HasError, Error, LogConfig, "Failed to load config file \"{}\": {}", configFile->m_Path, configFile->m_Exception);
	}
}
