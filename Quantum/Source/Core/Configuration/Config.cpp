#include "Config.h"

namespace Quantum
{
	void Config::Initialize()
	{
		for (auto configFile : s_ConfigFiles)
			configFile->Load();
	}

	void Config::Register(ConfigFile* configFile)
	{
		s_ConfigFiles.push_back(configFile);
	}
}
