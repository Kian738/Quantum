#pragma once

#include "Core/Types.h"
#include <future>

namespace Quantum
{
	class AsyncHelper
	{
	public:
		static void Run(const Func<void()>& function);
		static void Run(const Func<void()>& function, const Func<void()>& callback);
		static void RunAll(const List<Func<void()>>& functions);

		static void Wait(const Func<void()>& function);
		static void Wait(const Func<void()>& function, const Func<void()>& callback);
		static void WaitAll(const List<Func<void()>>& functions);
	};
}
