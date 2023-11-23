#include "Console.h"
#include "Core/Core.h"
#include <iostream>
#include <format>

namespace Quantum
{
	bool Console::m_IsAllocated = false;

	void Console::Allocate()
	{
		if (m_IsAllocated)
			return;

		std::cin.tie(0);
		std::cout.tie(0);
		std::ios_base::sync_with_stdio(false);

		AllocConsole();
		SetConsoleTitleA(std::format("{} - Console", App::GetName()).c_str());

		FILE* file = nullptr;
		freopen_s(&file, "CONIN$", "r", stdin);
		freopen_s(&file, "CONOUT$", "w", stdout);

		auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
		if (handle != INVALID_HANDLE_VALUE)
		{
			DWORD dwMode = 0;
			GetConsoleMode(handle, &dwMode);
			dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
			SetConsoleMode(handle, dwMode);
		}

		m_IsAllocated = true;
	}

	void Console::Free()
	{
		if (!m_IsAllocated)
			return;

		FreeConsole();

		m_IsAllocated = false;
	}
}
