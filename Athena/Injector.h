#pragma once
#include <iostream>
#include <Windows.h>
#include "ntdll.h"

class Injector
{
public:
	static void MapLocalSection(HANDLE& sectionHandle, ntdll* nt, PVOID& localSectionAddress, SIZE_T size);
	static void MapRemoteSection(HANDLE& sectionHandle, HANDLE& targetHandle, ntdll* nt, PVOID& remoteSectionAddress, SIZE_T size);
	static void StartThread(HANDLE& targetHandle, PVOID& remoteSectionAddress, ntdll* nt);
};

