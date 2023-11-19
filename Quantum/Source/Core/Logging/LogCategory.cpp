#include "LogCategory.h"

namespace Quantum
{
	LogCategory::LogCategory(const String& name)
		: m_Name(name)
	{
	}

	StringView LogCategory::GetName() const
	{
		return m_Name;
	}
}
