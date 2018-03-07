#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <psapi.h>
#include <tlhelp32.h>
//required function calls

void PrintProcessAndID(DWORD processID)
{
	//Writes unknown if name exceeds maxpath
	TCHAR ProcessName[MAX_PATH] = TEXT("<unknown>");

	//Gets intial process handle.
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
		PROCESS_VM_READ,
		FALSE, processID);

	//Gets the process name.
	if (NULL != hProcess)
	{
		HMODULE hMod;
		DWORD cbNeeded;

		if (EnumProcessModules(hProcess, &hMod, sizeof(hMod),
			&cbNeeded))
		{
			GetModuleBaseName(hProcess, hMod, ProcessName,
				sizeof(ProcessName) / sizeof(TCHAR));
		}
	}

	_tprintf(TEXT("%s  (PID: %u)\n"), ProcessName, processID);

	//Closes handle to process.
	CloseHandle(hProcess);
}

//Main method that calls on PrintNameAndID
int main(void)
{
	//Obtains process identifiers
	DWORD aProcesses[1024], cbNeeded, cProcesses;
	unsigned int i;

	if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
	{
		return 1;
	}


	//Returns # of process identifiers
	cProcesses = cbNeeded / sizeof(DWORD);

	//Prints every running process name and ID
	for (i = 0; i < cProcesses; i++)
	{
		if (aProcesses[i] != 0)
		{
			PrintProcessAndID(aProcesses[i]);
		}
	}

	//attempt at obtaining the session name and session ID
	DWORD processIDs[1024];
	DWORD needed;
	EnumProcesses(processIDs, sizeof(processIDs), &needed);
	OpenProcess(PROCESS_ALL_ACCESS, TRUE, processIDs[i]);

	//Breaks system by pausing to view all processes instead of closing out
	system("pause");
	return 0;
}