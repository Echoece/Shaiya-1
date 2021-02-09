#pragma once
#include <windows.h>
#include <tlhelp32.h>
#include <napi.h>

DWORD GetProcessIdEx(
	LPCSTR szExeFile
);

BOOL ReadProcessMemoryEx(
	LPCSTR szExeFile, 
	LPVOID lpBaseAddress, 
	LPVOID lpBuffer, 
	SIZE_T nSize
);

BOOL WriteProcessMemoryEx(
	LPCSTR szExeFile, 
	LPVOID lpBaseAddress, 
	LPCVOID lpBuffer, 
	SIZE_T nSize
);

BOOL SetSeDebugPrivilege();
