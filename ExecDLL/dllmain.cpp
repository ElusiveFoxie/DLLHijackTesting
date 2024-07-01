// dllmain.cpp : Defines the entry point for the DLL application.
#include "windows.h"
#include "pch.h" 

void run() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Create the process
    if (CreateProcess(L"C:\\Windows\\System32\\calc.exe",   // No module name (use command line)
        NULL,                                 // Command line
        NULL,                                 // Process handle not inheritable
        NULL,                                 // Thread handle not inheritable
        FALSE,                                // Set handle inheritance to FALSE
        0,                                    // No creation flags
        NULL,                                 // Use parent's environment block
        NULL,                                 // Use parent's starting directory
        &si,                                  // Pointer to STARTUPINFO structure
        &pi))                                 // Pointer to PROCESS_INFORMATION structure
    {
        // Here, pi.hProcess and pi.hThread contain handles to the process and its primary thread.
        // Wait for the process to finish execution
        WaitForSingleObject(pi.hProcess, INFINITE);

        // Close process and thread handles.
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    else
    {
        // Handle the error
        DWORD dwError = GetLastError();
        // Convert and log the error, handle as needed
    }
}

extern "C" __declspec(dllexport) void CALLBACK RunCalc(HWND hwnd, HINSTANCE hinst, LPSTR lpszCmdLine, int nCmdShow)
{
    run();
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        run();
        FreeLibraryAndExitThread(hModule, 0);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

