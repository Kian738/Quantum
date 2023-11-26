#include "Config.h"

namespace Quantum
{
	void Config::Initialize()
	{
		for (auto configFile : s_ConfigFiles)
			configFile->Load();
	}

	void Config::Shutdown()
	{
		for (auto configFile : s_ConfigFiles)
			delete configFile;
	}

	void Config::Register(ConfigFile* configFile)
	{
		s_ConfigFiles.push_back(configFile);
	}

	void Config::Unregister(ConfigFile* configFile)
	{
		s_ConfigFiles.erase(
			std::remove(s_ConfigFiles.begin(), s_ConfigFiles.end(), configFile),
			s_ConfigFiles.end()
		);
	}
}
