#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>

class ProcHelper
{
public:
	ProcHelper(const char* processName);
	BYTE* GetNtBaseAddr();
	HMODULE GetNtHmodule();
	HANDLE GetProcHandle();
	BOOL Is64BitProcess();
	DWORD procID;
	const char* procName;
private:
	HANDLE hProc;
	MODULEENTRY32 modNtEntry;
	DWORD GetProcessByName(const char* processName);
	MODULEENTRY32 GetNtdllModule();
};

