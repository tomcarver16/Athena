#include "ntdll.h"

ntdll::ntdll() {
	fNtCreateSection = (myNtCreateSection)(GetProcAddress(GetModuleHandleA("ntdll"), "NtCreateSection"));
	fNtMapViewOfSection = (myNtMapViewOfSection)(GetProcAddress(GetModuleHandleA("ntdll"), "NtMapViewOfSection"));
	fRtlCreateUserThread = (myRtlCreateUserThread)(GetProcAddress(GetModuleHandleA("ntdll"), "RtlCreateUserThread"));
	fNtCreateThreadEx = (myNtCreateThreadEx)(GetProcAddress(GetModuleHandleA("ntdll"), "NtCreateThreadEx"));
	fNtQueueApcThread = (myNtQueueApcThread)(GetProcAddress(GetModuleHandleA("ntdll"), "NtQueueApcThread"));
	fNtAlertResumeThread = (myNtAlertResumeThread)(GetProcAddress(GetModuleHandleA("ntdll"), "NtAlertResumeThread"));
}