#include "App.h"
#include "Core/Core.h"

namespace Quantum
{
	String App::GetName()
	{
		auto executableName = Environment::GetExecutableName();
		static auto appName = StringUtils::BeforeLast(executableName, ".");
		return appName;
	}
}
