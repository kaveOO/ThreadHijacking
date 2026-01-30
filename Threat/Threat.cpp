#include <iostream>
#include <Windows.h>

// Should hijack target thread right here :)

CONTEXT getThreadContext(HANDLE hThread) {
	CONTEXT context;
	GetThreadContext(hThread, &context);
	return context;
}

int main() {
	HANDLE hThread;
	CONTEXT context;

	hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, 22408);
	if (!hThread) {
		std::cout << "Failed to open thread handle : " << GetLastError() << std::endl;
		return 1;
	}

	std::cout << "Successfully opened thread 0x" << hThread << std::endl;

	context = getThreadContext(hThread);

	std::cout << context.ContextFlags << std::endl;

	//if (SuspendThread(hThread) == -1) {
	//	std::cout << "Failed to suspend thread : " << GetLastError() << std::endl;
	//	return 1;
	//}

	//std::cout << "Sucessfully suspended thread" << std::endl;

	//Sleep(3000);

	//if (ResumeThread(hThread) == -1) {
	//	std::cout << "Failed to resume thread : " << GetLastError() << std::endl;
	//	return 1;
	//}
	//
	//std::cout << "Sucessfully resumed thread" << std::endl;
}