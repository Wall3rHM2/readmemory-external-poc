
/*
	GMOD
	LocalPlayer = 0x0076CAFC
	HP = 0x0090
*/
#include <Windows.h>
#include <conio.h>
#include <tlhelp32.h>
#include <string>
#include <psapi.h>
#include <iostream>
#include <wchar.h>
#pragma comment( lib, "psapi" )

#define LocalPlayer 0x0076CAFC
#define HP 0x0090

DWORD getProcessID(const wchar_t* processName)
{
	DWORD pid;
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (Process32First(snapshot, &entry) == TRUE)
	{
		while (Process32Next(snapshot, &entry) == TRUE)
		{
			if (wcscmp(entry.szExeFile, processName) == 0) //when the process is found
			{
				pid = entry.th32ProcessID;
			}
		}
	}

	CloseHandle(snapshot);
	return pid;
}

int ReadMemoryInt(HANDLE processHandle, LPCVOID address)
{
	int buffer = 0;
	SIZE_T NumberOfBytesToRead = sizeof(buffer); //this is equal to 4
	SIZE_T NumberOfBytesActuallyRead;
	BOOL err = ReadProcessMemory(processHandle, address, &buffer, NumberOfBytesToRead, &NumberOfBytesActuallyRead);
	if (err || NumberOfBytesActuallyRead != NumberOfBytesToRead)
		/*an error occured*/;
	return buffer;
}


int getModule(wchar_t moduleName[], HMODULE modules[2024], HANDLE process, HMODULE* mainModule)
{//208
	TCHAR lastModule[MAX_PATH];
	for (int i = 0; i < sizeof(modules) / sizeof(HMODULE) + 2024; i++) { //searches for main module inside all modules array
		TCHAR module[MAX_PATH];
		//std::wcout << " *beep: " << i << "\n";
		GetModuleFileNameEx(process, modules[i], module, sizeof(module) / sizeof(TCHAR));
		if (wcsstr(module, lastModule) == NULL) { // print module and dont repeat same module
			std::wcout << "*module List: " << module << "\n";
		}
		wcsncpy_s(lastModule, module, sizeof(module) / sizeof(TCHAR));
		//std::wcout << "*module List: " << module << "\n";
		//std::wcout << module << "\n";
		if (wcsstr(module, moduleName) != NULL)
		{
			*mainModule = modules[i];
			std::wcout << "found generic module: " << module << "\n";
			return 0;
		}
	}
	return 0;
}




int main()
{
	const wchar_t* processName = L"hl2.exe";
	DWORD pid = getProcessID(processName);
	HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (process == NULL) return 0;
	TCHAR mainExeName[MAX_PATH];
	//HMODULE mainModule;
	HMODULE clientModule;
	HMODULE modules[2024];
	MODULEINFO mainInfo;
	MODULEINFO clientInfo;
	DWORD sbNeeded;

	std::wcout << "pid: " << pid << "\n";
	std::wcout << "process: " << process << "\n";
	if (!GetProcessImageFileName(process, mainExeName, MAX_PATH))
	{
		std::cout << "Error in GetProcessImageFileName\n";
	}
	std::wcout << "main exe name: " << mainExeName << "\n";
	EnumProcessModules(process, modules, sizeof(modules), &sbNeeded);
	wchar_t clientDLLName[] = L"\\bin\\client.dll";
	getModule(clientDLLName, modules, process, &clientModule);

	DWORD LocalPlayerPointer;
	ReadProcessMemory(process, (PBYTE*)((DWORD)clientModule + LocalPlayer), &LocalPlayerPointer, sizeof(DWORD), 0);
	int foo = ReadMemoryInt(process, (void*)LocalPlayerPointer); //LocalPlayer pointer address
	int health = ReadMemoryInt(process, (void*)(LocalPlayerPointer + HP));
	//std::wcout << "Health value: " << foo << "\n";
	std::wcout << "\n\nHealth value: " << health << "\n";

	return 0;
}