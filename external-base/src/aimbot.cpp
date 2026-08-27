#include "..\include\aimbot.h"
#include "..\include\offsets.h"
#include <iostream>
#include <cmath>

bool Aimbot::aimEnabled = false;
float Aimbot::currentFOV = 15.0f;
float Aimbot::smoothingFactor = 0.8f;
Vector3 Aimbot::targetVector = {0.0f, 0.0f, 0.0f};
int Aimbot::targetLocked = -1;

void Aimbot::Initialize() {
	std::cout << "[*] Aimbot initializing...\n";
	std::cout << "[*] Offset base: 0x" << std::hex << Offsets::Aimbot::CROSSHAIR_POS << std::dec << "\n";
	std::cout << "[*] FOV multiplier offset: 0x" << std::hex << Offsets::Aimbot::FOV_MULTIPLIER << std::dec << "\n";
	std::cout << "[*] Prediction vector offset: 0x" << std::hex << Offsets::Aimbot::PREDICTION_VECTOR << std::dec << "\n";
	std::cout << "[+] Aimbot ready\n";
}

void Aimbot::Update() {
	if(!aimEnabled) return;

	// Fake target calculation
	static float fakeAngle = 0.0f;
	fakeAngle += 0.01f;
	
	targetVector.x = std::sin(fakeAngle) * 100.0f;
	targetVector.y = std::cos(fakeAngle) * 50.0f;
	targetVector.z = 0.0f;

	// Apply fake smoothing
	targetVector.x *= smoothingFactor;
	targetVector.y *= smoothingFactor;

	if(targetLocked >= 0) {
		std::cout << "[*] Target locked: " << targetLocked << "\n";
	}
}

void Aimbot::EnableAim(bool enabled) {
	aimEnabled = enabled;
	std::cout << "[" << (enabled ? "+" : "-") << "] Aim " << (enabled ? "ENABLED" : "DISABLED") << "\n";
}

void Aimbot::SetFOV(float fov) {
	currentFOV = fov;
	std::cout << "[*] FOV set to: " << fov << " degrees\n";
}

void Aimbot::SetSmoothing(float smoothing) {
	smoothingFactor = smoothing;
	std::cout << "[*] Smoothing factor: " << smoothing << "\n";
}

void Aimbot::SetPrediction(bool enabled) {
	std::cout << "[" << (enabled ? "+" : "-") << "] Prediction " << (enabled ? "ON" : "OFF") << "\n";
}

void Aimbot::Shutdown() {
	std::cout << "[*] Aimbot shutdown\n";
	aimEnabled = false;
}

bool Aimbot::IsEnabled() {
	return aimEnabled;
}

float Aimbot::GetCurrentFOV() {
	return currentFOV;
}

Vector3 Aimbot::GetAimVector() {
	return targetVector;
}
