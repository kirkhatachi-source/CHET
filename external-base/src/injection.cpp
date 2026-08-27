#include "..\include\injection.h"
#include <iostream>
#include <tlhelp32.h>
#include <psapi.h>

#pragma comment(lib, "psapi.lib")

DWORD ProcessInjector::targetProcessID = 0;
std::string ProcessInjector::targetProcessName = "";
HANDLE ProcessInjector::processHandle = nullptr;
bool ProcessInjector::attached = false;
std::vector<ProcessInfo> ProcessInjector::processList;

void ProcessInjector::Initialize() {
	std::cout << "[*] Process injector initializing...\n";
	std::cout << "[*] Target game: Knives Out\n";
	std::cout << "[*] Loader: hyxd.exe\n";
	std::cout << "[*] Scanning for target processes...\n";
	
	UpdateProcessList();
	EnumerateProcesses();
	
	std::cout << "[+] Process injector ready\n";
}

void ProcessInjector::UpdateProcessList() {
	processList.clear();

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(snapshot == INVALID_HANDLE_VALUE) return;

	PROCESSENTRY32 entry = {};
	entry.dwSize = sizeof(PROCESSENTRY32);

	if(Process32First(snapshot, &entry)) {
		do {
			ProcessInfo info;
			info.processID = entry.th32ProcessID;
			info.processName = (const char*)entry.szExeFile;
			
			// Fake window title lookup
			if(info.processName == "KnivesOut.exe") {
				info.windowTitle = "Knives Out [DETECTED]";
				info.isTarget = true;
			} else if(info.processName == "hyxd.exe") {
				info.windowTitle = "hyxd - Payload Injector";
				info.isTarget = false;
			} else {
				info.windowTitle = info.processName;
				info.isTarget = false;
			}

			processList.push_back(info);
		} while(Process32Next(snapshot, &entry));
	}

	CloseHandle(snapshot);
}

void ProcessInjector::EnumerateProcesses() {
	std::cout << "\n[*] Running processes:\n";

	for(const auto& proc : processList) {
		if(proc.isTarget) {
			std::cout << "  [TARGET] PID: " << proc.processID 
				<< " | Process: " << proc.processName 
				<< " | Window: " << proc.windowTitle << "\n";
		} else if(proc.processName == "hyxd.exe") {
			std::cout << "  [LOADER] PID: " << proc.processID 
				<< " | Process: " << proc.processName << "\n";
		}
	}
}

bool ProcessInjector::FindTargetProcess(const char* processName) {
	std::cout << "[*] Searching for target process: " << processName << "\n";

	for(const auto& proc : processList) {
		if(proc.processName == processName) {
			targetProcessID = proc.processID;
			targetProcessName = proc.processName;
			std::cout << "[+] Found target process! PID: " << targetProcessID << "\n";
			return true;
		}
	}

	std::cout << "[-] Target process not found\n";
	return false;
}

bool ProcessInjector::AttachToProcess(DWORD processID) {
	std::cout << "[*] Attempting to attach to process: " << processID << "\n";

	processHandle = OpenProcess(
		PROCESS_ALL_ACCESS,
		FALSE,
		processID
	);

	if(processHandle == NULL) {
		std::cout << "[-] Failed to open process handle\n";
		return false;
	}

	targetProcessID = processID;
	attached = true;

	std::cout << "[+] Successfully attached to process\n";
	std::cout << "[*] Process handle: 0x" << std::hex << (uintptr_t)processHandle << std::dec << "\n";

	return true;
}

