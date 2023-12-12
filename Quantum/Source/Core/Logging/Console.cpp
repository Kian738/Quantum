#include "Console.h"

#include "Core/Core.h"
#include <iostream>

namespace Quantum
{
	static int WINAPI ConsoleCtrlHandler(DWORD dwCtrlType)
	{
		switch (dwCtrlType)
		{
		case CTRL_C_EVENT:
		case CTRL_CLOSE_EVENT:
		case CTRL_BREAK_EVENT:
		case CTRL_LOGOFF_EVENT:
		case CTRL_SHUTDOWN_EVENT:
			if (GEngine)
				GEngine->Stop(); // TODO: Make this finish clean up in Launch.h
			[[fallthrough]];
		default:
			return FALSE;
		}
	}

	void Console::Allocate()
	{
		std::cin.tie(0);
		std::cout.tie(0);
		std::ios_base::sync_with_stdio(false);

		AllocConsole();
		SetConsoleTitleA(std::format("{} - Console", App::GetName()).c_str());
		SetConsoleCtrlHandler(ConsoleCtrlHandler, TRUE);

		FILE* file = nullptr;
		freopen_s(&file, "CONIN$", "r", stdin);
		freopen_s(&file, "CONOUT$", "w", stdout);

		if (auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
			handle != INVALID_HANDLE_VALUE)
		{
			DWORD dwMode = 0;
			GetConsoleMode(handle, &dwMode);
			dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
			SetConsoleMode(handle, dwMode);
		}

		s_IsAllocated = true;
	}

	void Console::Free()
	{
		FreeConsole();

		s_IsAllocated = false;
	}
}
