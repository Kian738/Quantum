#pragma once

namespace Quantum
{
	class Console
	{
	private:
		static bool m_IsAllocated;
	public:
		static void Allocate();
		static void Free();

		static bool IsAllocated() { return m_IsAllocated; };
	};
}
