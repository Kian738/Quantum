#pragma once

#include "Config.h"
#include "ConfigFile.h"

#define DECLARE_CONFIG_FILE(Name) \
	namespace Quantum \
	{ \
		struct ConfigFile##Name : public ConfigFile \
		{ \
			ConfigFile##Name() : ConfigFile(#Name) {} \
		}; \
		extern ConfigFile##Name G##Name##Config; \
	}

#define DECLARE_STATIC_CONFIG_FILE(Name) \
	namespace Quantum \
	{ \
		struct ConfigFile##Name : public ConfigFile \
		{ \
			ConfigFile##Name() : ConfigFile(#Name, true) {} \
		}; \
		extern ConfigFile##Name G##Name##Config; \
	}

#define DEFINE_CONFIG_FILE(Name) \
	namespace Quantum \
	{ \
		ConfigFile##Name G##Name##Config; \
	}
