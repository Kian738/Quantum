#include "Core/Launch.h"

using namespace Quantum;

class EditorAppContext : public AppContext
{
public:
	EditorAppContext() : AppContext("QuantumEngine")
	{
	}

	void Initialize() override
	{
	}

	void Update(double delta) override
	{
	}

	void Render() override
	{
	}

	void Shutdown() override
	{
	}
};

AppContext* GetAppContext()
{
	return new EditorAppContext;
}
