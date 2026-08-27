#pragma once
#include <cstdint>
#include <vector>

constexpr float VERSION = 1.0f;
constexpr bool DEBUG_MODE = true;

struct Vector2 {
	float x, y;
};

struct Vector3 {
	float x, y, z;
};

struct Matrix4x4 {
	float m[4][4];
};

typedef unsigned char byte;
typedef unsigned int uint;
typedef unsigned long ulong;
