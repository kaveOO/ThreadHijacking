#pragma once

#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>

class Process {
	protected:
		DWORD	processId = 0;
		HANDLE	hProcess = NULL;
	public:
		Process() = delete;
		Process(const wchar_t *processName);
		~Process();
};