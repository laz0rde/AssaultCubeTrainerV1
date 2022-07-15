#include <iostream>
#include <vector>
#include <Windows.h>
#include <iostream>
#include "proc.h"
#include "mem.h"

int main()
{
    HANDLE hProcess = 0;

    uintptr_t moduleBase = 0, localPlayerPtr = 0, healthPtr = 0;
    bool bHealth = 0, bAmmo = 0;

    const int newValue = 1337;

    DWORD procId = GetProcId(L"ac_client.exe");

    if (procId) {
        hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);
        moduleBase = GetModuleBaseAddress(procId, L"ac_client.exe");
        localPlayerPtr = moduleBase + 0x10f4f4;
        healthPtr = FindDMAAddy(hProcess, localPlayerPtr, { 0xf8 });
    }
    else {
        std::cout << "Process Not Found\n";
    }

    DWORD dwExit = 0;

    while (GetExitCodeProcess(hProcess, &dwExit) && dwExit == STILL_ACTIVE) {
        if (GetAsyncKeyState(VK_F1) & 1) {
            bHealth = !bHealth;
        }

        if (GetAsyncKeyState(VK_F9) & 1) {
            bAmmo = !bAmmo;

            if (bAmmo) {
                mem::PatchEx((BYTE*)(moduleBase + 0x637e9), (BYTE*)"\x90\x90", 2, hProcess);
            }
            else {
                mem::PatchEx((BYTE*)(moduleBase + 0x637e9), (BYTE*)"\xff\x0e", 2, hProcess);
            }
        }

        if (bHealth) {
            mem::PatchEx((BYTE*)healthPtr, (BYTE*)&newValue, sizeof(newValue), hProcess);
        }

        Sleep(10);
    }

    return 0;
}
