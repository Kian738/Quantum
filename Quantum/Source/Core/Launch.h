#pragma once

#include "Core.h"
#include "Engine.h"

extern Quantum::String GetProjectName();

namespace Quantum
{
	int Main(int argc, char** argv)
	{
		auto projectName = GetProjectName();
		Project::Load(projectName);

		Config::Initialize();
		Log::Initialize();

		auto [date, time] = DateTime::FromCompileTime().GetDateTime();
		LOG(Info, LogCommon, "QuantumEngine built on {} at {}", date, time); // TODO: Add version number

		// TODO: Parse command line arguments
 		Engine* engine = new Engine;
		auto status = engine->Run();
		delete engine;

		Log::Shutdown();

		Project::GetActive()->Save();

		return status;
	}
}

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	return Quantum::Main(__argc, __argv);
}
