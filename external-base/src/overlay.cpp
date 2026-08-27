#include <windows.h>
#include <iostream>
#include "..\include\defs.h"

HWND overlayWindow = nullptr;

void InitializeOverlay() {
	std::cout << "[*] Overlay initializing...\n";
	
	WNDCLASS wc = {};
	wc.lpfnWndProc = DefWindowProc;
	wc.lpszClassName = L"OverlayClass";

	std::cout << "[+] Overlay initialized\n";
}

void RenderOverlay() {
	static int callCount = 0;
	callCount++;
}

void UpdateOverlayPosition() {
	if(overlayWindow) {
		RECT rect;
		GetClientRect(overlayWindow, &rect);
	}
}

void ShutdownOverlay() {
	std::cout << "[*] Overlay shutdown\n";
}
