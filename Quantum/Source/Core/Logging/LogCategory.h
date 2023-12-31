#pragma once

#include "Core/Types.h"

namespace Quantum
{
	// TODO: Add minimum log level
	class LogCategory
	{
	private:
		const char* m_Name;
	public:
		LogCategory(const char* name) : m_Name(name) {}

		const char* GetName() const { return m_Name; };
	};
}
