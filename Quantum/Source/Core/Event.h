#pragma once

#include "Types.h"
#include <functional>

namespace Quantum
{
	template <typename... Args>
	class Event
	{
	private:
		using Func = std::function<void(Args...)>;
		List<Func> m_Listeners;
	public:
		void Fire(Args... args)
		{
			for (auto& listener : m_Listeners)
				listener(args...);
		}

		void AddListener(Func listener) { m_Listeners.push_back(listener); };
		void RemoveListener(Func listener)
		{
			m_Listeners.erase(
				std::remove(m_Listeners.begin(), m_Listeners.end(), listener),
				m_Listeners.end()
			);
		};

		void ClearAllListeners() { m_Listeners.clear(); };

		void operator()(Args... args) { Fire(args...); };

		void operator+=(Func listener) { AddListener(listener); };
		void operator-=(Func listener) { RemoveListener(listener); };

	};
}
