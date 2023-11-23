#pragma once

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

#define DEFINE_CONFIG_FILE_STATIC(Name) \
	namespace Quantum \
	{ \
		static struct ConfigFile##Name : public ConfigFile \
		{ \
			ConfigFile##Name() : ConfigFile(#Name) {} \
		} G##Name##Config; \
	}

#define DEFINE_CONFIG_FILE(Name) \
	namespace Quantum \
	{ \
		ConfigFile##Name G##Name##Config; \
	}
