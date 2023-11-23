#include "Core/Launch.h"

Quantum::Engine* CreateEngine()
{
	Quantum::EngineSpecification specification;
	return new Quantum::Engine(specification);
}
