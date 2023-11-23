#pragma once

#include "Core/Types.h"
#include <yaml-cpp/yaml.h>

namespace Quantum
{
	// TODO: Add loading mechanism so File is only cached when needed
	class ConfigFile
	{
	private:
		String m_Path;
		YAML::Node m_Data; // TOOD: Maybe we shouldnt store the data in memory, but rather read it from the file when needed?
		friend class Config;
	public:
		ConfigFile(StringView name);
		~ConfigFile();

		YAML::Node& Get() { return m_Data; };

		void Reload();
		void Save();
	};
}
