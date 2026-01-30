#pragma once

#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>

class Process {
	private:
		DWORD	processId = 0;
		HANDLE	hProcess = NULL;
	public:
		Process() = delete;
		Process(const wchar_t *processName);
		~Process();

		DWORD	GetProcessId()		const;
		HANDLE	GetProcessHandle()	const;
};