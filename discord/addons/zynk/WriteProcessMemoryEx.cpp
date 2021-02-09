#include "addon.h"

BOOL WriteProcessMemoryEx(LPCSTR szExeFile, LPVOID lpBaseAddress, LPCVOID lpBuffer, SIZE_T nSize) {
	PROCESSENTRY32 lppe;
	lppe.dwSize = sizeof(lppe);
	DWORD dwProcessId = NULL;

	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (hSnapshot == INVALID_HANDLE_VALUE) {
		return FALSE;
	}

	Process32First(hSnapshot, &lppe);
	if (!strcmp(szExeFile, lppe.szExeFile)) {
		CloseHandle(hSnapshot);
		dwProcessId = lppe.th32ProcessID;
		goto label;
	}

	while (Process32Next(hSnapshot, &lppe)) {
		if (!strcmp(szExeFile, lppe.szExeFile)) {
			CloseHandle(hSnapshot);
			dwProcessId = lppe.th32ProcessID;
			goto label;
		}
	}

	CloseHandle(hSnapshot);
	return FALSE;

	label:
	HANDLE hProcess = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_WRITE, FALSE, dwProcessId);
	if (!hProcess) {
		return FALSE;
	}
	
	DWORD lpflOldProtect;
	if (!VirtualProtectEx(hProcess, lpBaseAddress, nSize, PAGE_EXECUTE_READWRITE, &lpflOldProtect)) {
		CloseHandle(hProcess);
		return FALSE;
	}
	
	SIZE_T lpNumberOfBytesWritten;
	if (!WriteProcessMemory(hProcess, lpBaseAddress, lpBuffer, nSize, &lpNumberOfBytesWritten)) {
		CloseHandle(hProcess);
		return FALSE;
	}
	
	DWORD flNewProtect = lpflOldProtect;
	if (!VirtualProtectEx(hProcess, lpBaseAddress, nSize, flNewProtect, &lpflOldProtect)) {
		CloseHandle(hProcess);
		return FALSE;
	}

	CloseHandle(hProcess);
	return lpNumberOfBytesWritten;
}
