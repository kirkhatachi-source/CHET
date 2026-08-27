#include <iostream>
#include <thread>
#include <chrono>
#include <windows.h>
#include "..\include\defs.h"
#include "..\include\renderer.h"
#include "..\include\memory.h"
#include "..\include\aimbot.h"
#include "..\include\esp.h"
#include "..\include\injection.h"
#include "..\include\offsets.h"

int main() {
	std::cout << "========================================\n";
	std::cout << "   External Base v1.0 (Knives Out)\n";
	std::cout << "   Loader: hyxd.exe\n";
	std::cout << "========================================\n\n";
	std::cout << "[*] Initializing system...\n";
	std::cout << "[*] Version: " << VERSION << "\n";

	ProcessInjector::Initialize();
	Memory::Initialize();
	Renderer::Initialize();
	Aimbot::Initialize();
	ESP::Initialize();

	std::cout << "\n[+] System ready\n";
	std::cout << "[*] Detecting game process...\n\n";

	// Game detection
	if(!ProcessInjector::FindTargetProcess(Offsets::TARGET_GAME)) {
		std::cout << "[-] Game not found. Waiting...\n";
	} else {
		std::cout << "[+] Game detected!\n";
		
		// Get target PID
		DWORD targetPID = ProcessInjector::GetTargetProcessID();
		std::cout << "[*] Target PID: " << targetPID << "\n";

		// Attempt attachment
		std::cout << "[*] Attempting process attachment...\n";
		if(ProcessInjector::AttachToProcess(targetPID)) {
			std::cout << "[+] Successfully attached to game process\n";
			
			// Inject payload
			std::cout << "[*] Injecting " << Offsets::DLL_PAYLOAD << "...\n";
			if(ProcessInjector::InjectPayload(Offsets::DLL_PAYLOAD)) {
				std::cout << "[+] Payload injection successful\n";
			}
		}
	}

	std::cout << "\n[*] Running main loop...\n\n";

	// Enable features
	Aimbot::EnableAim(true);
	Aimbot::SetFOV(25.0f);
	Aimbot::SetSmoothing(0.85f);
	Aimbot::SetPrediction(true);

	ESP::EnableESP(true);
	ESP::EnableBoundingBox(true);
	ESP::EnableHealthBar(true);
	ESP::EnableDistance(true);
	ESP::SetMaxDistance(300.0f);

	bool running = true;
	int frameCount = 0;

	while(running && frameCount < 300) {
		Memory::Update();
		Aimbot::Update();
		ESP::Update();
		Renderer::RenderFrame();

		if(frameCount % 60 == 0) {
			std::cout << "\n[FRAME " << frameCount << "]\n";
			std::cout << "[AIM] Enabled: " << (Aimbot::IsEnabled() ? "YES" : "NO") << " | FOV: " << Aimbot::GetCurrentFOV() << "\n";
			std::cout << "[ESP] Enabled: " << (ESP::IsEnabled() ? "YES" : "NO") << " | Entities: " << ESP::GetEntityCount() << "\n";
			ESP::Render();
			std::cout << "\n";
		}

		frameCount++;
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}

	std::cout << "\n[*] Shutting down...\n";
	ProcessInjector::Shutdown();
	Aimbot::Shutdown();
	ESP::Shutdown();
	Memory::Cleanup();
	std::cout << "[+] Shutdown complete\n";
	std::cout << "[*] hyxd.exe exiting\n";

	return 0;
}
