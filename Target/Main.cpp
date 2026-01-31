#include <iostream>
#include <Windows.h>

int main() {
	for (size_t i = 0;;i++) {
		//std::cout << i << std::endl;
		//Sleep(3000);
		if (i == 10000000000) {
			std::cout << i << std::endl;
			Sleep(1000);
		}
		
		if (i == 10000000042) {
			std::cout << "test" << std::endl;
		}
	}
}