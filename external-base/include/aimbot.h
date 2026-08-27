#pragma once
#include "defs.h"

class Aimbot {
public:
	static void Initialize();
	static void Update();
	static void EnableAim(bool enabled);
	static void SetFOV(float fov);
	static void SetSmoothing(float smoothing);
	static void SetPrediction(bool enabled);
	static void Shutdown();

	static bool IsEnabled();
	static float GetCurrentFOV();
	static Vector3 GetAimVector();

private:
	static bool aimEnabled;
	static float currentFOV;
	static float smoothingFactor;
	static Vector3 targetVector;
	static int targetLocked;
};
