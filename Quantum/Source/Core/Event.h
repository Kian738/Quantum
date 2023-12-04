#pragma once

#include "Types.h"

namespace Quantum
{
	template <typename... Args>
	class Event
	{
	private:
		using CallbackFunc = Func<void(Args...)>;
		List<CallbackFunc> m_Listeners;
	public:
		void Fire(Args... args)
		{
			for (auto& listener : m_Listeners)
				listener(args...);
		}

		void AddListener(CallbackFunc listener) { m_Listeners.push_back(listener); };
		void RemoveListener(CallbackFunc listener)
		{
			m_Listeners.erase(
				std::remove(m_Listeners.begin(), m_Listeners.end(), listener),
				m_Listeners.end()
			);
		};

		void ClearAllListeners() { m_Listeners.clear(); };

		void operator()(Args... args) { Fire(args...); };

		void operator+=(CallbackFunc listener) { AddListener(listener); };
		void operator-=(CallbackFunc listener) { RemoveListener(listener); };

	};
}
