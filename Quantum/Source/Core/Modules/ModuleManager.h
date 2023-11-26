#pragma once

namespace Quantum
{
	class ModuleManager
	{
	public:
		ModuleManager();
		~ModuleManager();

		void Load();
		void Shutdown();

		void Update();

		void RegisterModule(class Module* module);
		void UnregisterModule(class Module* module);
	};
}