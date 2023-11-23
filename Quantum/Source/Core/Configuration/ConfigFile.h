#pragma once

#include "Core/Types.h"
#include "Utils/StringUtils.h"
#include <yaml-cpp/yaml.h>

namespace Quantum
{
	// TODO: Add loading mechanism so File is only cached when needed
	class ConfigFile
	{
	private:
		String m_Path;
		YAML::Node m_Data; // TOOD: Maybe we shouldnt store the data in memory, but rather read it from the file when needed?
	public:
		ConfigFile(StringView name);
		~ConfigFile();

		template<typename T>
		T Get(StringView path, StringView key)
		{
			auto pathParts = StringUtils::Split(path, ".");

			auto& node = m_Data;
			for (auto& part : pathParts)
				node = node[part];

			return node[key].as<T>();
		};

		template<typename T>
		T Set(StringView path, StringView key, T value)
		{
			auto pathParts = StringUtils::Split(path, ".");

			auto& node = m_Data;
			for (auto& part : pathParts)
				node = node[part];

			node[key] = value;
		};

		void Reload();
		void Save();
	};
}
