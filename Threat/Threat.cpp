#include <iostream>
#include <Windows.h>
#include <ios>

// Should hijack target thread right here :)

CONTEXT GetAndPrintContext(HANDLE hThread) {
	CONTEXT context = { };
	context.ContextFlags = CONTEXT_FULL;

	if (GetThreadContext(hThread, &context)) {

	}

	return context;
}

int main() {
	HANDLE hThread;
	CONTEXT context;

	hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, 6248);
	if (!hThread) {
		std::cout << "Failed to open thread handle : " << GetLastError() << std::endl;
		return 1;
	}

	std::cout << "Successfully opened thread 0x" << hThread << std::endl;

	context = GetAndPrintContext(hThread);

	std::cout << "0x7ffad8f3cca4" << std::endl;

	#ifdef _WIN64
		std::cout << "RIP (Instruction Pointer): 0x" << std::hex << context.Rip << std::endl;
		std::cout << "RSP (Stack Pointer): 0x" << std::hex << context.Rsp << std::endl;
	#endif


	if (SuspendThread(hThread) == -1) {
		std::cout << "Failed to suspend thread : " << GetLastError() << std::endl;
		return 1;
	}

	std::cout << "Sucessfully suspended thread" << std::endl;

	//Sleep(3000);

	if (ResumeThread(hThread) == -1) {
		std::cout << "Failed to resume thread : " << GetLastError() << std::endl;
		return 1;
	}
	
	std::cout << "Sucessfully resumed thread" << std::endl;
}