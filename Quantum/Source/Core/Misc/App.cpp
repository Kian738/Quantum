#include "App.h"
#include "Core/Core.h"

namespace Quantum
{
	String App::GetName()
	{
		auto executableName = Environment::GetExecutableName();
		auto appName = executableName.substr(0, executableName.find_last_of('.'));
		return appName;
	}
}
