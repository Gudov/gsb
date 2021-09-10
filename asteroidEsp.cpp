#include "asteroidEsp.h"
#include "gameHooks.h"
#include "render.h"
#include <foundation/PxVec2.h>
#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>
#include "menu.h"


struct AsteroidSubData {
	float maxDist;
	asteroidStruct* ptr;
	void* subPtr;
};

struct AsteroidCache {
	physx::PxVec3 pos;
	char type[256];
	float dist;
	uint32_t ind;
};

static std::vector<AsteroidSubData> asteroidsSubData;
static std::vector<AsteroidCache> asteroidsCache;

static void drawAsteroid(physx::PxVec3 &pos, char* text, float dist, bool drawLine, bool drawNear, bool drawFar, ImGuiIO &io) {
	if (dist > 3000 && drawFar) {
		physx::PxVec2 screenPos = worldToScreen(pos);
		if (screenPos.x > 0 && screenPos.y > 0) {
			ImGui::GetWindowDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(screenPos.x, screenPos.y), Colors::farAsteroid, text, 0, 0.0f, 0);
		}
		if (drawLine) {
			physx::PxVec2 linePos = worldToScreenIgnoreDirection(pos);
			ImGui::GetWindowDrawList()->AddLine(ImVec2(linePos.x, linePos.y), ImVec2(io.DisplaySize.x / 2, io.DisplaySize.y / 2), Colors::lineFarAsteroid);
		}
	} else if (drawNear) {
		physx::PxVec2 screenPos = worldToScreen(pos);
		if (screenPos.x > 0 && screenPos.y > 0) {
			ImGui::GetWindowDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(screenPos.x, screenPos.y), Colors::nearAsteroid, text, 0, 0.0f, 0);
		}
	}
}

static void drawAsteroidsFromCache(bodyData ply) {
	ImGuiIO io = ImGui::GetIO();
	bool drawNear = getOptionBool("drawNearAsteroid", true);
	bool drawFar = getOptionBool("drawFarAsteroid", true);
	bool drawLine = getOptionBool("drawAsteroidLine", true);

	for (auto &asteroid : asteroidsCache) {
		physx::PxVec3 localPos = ply.pos - asteroid.pos;
		float dist = sqrtf((localPos.x * localPos.x) + (localPos.y * localPos.y) + (localPos.z * localPos.z));
		char buff[256];
		sprintf(buff, "%s %.0f %0.f", asteroid.type, asteroid.dist, dist);
		drawAsteroid(asteroid.pos, buff, asteroid.dist, drawLine, drawNear, drawFar, io);
	}
}

static bool testObjectPtr(asteroidStruct* object) {
	bool skip = false;
	__try {
		if ((uint64_t)object < 0x10'0000'0000 || (uint64_t)object > 0x1'0000'0000'0000 || object->type == nullptr) {
			skip = true;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		skip = true;
	}
	return skip;
}

void drawAsteroidESP(bodyData ply) {

	bool asteroidEspEnabled = getOptionBool("asteroidEspEnabled", false);
	if (!asteroidEspEnabled) return;

	if (objectManager == 0) {
		return;
	}
	static uint32_t updateCounter = 0;
	updateCounter++;

	if (updateCounter < 30) {
		drawAsteroidsFromCache(ply);
		return;
	}
	updateCounter = 0;
	asteroidsCache.clear();

	uint32_t maxObjects = *(uint32_t*)(objectManager + 0x60068);

	ImGuiIO io = ImGui::GetIO();
	bool checkOre = getOptionBool("asteroidOreCheck", true);
	char* filterOre = getOptionString("asteroidFilter", "ore");
	bool drawNear = getOptionBool("drawNearAsteroid", true);
	bool drawFar = getOptionBool("drawFarAsteroid", true);
	bool drawLine = getOptionBool("drawAsteroidLine", true);

	for (uint32_t i = 0; i < maxObjects; i++) {
		asteroidStruct* object = (asteroidStruct*)((*(uint64_t*)(objectManager + 0x60060) & 0xFFFFFFFFFFFFFFFCui64) + (0x120 * i));
		if (testObjectPtr(object)) {
			continue;
		}

		if (checkOre && !strstr(object->type, "ore")) {
			continue;
		}

		if (!strstr(object->type, filterOre)) {
			continue;
		}

		physx::PxVec3 objectPos{ object->x, object->y, object->z };
		physx::PxVec3 localPos = ply.pos - objectPos;
		float dist = sqrtf((localPos.x * localPos.x) + (localPos.y * localPos.y) + (localPos.z * localPos.z));

		if (asteroidsSubData.size() <= i) {
			asteroidsSubData.resize(i * 1.2f);
		}

		if (dist > 600) {
			AsteroidSubData& subData = asteroidsSubData[i];
			if (subData.ptr != object || subData.subPtr != (void*)object->ptr0) {
				subData.ptr = object;
				subData.maxDist = dist;
				subData.subPtr = (void*)object->ptr0;
			}
			else if (subData.maxDist < dist) {
				subData.maxDist = dist;
			}
		}

		float maxDist = (asteroidsSubData[i].ptr == object) ? asteroidsSubData[i].maxDist : 0;
		char buff[256];
		sprintf(buff, "%s %.0f %0.f", object->type, asteroidsSubData[i].maxDist, dist);
		drawAsteroid(objectPos, buff, maxDist, drawLine, drawNear, drawFar, io);

		AsteroidCache cache;
		cache.ind = i;
		cache.pos = objectPos;
		cache.dist = maxDist;
		strcpy(cache.type, object->type);
		asteroidsCache.push_back(cache);
	}
}