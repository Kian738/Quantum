#pragma once

#include "Core/Engine.h"
#include "Configuration/ConfigMacros.h"
#include "Logging/LogMacros.h"

DECLARE_CONFIG_FILE(Engine);

DECLARE_LOG_CATEGORY(Common);

namespace Quantum
{
	inline Engine* GEngine = nullptr;
}
