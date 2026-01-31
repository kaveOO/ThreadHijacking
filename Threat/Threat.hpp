#pragma once

#include <iostream>
#include <Windows.h>
#include <ios>
#include <Psapi.h>
#include <tchar.h>

#include "Process.hpp"

class Threat : protected Process {
	private:
		HANDLE	hThread = {};
		CONTEXT	context = {};
		DWORD	threadId = 0;
	public:
		Threat() = delete;
		Threat(const wchar_t *processName);
		~Threat();

		void	DebugPrint() const;
		bool	Hijack();
};