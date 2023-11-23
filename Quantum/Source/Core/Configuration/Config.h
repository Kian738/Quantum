#pragma once

#include "Core/Types.h"
#include "ConfigFile.h"

namespace Quantum
{
	class ConfigCache
	{
	public:
		ConfigCache();
		~ConfigCache();

		template<typename T>
		T Get(StringView path, StringView key, const ConfigFile& file)
		{
			return file.Get<T>(path, key);
		};

		template<typename T>
		T Set(StringView path, StringView key, T value, const ConfigFile& file)
		{
			return file.Set<T>(path, key, value);
		};

		static void Initialize();
	};
}
