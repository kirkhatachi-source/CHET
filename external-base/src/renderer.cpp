#include "..\include\renderer.h"
#include <iostream>
#include <ctime>

int Renderer::frameCount = 0;
float Renderer::deltaTime = 0.0f;

void Renderer::Initialize() {
	std::cout << "[*] Renderer initializing...\n";
	frameCount = 0;
	deltaTime = 0.016f;
	std::cout << "[+] Renderer initialized\n";
}

void Renderer::RenderFrame() {
	frameCount++;
	if(frameCount % 60 == 0) {
		std::cout << "[*] Frame count: " << frameCount << "\n";
	}
}

void Renderer::ClearScreen() {
	system("cls");
	std::cout << "[*] Screen cleared\n";
}

void Renderer::Shutdown() {
	std::cout << "[*] Renderer shutdown\n";
}

void RenderOverlay() {
	std::cout << "[*] Overlay rendering\n";
}
