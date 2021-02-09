#include "addon.h"

DWORD GetProcessIdEx(LPCSTR szExeFile) {
	PROCESSENTRY32 lppe;
	lppe.dwSize = sizeof(lppe);

	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (hSnapshot == INVALID_HANDLE_VALUE) {
		return NULL;
	}

	Process32First(hSnapshot, &lppe);
	if (!strcmp(szExeFile, lppe.szExeFile)) {
		CloseHandle(hSnapshot);
		return lppe.th32ProcessID;
	}

	while (Process32Next(hSnapshot, &lppe)) {
		if (!strcmp(szExeFile, lppe.szExeFile)) {
			CloseHandle(hSnapshot);
			return lppe.th32ProcessID;
		}
	}

	CloseHandle(hSnapshot);
	return NULL;
}
