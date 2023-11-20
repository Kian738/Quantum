#pragma once

#define DECLARE_CONFIG_SECTION(Name) \
	namespace Quantum \
	{ \
		struct ConfigSection##Name : public ConfigSection \
		{ \
			ConfigSection##Name() : ConfigSection(#Name) {} \
		}; \
		extern ConfigSection##Name Config##Name; \
	}
