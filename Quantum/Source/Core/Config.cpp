#include "Config.h"

#define RETURN_STRING_VALUE(key) \
	static auto value = GetString(key); \
	return value;

#define RETURN_BOOL_VALUE(key) \
	static auto value = GetBool(key); \
	return value;

namespace Quantum
{
	// TODO: Implement config file parsing
	ProjectConfig::ProjectConfig()
	{
	}

	ProjectConfig::~ProjectConfig()
	{
	}

	const char* ProjectConfig::GetName()
	{
		RETURN_STRING_VALUE("Name");
	}

	const char* ProjectConfig::GetDescription()
	{
		RETURN_STRING_VALUE("Description");
	}

	const char* ProjectConfig::GetAuthor()
	{
		RETURN_STRING_VALUE("Author");
	}

	bool ProjectConfig::ShouldUseConsole()
	{
		RETURN_BOOL_VALUE("UseConsole");
	}

	const char* ProjectConfig::GetString(StringView key)
	{
		return "PlaceHolder"; // TODO: Implement
	}

	bool ProjectConfig::GetBool(StringView key)
	{
		return true; // TODO: Implement
	}

	int ProjectConfig::GetInt(StringView key)
	{
		return 0; // TODO: Implement
	}

	float ProjectConfig::GetFloat(StringView key)
	{
		return 0.0f; // TODO: Implement
	}
}
