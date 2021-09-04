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

static std::vector<AsteroidSubData> asteroidsSubData;

void drawAsteroidESP(bodyData ply) {
	if (objectManager == 0) {
		return;
	}
	uint32_t maxObjects = *(uint32_t*)(objectManager + 0x60068);

	ImGuiIO io = ImGui::GetIO();

	for (uint32_t i = 0; i < maxObjects; i++) {
		asteroidStruct* object = (asteroidStruct*)((*(uint64_t*)(objectManager + 0x60060) & 0xFFFFFFFFFFFFFFFCui64) + (0x120 * i));
		if ((uint64_t)object < 0x10'0000'0000 || (uint64_t)object > 0x1'0000'0000'0000 || object->type == nullptr) {
			continue;
		}

		if (!strstr(object->type, "ore")) {
			continue;
		}

		if (!strstr(object->type, getOptionString("asteroidFilter", "ore"))) {
			continue;
		}

		physx::PxVec3 objectPos{ object->x, object->y, object->z };
		physx::PxVec3 localPos = ply.pos - objectPos;
		float dist = sqrtf((localPos.x * localPos.x) + (localPos.y * localPos.y) + (localPos.z * localPos.z));

		if (asteroidsSubData.size() <= i) {
			asteroidsSubData.resize(i * 1.2f);
		}

		if (dist > 200) {
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

		physx::PxVec2 screenPos = worldToScreen(objectPos);

		char buff[256];
		sprintf(buff, "%s %.0f %0.f", object->type, asteroidsSubData[i].maxDist, dist);
		if (asteroidsSubData[i].ptr == object && asteroidsSubData[i].maxDist > 3000) {
			if (screenPos.x > 0 && screenPos.y > 0 && getOptionBool("drawFarAsteroid", true)) {
				ImGui::GetWindowDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(screenPos.x, screenPos.y), ImColor(193, 137, 0, 255), buff, 0, 0.0f, 0);
			}
			if (getOptionBool("drawAsteroidLine", true)) {
				physx::PxVec2 linePos = worldToScreenIgnoreDirection(objectPos);
				ImGui::GetWindowDrawList()->AddLine(ImVec2(linePos.x, linePos.y), ImVec2(io.DisplaySize.x/2, io.DisplaySize.y/2), ImColor(193, 137, 0, 255));
			}
		} else {
			if (screenPos.x > 0 && screenPos.y > 0 && getOptionBool("drawNearAsteroid", false)) {
				ImGui::GetWindowDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(screenPos.x, screenPos.y), ImColor(0, 255, 255, 255), buff, 0, 0.0f, 0);
			}
		}
	}
}