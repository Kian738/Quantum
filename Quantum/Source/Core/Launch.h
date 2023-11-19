#pragma once

#include "Engine.h"
#include <Windows.h>

extern Quantum::Engine* CreateEngine();

namespace Quantum
{
	int Main(int argc, char** argv);
}

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	return Quantum::Main(__argc, __argv);
}
