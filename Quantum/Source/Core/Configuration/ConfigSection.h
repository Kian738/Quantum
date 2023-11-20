#pragma once

#include "Core/Types.h"

namespace Quantum
{
	class ConfigSection
	{
	private:
		const char* m_Name;
		Dictionary<String, String> m_Values;
	public:
		ConfigSection(const char* name) : m_Name(name) {}

		const char* GetName() const { return m_Name; };
		
		void Load();
		void Save();
	};
}
