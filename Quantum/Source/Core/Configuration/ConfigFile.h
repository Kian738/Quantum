#pragma once

#include "Core/Types.h"
#include <yaml-cpp/yaml.h>

namespace Quantum
{
	// TODO: Add loading mechanism so File is only cached when needed
	// TODO: Create empty key if it doesn't exist
	class ConfigFile
	{
	private:
		String m_Name;
		String m_Path;
		YAML::Node m_Data;
		bool m_HasError = false;

		friend class Config;
	public:
		ConfigFile(StringView name);
		~ConfigFile();

		YAML::Node& Get() { return m_Data; };
		bool HasError() const { return m_HasError; };

		YAML::Node operator[](const char* key) { return m_Data[key]; };
		YAML::Node operator[](StringView key) { return m_Data[key]; };

		void Load();
		void Reload();
		void Save();
	};
}
