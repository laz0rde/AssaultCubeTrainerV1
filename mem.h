#pragma once
#include <vector>
#include <Windows.h>
#include <TlHelp32.h>

namespace mem {
	void PatchEx(BYTE* dst, BYTE* src, unsigned int size, HANDLE hprocess);
}


