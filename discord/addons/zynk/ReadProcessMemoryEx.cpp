#include "addon.h"

BOOL ReadProcessMemoryEx(LPCSTR szExeFile, LPVOID lpBaseAddress, LPVOID lpBuffer, SIZE_T nSize) {
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
	HANDLE hProcess = OpenProcess(PROCESS_VM_READ, FALSE, dwProcessId);
	if (!hProcess) {
		return FALSE;
	}

	SIZE_T lpNumberOfBytesRead;
	if (!ReadProcessMemory(hProcess, lpBaseAddress, lpBuffer, nSize, &lpNumberOfBytesRead)) {
		CloseHandle(hProcess);
		return FALSE;
	};

	CloseHandle(hProcess);
	return lpNumberOfBytesRead;
}
