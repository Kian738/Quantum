#pragma once

#include "Core.h"
#include "Engine.h"

extern Quantum::Engine* CreateEngine();

namespace Quantum
{
	int Main(int argc, char** argv)
	{
		Log::Initialize();

		auto compileDateTime = DateTime::FromCompileTime();
		LOG(Info, LogCommon, "Launching Quantum Engine built on {} at {}", compileDateTime.GetDate(), compileDateTime.GetTime());

		// TODO: Parse command line arguments.
		Engine* engine = CreateEngine();
		engine->Run();
		delete engine;
		return 0; // TODO: Return the exit code from the engine.
	}
}

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	return Quantum::Main(__argc, __argv);
}
