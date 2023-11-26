#pragma once

#include "Core.h"

namespace Quantum
{
	class Engine
	{
	private:
		bool m_IsRunning = false;
	public:
		Engine();
		~Engine();

		void Run();
	};
}
