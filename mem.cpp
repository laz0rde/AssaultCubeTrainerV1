#include "mem.h"

void mem::PatchEx(BYTE* dst, BYTE* src, unsigned int size, HANDLE hprocess) {
	DWORD oldProtect;
	VirtualProtectEx(hprocess, dst, size, PAGE_EXECUTE_READWRITE, &oldProtect);
	WriteProcessMemory(hprocess, dst, src, size, nullptr);
	VirtualProtectEx(hprocess, dst, size, oldProtect, &oldProtect);
}
