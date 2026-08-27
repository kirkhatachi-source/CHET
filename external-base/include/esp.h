#pragma once
#include "defs.h"
#include <vector>

struct ESPEntity {
	Vector3 position;
	Vector2 screenPos;
	float distance;
	int health;
	int team;
	bool visible;
	bool isAlly;
};

class ESP {
public:
	static void Initialize();
	static void Update();
	static void Render();
	static void EnableESP(bool enabled);
	static void EnableBoundingBox(bool enabled);
	static void EnableHealthBar(bool enabled);
	static void EnableDistance(bool enabled);
	static void SetMaxDistance(float distance);
	static void Shutdown();

	static bool IsEnabled();
	static int GetEntityCount();
	static const std::vector<ESPEntity>& GetVisibleEntities();

private:
	static bool espEnabled;
	static bool boundingBoxEnabled;
	static bool healthBarEnabled;
	static bool distanceEnabled;
	static float maxDrawDistance;
	static std::vector<ESPEntity> entityList;
	
	static void UpdateEntityList();
	static Vector2 WorldToScreen(const Vector3& worldPos);
	static bool IsEntityVisible(const ESPEntity& entity);
};
