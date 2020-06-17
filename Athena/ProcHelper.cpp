#include "ProcHelper.h"

ProcHelper::ProcHelper(const char* processName) {
    this->procName = processName;
    //Search for process ID
    this->procID = this->GetProcessByName(this->procName);
    //Open handle to process
    this->hProc = OpenProcess(PROCESS_ALL_ACCESS, false, this->procID);
    //TODO: Clean up if ntdll not loaded in process
    this->modNtEntry = this->GetNtdllModule();

    std::cout << "[+] Process Name : " << this->procName << std::endl;
    std::cout << "[+] Process ID : " << this->procID << std::endl;
    std::cout << std::boolalpha;
    std::cout << "[+] Is 64 bit : " << (BOOL)this->Is64BitProcess() << std::endl;

}

HANDLE ProcHelper::GetProcHandle() {
    return this->hProc;
}

BYTE* ProcHelper::GetNtBaseAddr() {
    BYTE* baseAddr = this->modNtEntry.modBaseAddr;
    return baseAddr;
}

HMODULE ProcHelper::GetNtHmodule() {
    return this->modNtEntry.hModule;
}

BOOL ProcHelper::Is64BitProcess() {
    BOOL bIsWow64 = FALSE;

    if (!IsWow64Process(this->hProc, &bIsWow64)) {
        std::cout << "[!] Unable to determine if 64 bit" << std::endl;
        return FALSE;
    }

    return bIsWow64;
}

DWORD ProcHelper::GetProcessByName(const char* procName) {
    HANDLE hSnap;
    BOOL done;
    PROCESSENTRY32 procEntry;

    ZeroMemory(&procEntry, sizeof(PROCESSENTRY32));
    procEntry.dwSize = sizeof(PROCESSENTRY32);

    hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    done = Process32First(hSnap, &procEntry);
    do {
        if (_strnicmp(procEntry.szExeFile, procName, sizeof(procEntry.szExeFile)) == 0) {
            return procEntry.th32ProcessID;
        }
    } while (Process32Next(hSnap, &procEntry));

    return 0;
}

MODULEENTRY32 ProcHelper::GetNtdllModule() {
    HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
    MODULEENTRY32 modEntry32;

    hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, this->procID);
    if (hModuleSnap == INVALID_HANDLE_VALUE) {
        return MODULEENTRY32{ 0 };
    }

    modEntry32.dwSize = sizeof(MODULEENTRY32);

    if (!Module32First(hModuleSnap, &modEntry32)) {
        CloseHandle(hModuleSnap);
        return modEntry32;
    }

    do {
        if (_strnicmp((char*)modEntry32.szModule, "ntdll.dll", sizeof(modEntry32.szModule)) == 0) {
            return modEntry32;
        }
    } while (Module32Next(hModuleSnap, &modEntry32));

    CloseHandle(hModuleSnap);

    return MODULEENTRY32{ 0 };
}