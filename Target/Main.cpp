#include <iostream>
#include <Windows.h>

int main() {
	for (size_t i = 0;;i++) {
		std::cout << i << std::endl;
		Sleep(1000);
	}
}