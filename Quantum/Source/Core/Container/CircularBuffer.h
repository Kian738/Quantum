#pragma once

#include "Core/Types.h"

namespace Quantum
{
	template <typename T, UInt64 N>
	class CircularBuffer
	{
	private:
		Deque<T> m_Buffer;
	public:
		void Push(const T& value)
		{
			PerformPopCheck();
			m_Buffer.push_back(value);
		}

		void Push(T&& value)
		{
			PerformPopCheck();
			m_Buffer.push_back(value);
		}

		void Emplace(const T& value)
		{
			PerformPopCheck();
			m_Buffer.emplace_back(value);
		}

		void Emplace(T&& value)
		{
			PerformPopCheck();
			m_Buffer.emplace_back(value);
		}

		T& operator[](UInt64 index)
		{
			return m_Buffer[index];
		}

		const T& operator[](UInt64 index) const
		{
			return m_Buffer[index];
		}

		UInt64 GetSize() const
		{
			return m_Buffer.size();
		}

		UInt64 GetCapacity() const
		{
			return N;
		}

		T& GetFront()
		{
			return m_Buffer.front();
		}

		const T& GetFront() const
		{
			return m_Buffer.front();
		}

		T& GetBack()
		{
			return m_Buffer.back();
		}

		const T& GetBack() const
		{
			return m_Buffer.back();
		}

		bool IsEmpty() const
		{
			return m_Buffer.empty();
		}

		void PopFront()
		{
			m_Buffer.pop_front();
		}

		void PopBack()
		{
			m_Buffer.pop_back();
		}

		void Clear()
		{
			m_Buffer.clear();
		}

		Deque<T>::iterator begin()
		{
			return m_Buffer.begin();
		}

		Deque<T>::iterator end()
		{
			return m_Buffer.end();
		}

		Deque<T>::const_iterator begin() const
		{
			return m_Buffer.begin();
		}

		Deque<T>::const_iterator end() const
		{
			return m_Buffer.end();
		}
	private:
		void PerformPopCheck()
		{
			if (m_Buffer.size() == N)
				m_Buffer.pop_front();
		}
	};
}
