#pragma once
#include <windows.h>
#include <string>
#include <vector>

struct ProcessInfo {
	DWORD processID;
	std::string processName;
	std::string windowTitle;
	bool isTarget;
};

class ProcessInjector {
public:
	static void Initialize();
	static bool FindTargetProcess(const char* processName);
	static bool AttachToProcess(DWORD processID);
	static bool InjectPayload(const char* dllPath);
	static void DetachFromProcess();
	static void EnumerateProcesses();
	static DWORD GetTargetProcessID();
	static std::string GetTargetProcessName();
	static void Shutdown();

	static bool IsAttached();
	static bool IsGameRunning();

private:
	static DWORD targetProcessID;
	static std::string targetProcessName;
	static HANDLE processHandle;
	static bool attached;
	static std::vector<ProcessInfo> processList;

	static bool CreateRemoteThread(HANDLE hProcess, const char* dllPath);
	static void UpdateProcessList();
};
