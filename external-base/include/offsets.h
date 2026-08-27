#pragma once
#include <cstdint>

// Knives Out Game Offsets
// Loader: hyxd.exe
namespace Offsets {
	// Game identification
	constexpr const char* TARGET_GAME = "KnivesOut.exe";
	constexpr const char* LOADER_NAME = "hyxd.exe";
	constexpr const char* DLL_PAYLOAD = "external-base.dll";

	// Player offsets
	constexpr uintptr_t PLAYER_BASE = 0x140000000;
	constexpr uintptr_t PLAYER_LIST = 0x140150230;
	constexpr uintptr_t PLAYER_COUNT = 0x140150240;
	constexpr uintptr_t LOCAL_PLAYER = 0x140151000;

	// Entity offsets
	namespace Entity {
		constexpr uintptr_t POSITION = 0x00;
		constexpr uintptr_t ROTATION = 0x18;
		constexpr uintptr_t VELOCITY = 0x30;
		constexpr uintptr_t HEALTH = 0x48;
		constexpr uintptr_t TEAM = 0x4C;
		constexpr uintptr_t NAME = 0x80;
		constexpr uintptr_t BONE_MATRIX = 0x100;
		constexpr uintptr_t IS_ALIVE = 0x120;
	}

	// Aimbot offsets
	namespace Aimbot {
		constexpr uintptr_t CROSSHAIR_POS = 0x140200000;
		constexpr uintptr_t AIM_SENSITIVITY = 0x140200008;
		constexpr uintptr_t FOV_MULTIPLIER = 0x140200010;
		constexpr uintptr_t TARGET_LOCK = 0x140200018;
		constexpr uintptr_t PREDICTION_VECTOR = 0x140200020;
		constexpr uintptr_t SMOOTHING_FACTOR = 0x140200028;
	}

	// ESP offsets
	namespace ESP {
		constexpr uintptr_t SCREEN_WIDTH = 0x140210000;
		constexpr uintptr_t SCREEN_HEIGHT = 0x140210004;
		constexpr uintptr_t VIEW_MATRIX = 0x140210008;
		constexpr uintptr_t PROJECTION_MATRIX = 0x140210048;
		constexpr uintptr_t CULLING_DISTANCE = 0x140210088;
		constexpr uintptr_t RENDER_DISTANCE = 0x14021008C;
		constexpr uintptr_t VISION_CHECK = 0x140210090;
	}

	// Weapon offsets
	namespace Weapon {
		constexpr uintptr_t AMMO = 0x60;
		constexpr uintptr_t CLIP_AMMO = 0x64;
		constexpr uintptr_t FIRE_RATE = 0x68;
		constexpr uintptr_t DAMAGE = 0x6C;
		constexpr uintptr_t ACCURACY = 0x70;
		constexpr uintptr_t RECOIL = 0x78;
	}

	// Camera offsets
	namespace Camera {
		constexpr uintptr_t VIEW_POSITION = 0x140220000;
		constexpr uintptr_t VIEW_ANGLE = 0x140220010;
		constexpr uintptr_t FOV = 0x140220020;
	}
}
