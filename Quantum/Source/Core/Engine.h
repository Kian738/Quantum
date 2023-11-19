#pragma once

namespace Quantum
{
	class Engine
	{
	public:
		Engine() = default;

		void Initialize();
		void Shutdown();
		void Tick();
	};
}
