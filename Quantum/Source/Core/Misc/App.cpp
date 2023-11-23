#include "App.h"
#include "Core/Core.h"

namespace Quantum
{
	String App::GetName()
	{
		auto executableName = Environment::GetExecutableName();
		static auto& appName = StringUtils::Split(executableName, ".")[0];
		return appName;
	}
}
