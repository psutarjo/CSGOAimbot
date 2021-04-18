#include <Windows.h>
#include <iostream>
#include "Source.h"

// DWORD is defined in Windows.h as a 32-bit unsigned integer

DWORD WINAPI OnDllAttach(PVOID base)
{
#ifdef _DEBUG

	// Spawn a console window and redirect the input/output streams when we have a debug build

	AllocConsole();
	freopen_s((FILE**)stdin, "COININ", "r", stdin);
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	SetConsoleTitleA("CSGO-Aimbot");
#endif

	// Pressing the delete key will stop the cheat

	while (!(GetAsyncKeyState(VK_DELETE) & 0x8000))
	{
		Run();
		Sleep(1);
	}
	// Unload the DLL and terminate the thread

	FreeLibraryAndExitThread(static_cast<HMODULE>(base), 0);
}

VOID WINAPI OnDllDetach()
{
#ifdef _DEBUG
	fclose((FILE*)stdin);
	fclose((FILE*)stdout);

	HWND hw_ConsoleHwnd = GetConsoleWindow();
	FreeConsole();
	PostMessageW(hw_ConsoleHwnd, WM_CLOSE, 0, 0);
#endif
}

// When the system starts or terminates a process or thread, it calls the entry-point function for each loaded DLL using
// the first thread of the process. The system also calls the entry-point function
// for a DLL when it is loaded or unloaded using the LoadLibrary and FreeLibrary functions.

// hModule: handle to dll module
// dwReason: can either be DLL_PROCESS_ATTACH(0), DLL_PROCESS_DETACH(1), DLL_THREAD_ATTACH(2), or DLL_THREAD_DETACH(3)
// lpReserved: On DllAttach, the lpReserved parameter indicates whether the DLL is being loaded statically or dynamically.
//			   For DllDetach, The lpReserved parameter indicates whether the DLL is being unloaded
//             as a result of a FreeLibrary call a failure to load, or process termination.

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH) {

		// Make a call to DisableThreadLibraryCalls with the hModule variable
		// as its argument; Doing this is an optimization trick to prevent
		// needless thread attach/detach messages from triggering further calls
		// to our DllMain function.

		DisableThreadLibraryCalls(hModule);

		// Creates a thread to execute within the virtual address space of the calling process.

		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)OnDllAttach, hModule, NULL, NULL);
	}
	else if (dwReason == DLL_PROCESS_DETACH) {
		OnDllDetach();
	}
	return TRUE;
}
