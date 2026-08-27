#pragma once
#include <cstdint>

class Memory {
public:
	static void Initialize();
	static void ScanMemory();
	static void Update();
	static void Cleanup();

private:
	static uintptr_t baseAddress;
	static bool isInitialized;
};

uintptr_t GetModuleBaseAddress(const char* moduleName);
