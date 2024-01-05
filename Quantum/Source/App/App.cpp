#include "App.h"

#include "Core/Core.h"

namespace Quantum
{
	String App::GetName()
	{
		static auto appName = StringUtils::BeforeLast(
			Environment::GetExecutableName(),
			"."
		);
		return appName;
	}
}
