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

		atexit(Log::Shutdown);

		auto [date, time] = DateTime::FromCompileTime().GetDateTime();
		LOG(Info, LogCommon, "QuantumEngine built on {} at {}", date, time); // TODO: Add version number

		// TODO: Parse command line arguments
		GEngine = new Engine;
		GEngine->Initialize(); // TODO: Pass appContext to engine

		GEngine->Run();

		auto status = GEngine->GetExitCode();
		delete GEngine;
		GEngine = nullptr;

		return status;
	}
}

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	return Quantum::Main(__argc, __argv);
}
