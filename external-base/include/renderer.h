#pragma once
#include "defs.h"

class Renderer {
public:
	static void Initialize();
	static void RenderFrame();
	static void ClearScreen();
	static void Shutdown();

private:
	static int frameCount;
	static float deltaTime;
};

void RenderOverlay();
