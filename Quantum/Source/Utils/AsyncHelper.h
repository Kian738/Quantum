#pragma once

#include "Core/Types.h"
#include <future>

namespace Quantum
{
	class AsyncHelper
	{
	public:
		static void Run(const Func<void()>& function);
		static void RunAll(const List<Func<void()>>& functions);

		static void Wait(const Func<void()>& function);
		static void WaitAll(const List<Func<void()>>& functions);
	};
}
