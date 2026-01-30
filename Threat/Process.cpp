#include "Process.hpp"

Process::Process(const wchar_t *processName) {
	HANDLE			hSnapshot;
	PROCESSENTRY32	processEntry = {};
	BOOL			hResult;

	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot == INVALID_HANDLE_VALUE) {
		std::cerr << "Failed to create snapshot of processes" << std::endl;
		return;
	}

	processEntry.dwSize = sizeof(PROCESSENTRY32);
	hResult = Process32First(hSnapshot, &processEntry);

	while (hResult) {
		if (wcscmp(processName, processEntry.szExeFile) == 0) {
			processId = processEntry.th32ProcessID;
			break;
		}
		hResult = Process32Next(hSnapshot, &processEntry);
	}

	if (processId == 0) {
		std::wcerr << "Failed to find " << processName << std::endl;
	}

	CloseHandle(hSnapshot);
}

Process::~Process() {
	CloseHandle(hProcess);
}

DWORD Process::GetProcessId() const {
	return processId;
}

HANDLE Process::GetProcessHandle() const {
	return hProcess;
}