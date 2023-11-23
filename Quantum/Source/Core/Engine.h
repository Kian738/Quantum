#pragma once

#include "Core.h"

namespace Quantum
{
	struct EngineSpecification
	{
		bool InitializeGraphics = true;
		// TODO: bool InitializeAudio = true;
		// TODO: bool InitializeInput = true;
		// TODO: bool InitializePhysics = true;
		// TODO: bool InitializeNetworking = true;
		// TODO: bool InitializeScripting = true;
	};

	class Engine
	{
	private:
		EngineSpecification m_Specification;
		bool m_IsRunning = false;
	public:
		Engine(EngineSpecification specification);
		~Engine();

		void Run();
	};
}
