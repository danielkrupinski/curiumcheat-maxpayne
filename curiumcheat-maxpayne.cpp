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
					getchar();

					CloseHandle(hProcess);
				}
			}
		}

	CloseHandle(snapshot);
    return 0;
}
