#include "Threat.hpp"

Threat::Threat(const wchar_t *processName) : Process(processName) {
	context.ContextFlags = CONTEXT_FULL;

	HANDLE			hSnapshot;
	THREADENTRY32	threadEntry = {};
	BOOL			hResult;

	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (hSnapshot == INVALID_HANDLE_VALUE) {
		std::cerr << "Failed to snapshot threads: " << GetLastError() << std::endl;
		return;
	}

	threadEntry.dwSize = sizeof(THREADENTRY32);
	hResult = Thread32First(hSnapshot, &threadEntry);

	while (hResult) {
		if (processId == threadEntry.th32OwnerProcessID) {
			threadId = threadEntry.th32ThreadID;
			break;
		}
		hResult = Thread32Next(hSnapshot, &threadEntry);
	}

	CloseHandle(hSnapshot);

	hThread = OpenThread(THREAD_ALL_ACCESS, 0, threadId);
	if (!hThread) {
		std::cerr << "[ ERROR ] OpenThread: " << GetLastError() << std::endl;
		return;
	}
}

Threat::~Threat() {
	CloseHandle(hThread);
}

void Threat::DebugPrint() const {
	std::cout << "-------------------------" << std::endl;
	std::cout << " THIS IS A DEBUG PRINT ! " << std::endl;
	std::cout << "-------------------------" << std::endl;
	std::cout << "[ DEBUG ] processId: " << processId << std::endl;
	std::cout << "[ DEBUG ] threadId: " << threadId << std::endl;
	std::cout << "[ DEBUG ] context: 0x" << std::hex << &context << std::endl;
	std::cout << "[ DEBUG ] hThread: 0x" << std::hex << hThread << std::endl;
}

bool Threat::Hijack() {
	HMODULE hModules[1024];
	DWORD modulesCount;

	if (!EnumProcessModules(hProcess, hModules, sizeof(hModules), &modulesCount)) {
		std::cerr << "[ ERROR ] EnumProcessModules: " << GetLastError() << std::endl;
		CloseHandle(hProcess);
		return false;
	}

	HMODULE ntdll = nullptr;

	for (size_t i = 0; i < (modulesCount / sizeof(HMODULE)); i++) {
		TCHAR path[MAX_PATH];

		if (!GetModuleFileNameEx(hProcess, hModules[i], path, sizeof(path) / sizeof(TCHAR))) {
			std::cerr << "[ ERROR ] GetModuleFileNameA: " << GetLastError() << std::endl;
			return false;
		}

		if (_tcsstr(path, L"ntdll.dll") == 0) {
			std::cout << "[ DEBUG ] ntdll found!" << std::endl;
			break;
		}

		MODULEINFO moduleInfos;
		
		if (!K32GetModuleInformation(hProcess, hModules[i], &moduleInfos, sizeof(moduleInfos))) {
			std::cerr << "[ ERROR ] K32GetModuleInformation: " << GetLastError() << std::endl;
			return false;
		}

		std::cout << moduleInfos.SizeOfImage << std::endl;
		

		std::wcout << path << std::endl;
	}

	while (1) {
		if (SuspendThread(hThread) == (DWORD) -1) {
			std::cerr << "[ ERROR ] SuspendThread: " << GetLastError() << std::endl;
			return false;
		}

		std::cout << "[ DEBUG ] SuspendThread" << std::endl;

		if (!GetThreadContext(hThread, &context)) {
			std::cerr << "[ ERROR ] GetThreadContext: " << GetLastError() << std::endl; 
			if (ResumeThread(hThread) == (DWORD) - 1) {
				std::cerr << "[ ERROR ] ResumeThread: " << GetLastError() << std::endl;
			}
		}
	
		Sleep(1000);
		std::cout << "Resume in 3..." << std::endl;
		Sleep(1000);
		std::cout << "Resume in 2..." << std::endl;
		Sleep(1000);
		std::cout << "Resume in 1..." << std::endl;

		if (ResumeThread(hThread) == (DWORD) -1) {
			std::cerr << "[ ERROR ] ResumeThread: " << GetLastError() << std::endl;
			return false;
		}
		std::cout << "[ DEBUG ] ResumeThread" << std::endl;

		Sleep(5000);
	}
}