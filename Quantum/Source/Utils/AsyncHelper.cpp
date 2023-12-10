#include "AsyncHelper.h"

namespace Quantum
{
	void AsyncHelper::Run(const Func<void()>& function)
	{
		std::thread(function).join();
	}

	void AsyncHelper::Run(const Func<void()>& function, const Func<void()>& callback)
	{
		std::thread(function).join();
		callback();
	}

	void AsyncHelper::RunAll(const List<Func<void()>>& functions)
	{
		List<std::thread> threads;
		for (auto& function : functions)
			threads.push_back(std::thread(function));

		for (auto& thread : threads)
			thread.join();
	}

	void AsyncHelper::Wait(const Func<void()>& function)
	{
		std::async(std::launch::async, function).wait();
	}

	void AsyncHelper::Wait(const Func<void()>& function, const Func<void()>& callback)
	{
		std::async(std::launch::async, function).wait();
		callback();
	}

	void AsyncHelper::WaitAll(const List<Func<void()>>& functions)
	{
		List<std::future<void>> futures;
		for (auto& function : functions)
			futures.push_back(std::async(std::launch::async, function));

		for (auto& future : futures)
			future.wait();
	}
}
