#pragma once

#include "Core/Types.h"

namespace Quantum
{
	// TODO: Add project files
	// TODO: Utilize multiple config files like Unreal Engine and use classes
	class ProjectConfig
	{
	public:
		ProjectConfig();
		~ProjectConfig();

		const char* GetName();
		const char* GetDescription();
		const char* GetAuthor();

		bool ShouldUseConsole();
	private:
		const char* GetString(StringView key);
		bool GetBool(StringView key);
		int GetInt(StringView key);
		float GetFloat(StringView key);
	};
}

// TODO: Just a placeholder for now
Quantum::ProjectConfig* GConfig = new Quantum::ProjectConfig;
