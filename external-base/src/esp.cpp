#include "..\include\esp.h"
#include "..\include\offsets.h"
#include <iostream>
#include <algorithm>
#include <cmath>

bool ESP::espEnabled = false;
bool ESP::boundingBoxEnabled = true;
bool ESP::healthBarEnabled = true;
bool ESP::distanceEnabled = true;
float ESP::maxDrawDistance = 300.0f;
std::vector<ESPEntity> ESP::entityList;

void ESP::Initialize() {
	std::cout << "[*] ESP module initializing...\n";
	std::cout << "[*] View matrix offset: 0x" << std::hex << Offsets::ESP::VIEW_MATRIX << std::dec << "\n";
	std::cout << "[*] Projection matrix offset: 0x" << std::hex << Offsets::ESP::PROJECTION_MATRIX << std::dec << "\n";
	std::cout << "[*] Screen dimensions offset: 0x" << std::hex << Offsets::ESP::SCREEN_WIDTH << std::dec << "\n";
	std::cout << "[*] Max draw distance: " << maxDrawDistance << " units\n";
	std::cout << "[+] ESP module ready\n";
}

void ESP::Update() {
	if(!espEnabled) return;

	UpdateEntityList();

	for(auto& entity : entityList) {
		if(entity.visible && entity.distance <= maxDrawDistance) {
			entity.screenPos = WorldToScreen(entity.position);
		}
	}
}

void ESP::Render() {
	if(!espEnabled || entityList.empty()) return;

	std::cout << "[*] Rendering " << entityList.size() << " entities\n";

	for(const auto& entity : entityList) {
		if(!entity.visible || entity.distance > maxDrawDistance) continue;

		std::cout << "[ESP] Entity at (" 
			<< entity.screenPos.x << ", " 
			<< entity.screenPos.y << ") - Dist: " 
			<< entity.distance << "m - HP: " 
			<< entity.health << "\n";

		if(boundingBoxEnabled) {
			std::cout << "  [BOX] " << (entity.isAlly ? "ALLY" : "ENEMY") << "\n";
		}
		if(healthBarEnabled) {
			std::cout << "  [HP] " << entity.health << "/100\n";
		}
		if(distanceEnabled) {
			std::cout << "  [DIST] " << entity.distance << "m\n";
		}
	}
}

void ESP::EnableESP(bool enabled) {
	espEnabled = enabled;
	std::cout << "[" << (enabled ? "+" : "-") << "] ESP " << (enabled ? "ENABLED" : "DISABLED") << "\n";
}

void ESP::EnableBoundingBox(bool enabled) {
	boundingBoxEnabled = enabled;
	std::cout << "[" << (enabled ? "+" : "-") << "] Bounding boxes " << (enabled ? "ON" : "OFF") << "\n";
}

void ESP::EnableHealthBar(bool enabled) {
	healthBarEnabled = enabled;
	std::cout << "[" << (enabled ? "+" : "-") << "] Health bars " << (enabled ? "ON" : "OFF") << "\n";
}

void ESP::EnableDistance(bool enabled) {
	distanceEnabled = enabled;
	std::cout << "[" << (enabled ? "+" : "-") << "] Distance display " << (enabled ? "ON" : "OFF") << "\n";
}

void ESP::SetMaxDistance(float distance) {
	maxDrawDistance = distance;
	std::cout << "[*] Max ESP distance: " << distance << "m\n";
}

void ESP::Shutdown() {
	std::cout << "[*] ESP module shutdown\n";
	espEnabled = false;
	entityList.clear();
}

bool ESP::IsEnabled() {
	return espEnabled;
}

int ESP::GetEntityCount() {
	return entityList.size();
}

const std::vector<ESPEntity>& ESP::GetVisibleEntities() {
	return entityList;
}

void ESP::UpdateEntityList() {
	entityList.clear();

	// Fake entity generation
	for(int i = 0; i < 12; i++) {
		ESPEntity entity;
		entity.position = {
			100.0f + (i * 50.0f),
			50.0f + (i * 25.0f),
			-500.0f
		};
		entity.distance = std::sqrt(
			entity.position.x * entity.position.x +
			entity.position.y * entity.position.y +
			entity.position.z * entity.position.z
		);
		entity.health = 50 + (i * 5);
		entity.team = i % 2;
		entity.visible = entity.distance <= maxDrawDistance;
		entity.isAlly = (entity.team == 0);
		entity.screenPos = WorldToScreen(entity.position);

		entityList.push_back(entity);
	}
}

Vector2 ESP::WorldToScreen(const Vector3& worldPos) {
	// Fake world-to-screen projection
	Vector2 screenPos;
	screenPos.x = 960.0f + (worldPos.x / 100.0f) * 50.0f;
	screenPos.y = 540.0f + (worldPos.y / 100.0f) * 50.0f;
	return screenPos;
}

bool ESP::IsEntityVisible(const ESPEntity& entity) {
	return entity.visible && entity.distance <= maxDrawDistance;
}
