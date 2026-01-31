#include "Threat.hpp"

int main() {
	Threat threat(L"Target.exe");
	
	threat.DebugPrint();
	threat.Hijack();
}