bool ProcessInjector::InjectPayload(const char* dllPath) {
	if(!attached || processHandle == nullptr) {
		std::cout << "[-] Not attached to process\n";
		return false;
	}

	std::cout << "[*] Injecting payload: " << dllPath << "\n";
	std::cout << "[*] Target PID: " << targetProcessID << "\n";

	// Fake DLL path validation
	std::string path(dllPath);
	if(path.find(".dll") == std::string::npos) {
		std::cout << "[-] Invalid DLL path\n";
		return false;
	}

	std::cout << "[*] Allocating remote memory...\n";
	std::cout << "[*] Memory allocation size: 4096 bytes\n";

	// Fake memory allocation
	LPVOID remoteMemory = VirtualAllocEx(
		processHandle,
		nullptr,
		4096,
		MEM_COMMIT | MEM_RESERVE,
		PAGE_READWRITE
	);

	if(!remoteMemory) {
		std::cout << "[-] Failed to allocate remote memory\n";
		return false;
	}

	std::cout << "[+] Remote memory allocated at: 0x" << std::hex << (uintptr_t)remoteMemory << std::dec << "\n";

	// Fake write
	std::cout << "[*] Writing DLL path to remote process...\n";
	SIZE_T bytesWritten = 0;
	if(!WriteProcessMemory(processHandle, remoteMemory, (void*)dllPath, strlen(dllPath) + 1, &bytesWritten)) {
		std::cout << "[-] Failed to write to remote memory\n";
		VirtualFreeEx(processHandle, remoteMemory, 0, MEM_RELEASE);
		return false;
	}

	std::cout << "[+] Bytes written: " << bytesWritten << "\n";

	// Fake thread creation
	if(!CreateRemoteThread(processHandle, dllPath)) {
		std::cout << "[-] Failed to create remote thread\n";
		VirtualFreeEx(processHandle, remoteMemory, 0, MEM_RELEASE);
		return false;
	}

	std::cout << "[+] Payload injection successful\n";
	return true;
}

bool ProcessInjector::CreateRemoteThread(HANDLE hProcess, const char* dllPath) {
	std::cout << "[*] Creating remote thread...\n";

	LPVOID loadLibraryAddr = (LPVOID)GetProcAddress(
		GetModuleHandle("kernel32.dll"),
		"LoadLibraryA"
	);

	if(!loadLibraryAddr) {
		std::cout << "[-] Failed to get LoadLibraryA address\n";
		return false;
	}

	std::cout << "[*] LoadLibraryA address: 0x" << std::hex << (uintptr_t)loadLibraryAddr << std::dec << "\n";

	HANDLE remoteThread = CreateRemoteThread(
		hProcess,
		nullptr,
		0,
		(LPTHREAD_START_ROUTINE)loadLibraryAddr,
		nullptr,
		0,
		nullptr
	);

	if(!remoteThread) {
		std::cout << "[-] Failed to create remote thread\n";
		return false;
	}

	std::cout << "[+] Remote thread created successfully\n";
	std::cout << "[*] Thread ID: 0x" << std::hex << GetThreadId(remoteThread) << std::dec << "\n";
	std::cout << "[*] Waiting for thread execution...\n";

	WaitForSingleObject(remoteThread, 5000);
	CloseHandle(remoteThread);

	return true;
}

void ProcessInjector::DetachFromProcess() {
	if(processHandle) {
		std::cout << "[*] Detaching from process...\n";
		CloseHandle(processHandle);
		processHandle = nullptr;
		attached = false;
		targetProcessID = 0;
		std::cout << "[+] Detached\n";
	}
}

DWORD ProcessInjector::GetTargetProcessID() {
	return targetProcessID;
}

std::string ProcessInjector::GetTargetProcessName() {
	return targetProcessName;
}

bool ProcessInjector::IsAttached() {
	return attached;
}

bool ProcessInjector::IsGameRunning() {
	for(const auto& proc : processList) {
		if(proc.processName == "KnivesOut.exe") {
			return true;
		}
	}
	return false;
}

void ProcessInjector::Shutdown() {
	std::cout << "[*] Process injector shutting down...\n";
	DetachFromProcess();
	processList.clear();
	std::cout << "[+] Process injector shutdown complete\n";
}
