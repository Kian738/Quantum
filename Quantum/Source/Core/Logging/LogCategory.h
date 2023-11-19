#pragma once

#include "Core/Types.h"

namespace Quantum
{
	// TODO: Add minimum log level
	class LogCategory
	{
	private:
		String m_Name;
	public:
		LogCategory(const String& name);

		StringView GetName() const;
	};
}
