#pragma once

namespace Quantum
{
	class IModule
	{
	public:
		virtual ~IModule() = default;

		virtual void Load() = 0;
		virtual void Shutdown() = 0;
	};
}
