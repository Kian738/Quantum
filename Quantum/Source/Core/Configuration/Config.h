#pragma once

#include "ConfigFile.h"
#include "Core/Types.h"

namespace Quantum
{
	class Config
	{
	private:
		inline static List<ConfigFile*> s_ConfigFiles;
	public:
		static void Initialize();
		static void Shutdown();

		static void Register(ConfigFile* configFile);
		static void Unregister(ConfigFile* configFile);
	};
}