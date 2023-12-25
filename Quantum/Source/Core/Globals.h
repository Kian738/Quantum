#pragma once

#include "Core/Engine.h"
#include "Configuration/ConfigMacros.h"
#include "Logging/LogMacros.h"

DECLARE_CONFIG_FILE(Engine);

DECLARE_LOG_CATEGORY(Common);
DECLARE_LOG_CATEGORY(Config);
DECLARE_LOG_CATEGORY(Graphics);

namespace Quantum
{
	inline Engine* GEngine;
}
