#pragma once

namespace Quantum
{
	class Console
	{
	private:
		static inline bool s_IsAllocated = false;
	public:
		static void Allocate();
		static void Free();

		static bool IsAllocated() { return s_IsAllocated; };
	};
}
