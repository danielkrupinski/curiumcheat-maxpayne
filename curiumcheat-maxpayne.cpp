#include <iostream>
#include <Windows.h>
#include <tlhelp32.h>

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

				printf("Process found!");
				Sleep(1500);
				system("cls");
				printf("Cheat activated!");

				float bullettime = 1.0;
				size_t base = 0;

				for (;;)
				{
					/* Get base address */
					ReadProcessMemory(hProcess, (LPVOID)(0x04CA59B4), &base, sizeof(int), 0); // sndmfc.dll(0x4C90000)+0x159B4
					ReadProcessMemory(hProcess, (LPVOID)(base + 0xC), &base, sizeof(int), 0); // 0xC - first offset
					ReadProcessMemory(hProcess, (LPVOID)(base + 0x8), &base, sizeof(int), 0); // 0x8 - second offset
					ReadProcessMemory(hProcess, (LPVOID)(base + 0xF4), &base, sizeof(int), 0); // 0xF4 - third offset
					WriteProcessMemory(hProcess, (LPVOID)(base + 0x7A4), &bullettime, sizeof(bullettime), 0); // infinite bullet time - base + 0x7A4
					Sleep(1);
				}
				CloseHandle(hProcess);
			}
		}
	}
	CloseHandle(snapshot);
	return 0;
}
