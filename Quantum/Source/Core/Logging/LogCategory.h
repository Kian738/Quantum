#pragma once

#include "Core/Types.h"

namespace Quantum
{
	class LogCategory
	{
	private:
		String m_Name;
	public:
		LogCategory(const String& name);

		const String& GetName() const;
	};
}
