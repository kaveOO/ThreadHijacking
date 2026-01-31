#include "Process.hpp"

Process::Process(const wchar_t *processName) {
	HANDLE			hSnapshot;
	PROCESSENTRY32	processEntry = {};
	BOOL			hResult;

	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot == INVALID_HANDLE_VALUE) {
		std::cerr << "Failed to snapshot processes: " << GetLastError() << std::endl;
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

	CloseHandle(hSnapshot);

	if (processId == 0) {
		std::cerr << "[ ERROR ] Failed to get processId: " << GetLastError() << std::endl;
		return;
	}

	hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, processId);
	if (!hProcess) {
		std::cerr << "[ ERROR ] OpenProcess: " << GetLastError() << std::endl;
		return;
	}
}

Process::~Process() {
}