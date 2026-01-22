#include <iostream>
#include <Windows.h>

// Should hijack target thread right here :)

int main() {
	HANDLE hThread;

	hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, 2540);
	if (!hThread) {
		std::cout << "Failed to open thread handle : " << GetLastError() << std::endl;
		return 1;
	}

	std::cout << "Successfully opened thread 0x" << hThread << std::endl;

	if (SuspendThread(hThread) == -1) {
		std::cout << "Failed to suspend thread : " << GetLastError() << std::endl;
		return 1;
	}

	std::cout << "Sucessfully suspended thread" << std::endl;

	Sleep(3000);

	if (ResumeThread(hThread) == -1) {
		std::cout << "Failed to resume thread : " << GetLastError() << std::endl;
		return 1;
	}
	
	std::cout << "Sucessfully resumed thread" << std::endl;
}