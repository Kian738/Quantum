#include "Config.h"
#include "Core/Core.h"

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
