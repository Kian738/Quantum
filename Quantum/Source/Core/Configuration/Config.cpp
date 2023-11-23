#include "Config.h"
#include "Core/Globals.h"

namespace Quantum
{
	ConfigCache::ConfigCache()
	{
	}

	ConfigCache::~ConfigCache()
	{
	}

	void ConfigCache::Initialize()
	{
		GConfig = new ConfigCache();
	}
}
