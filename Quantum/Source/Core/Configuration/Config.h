#pragma once

#include "ConfigFile.h"
#include "Core/Types.h"

namespace Quantum
{
	class Config
	{
	private:
		static inline List<ConfigFile*> s_ConfigFiles;
	public:
		static void Initialize();
		static void Register(ConfigFile* configFile);
	};
}
