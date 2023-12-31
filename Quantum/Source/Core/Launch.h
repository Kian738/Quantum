#pragma once

#include "Core.h"

extern Quantum::AppContext* GetAppContext();

namespace Quantum
{
	int Main(int argc, char** argv)
	{
		auto appContext = GetAppContext();

		Project::Load(appContext->GetProjectPath());

		Config::Initialize();
		Log::Initialize();

		if (!Project::GetActive()->IsLoaded())
			LOG(Fatal, LogCommon, "Failed to load project");

		Config::PrintStatus();

		auto [date, time] = DateTime::FromCompileTime().GetDateTime();
		LOG(Info, LogCommon, "QuantumEngine built on {} at {}", date, time); // TODO: Add version number (e.g. 2023.1P)

		// TODO: Parse command line arguments
		GEngine = new Engine(appContext);
		GEngine->Initialize();

		GEngine->Run();

		auto status = GEngine->GetExitCode();
		delete GEngine;
		GEngine = nullptr;

		delete appContext;
		appContext = nullptr;

		Log::Shutdown();

		return status;
	}
}

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	return Quantum::Main(__argc, __argv);
}

int main(int argc, char** argv)
{
	return Quantum::Main(argc, argv);
}
