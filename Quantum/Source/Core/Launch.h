#pragma once

#include "Core.h"
#include "Engine.h"

extern Quantum::Engine* CreateEngine();

namespace Quantum
{
	int Main(int argc, char** argv)
	{
		Log::Initialize();
		auto [date, time] = DateTime::FromCompileTime().GetDateTime();
		LOG(Info, LogCommon, "Quantum Engine built on {} at {}", date, time);

		// TODO: Parse command line arguments
 		Engine* engine = CreateEngine();
		engine->Run();
		delete engine;

		LOG(Info, LogCommon, "Shutting down...");
		Log::Shutdown();

		return 0; // TODO: Return the exit code from the engine
	}
}

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	return Quantum::Main(__argc, __argv);
}
