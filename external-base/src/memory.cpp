#include "..\include\memory.h"
#include <iostream>
#include <windows.h>
#include <tlhelp32.h>

uintptr_t Memory::baseAddress = 0;
bool Memory::isInitialized = false;

void Memory::Initialize() {
	std::cout << "[*] Memory module initializing...\n";
	isInitialized = true;
	std::cout << "[+] Memory module ready\n";
}

void Memory::ScanMemory() {
	if(!isInitialized) return;
	std::cout << "[*] Scanning...\n";
}

void Memory::Update() {
	if(!isInitialized) return;
}

void Memory::Cleanup() {
	std::cout << "[*] Memory cleanup\n";
	isInitialized = false;
}

uintptr_t GetModuleBaseAddress(const char* moduleName) {
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetCurrentProcessId());
	if(snapshot == INVALID_HANDLE_VALUE) return 0;

	MODULEENTRY32 entry = {};
	entry.dwSize = sizeof(MODULEENTRY32);

	if(Module32First(snapshot, &entry)) {
		do {
			if(strcmp((const char*)entry.szModule, moduleName) == 0) {
				CloseHandle(snapshot);
				return (uintptr_t)entry.modBaseAddr;
			}
		} while(Module32Next(snapshot, &entry));
	}

	CloseHandle(snapshot);
	return 0;
}
