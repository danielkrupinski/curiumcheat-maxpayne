#include <iostream>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <tlhelp32.h>
#include <tchar.h>

DWORD_PTR dwGetModuleBaseAddress(DWORD dwProcID, TCHAR *szModuleName)
{
	DWORD_PTR dwModuleBaseAddress = 0;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcID);
	if (hSnapshot != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 ModuleEntry32;
		ModuleEntry32.dwSize = sizeof(MODULEENTRY32);
		if (Module32First(hSnapshot, &ModuleEntry32))
		{
			do
			{
				if (_tcsicmp(ModuleEntry32.szModule, szModuleName) == 0)
				{
					dwModuleBaseAddress = (DWORD_PTR)ModuleEntry32.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnapshot, &ModuleEntry32));
		}
		CloseHandle(hSnapshot);
	}
	return dwModuleBaseAddress;
}

int main()
{
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (Process32First(snapshot, &entry) == TRUE)
	{
		while (Process32Next(snapshot, &entry) == TRUE)
		{
			if (_stricmp(entry.szExeFile, "MaxPayne.exe") == 0)
			{
				HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);
				
				DWORD_PTR sndmfcdlladress = dwGetModuleBaseAddress(entry.th32ProcessID, (TCHAR*)("sndmfc.dll"));

				printf("Process found!");
				Sleep(1000);
				system("cls");
				printf("Cheat activated!");

				float bullettime = 1.0;
				size_t base = 0;

				while (true)
				{
					ReadProcessMemory(hProcess, (LPVOID)(sndmfcdlladress +0x159B4), &base, sizeof(int), 0);
					ReadProcessMemory(hProcess, (LPVOID)(base + 0xC), &base, sizeof(int), 0);
					ReadProcessMemory(hProcess, (LPVOID)(base + 0x8), &base, sizeof(int), 0);
					ReadProcessMemory(hProcess, (LPVOID)(base + 0xF4), &base, sizeof(int), 0);
					WriteProcessMemory(hProcess, (LPVOID)(base + 0x7A4), &bullettime, sizeof(bullettime), 0);
					Sleep(1);
				}
				CloseHandle(hProcess);
			}
		}
	}
	CloseHandle(snapshot);
	return 0;
}
