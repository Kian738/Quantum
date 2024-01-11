#include "Core/Launch.h"

#ifndef PROJECT_NAME
	#define PROJECT_NAME ""
	#error "PROJECT_NAME must be defined"
#endif

namespace Quantum
{
	class RuntimeAppContext : public AppContext
	{
	public:
		RuntimeAppContext() : AppContext(PROJECT_NAME)
		{
		}

		void Initialize() override
		{
		}

		void Shutdown() override
		{
		}

		void Update(float deltaTime) override
		{
		}
	};
}

Quantum::AppContext* GetAppContext()
{
	return new Quantum::RuntimeAppContext;
}
