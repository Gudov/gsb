#include "menu.h"
#include <Windows.h>
#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>
#include <vector>
#include <unordered_map>

static bool showmenu = false;
static std::unordered_map<std::string, bool> optionsBool;
static std::unordered_map<std::string, float> optionsFloat;
static std::unordered_map<std::string, char*> optionsString;

bool getOptionBool(std::string name, bool def) {
	auto find = optionsBool.find(name);
	if (find != optionsBool.end()) {
		return find->second;
	} else {
		return def;
	}
}

float getOptionFloat(std::string name, float def) {
	auto find = optionsFloat.find(name);
	if (find != optionsFloat.end()) {
		return find->second;
	} else {
		return def;
	}
}

char* getOptionString(std::string name, const char* def) {
	auto find = optionsString.find(name);
	if (find != optionsString.end()) {
		return find->second;
	} else {
		return (char*)def;
	}
}


void drawMenu() {
	if (GetAsyncKeyState(VK_INSERT) & 1) {
		showmenu = !showmenu;
	}

	if (showmenu) {
		ImGui::Begin("Menu");

		static bool asteroidEspEnabled = true;
		ImGui::Checkbox("asteroidEspEnabled", &asteroidEspEnabled);
		optionsBool["asteroidEspEnabled"] = asteroidEspEnabled;

		static char asteroidFilter[256] = "ore";
		if (ImGui::TreeNode("asteroidFilter")) {
			ImGui::InputText("asteroidFilter", asteroidFilter, 255);
			if (ImGui::Button("ice ore")) { strcpy(asteroidFilter, "ice"); }
			if (ImGui::Button("ajatitite ore")) { strcpy(asteroidFilter, "ajat"); }
			if (ImGui::Button("valkite ore")) { strcpy(asteroidFilter, "valki"); }
			ImGui::TreePop();
		}
		optionsString["asteroidFilter"] = asteroidFilter;

		static bool asteroidOreCheck = true;
		ImGui::Checkbox("asteroidOreCheck", &asteroidOreCheck);
		optionsBool["asteroidOreCheck"] = asteroidOreCheck;

		static bool drawNearAsteroid = false;
		ImGui::Checkbox("drawNearAsteroid", &drawNearAsteroid);
		optionsBool["drawNearAsteroid"] = drawNearAsteroid;

		static bool drawFarAsteroid = true;
		ImGui::Checkbox("drawFarAsteroid", &drawFarAsteroid);
		optionsBool["drawFarAsteroid"] = drawFarAsteroid;

		static bool drawAsteroidLine = true;
		ImGui::Checkbox("drawAsteroidLine", &drawAsteroidLine);
		optionsBool["drawAsteroidLine"] = drawAsteroidLine;

		static bool drawPhysMass = false;
		ImGui::Checkbox("drawPhysMass", &drawPhysMass);
		optionsBool["drawPhysMass"] = drawPhysMass;

		/*ImGui::Checkbox("Modelrecfinder", &modelrecfinder);
		if (modelrecfinder == 1)
		{
			if (check_draw_result == 1)ImGui::Text("Draw called."); ImGui::SameLine();
			if (check_drawindexed_result == 1)ImGui::Text("DrawIndexed called."); ImGui::SameLine();
			if (check_drawindexedinstanced_result == 1)ImGui::Text("DrawIndexedInstanced called.");

			//ImGui::SliderInt("Modelfind Mode", &modelfindmode, 1, 3);
			ImGui::NewLine();
			if (modelfindmode == 1)ImGui::SliderInt("Modelfind Mode 1 (Step 10)", &modelfindmode, 1, 3);
			else if (modelfindmode == 2)ImGui::SliderInt("Modelfind Mode 2 (Step 100)", &modelfindmode, 1, 3);
			else if (modelfindmode == 3)ImGui::SliderInt("Modelfind Mode 3 (Step 1000)", &modelfindmode, 1, 3);

			//bruteforce
			ImGui::SliderInt("find Stride", &countStride, -1, 100);
			ImGui::SliderInt("find IndexCount", &countIndexCount, -1, 100);
			ImGui::SliderInt("find veWidth", &countveWidth, -1, 100);
			ImGui::SliderInt("find pscWidth", &countpscWidth, -1, 100);

		}
		ImGui::Checkbox("Dump Shader", &dumpshader);

		ImGui::Checkbox("Wtsfinder", &wtsfinder);
		if (wtsfinder == 1)
		{
			ImGui::Text("valid vscStartSlot = %d", validvscStartSlot);
			ImGui::Checkbox("method1", &method1);
			ImGui::Checkbox("method2", &method2);
			ImGui::Checkbox("method3", &method3);
			ImGui::Checkbox("method4", &method4);

			DWORD dwTicks = GetTickCount();
			if ((dwTicks - g_dwLastAction) >= 1000)
			{
				//reset buffer every second while bruteforcing values
				//Log("do something if 1 second has passed");

				//reset to avoid wrong values
				pStageBufferA = NULL;
				pStageBufferB = NULL;

				//reset var to current ticks
				g_dwLastAction = dwTicks;
			}
			//bruteforce
			ImGui::SliderInt("WorldViewCBnum", &WorldViewCBnum, 0, 10);
			ImGui::SliderInt("ProjCBnum", &ProjCBnum, 0, 10);
			ImGui::SliderInt("matProjnum", &matProjnum, 0, 100);//240
		}

		static bool editProjMat = false;
		ImGui::Checkbox("editProjMat", &editProjMat);
		if (editProjMat) {
			ImGui::PushItemWidth(100);
			ImGui::InputFloat("mat00", &statProj.r[0].m128_f32[0]);
			ImGui::SameLine();
			ImGui::PushItemWidth(100);
			ImGui::InputFloat("mat01", &statProj.r[0].m128_f32[1]);
			ImGui::SameLine();
			ImGui::PushItemWidth(100);
			ImGui::InputFloat("mat02", &statProj.r[0].m128_f32[2]);
			ImGui::SameLine();
			ImGui::PushItemWidth(100);
			ImGui::InputFloat("mat03", &statProj.r[0].m128_f32[3]);

			ImGui::PushItemWidth(100);
			ImGui::InputFloat("mat10", &statProj.r[1].m128_f32[0]);
			ImGui::SameLine();
			ImGui::PushItemWidth(100);
			ImGui::InputFloat("mat11", &statProj.r[1].m128_f32[1]);
			ImGui::SameLine();
			ImGui::PushItemWidth(100);
			ImGui::InputFloat("mat12", &statProj.r[1].m128_f32[2]);
			ImGui::SameLine();
			ImGui::PushItemWidth(100);
			ImGui::InputFloat("mat13", &statProj.r[1].m128_f32[3]);

			ImGui::PushItemWidth(100);
			ImGui::InputFloat("mat20", &statProj.r[2].m128_f32[0]);
			ImGui::SameLine();
			ImGui::PushItemWidth(100);
			ImGui::InputFloat("mat21", &statProj.r[2].m128_f32[1]);
			ImGui::SameLine();
			ImGui::PushItemWidth(100);
			ImGui::InputFloat("mat22", &statProj.r[2].m128_f32[2]);
			ImGui::SameLine();
			ImGui::PushItemWidth(100);
			ImGui::InputFloat("mat23", &statProj.r[2].m128_f32[3]);

			ImGui::PushItemWidth(100);
			ImGui::InputFloat("mat30", &statProj.r[3].m128_f32[0]);
			ImGui::SameLine();
			ImGui::PushItemWidth(100);
			ImGui::InputFloat("mat31", &statProj.r[3].m128_f32[1]);
			ImGui::SameLine();
			ImGui::PushItemWidth(100);
			ImGui::InputFloat("mat32", &statProj.r[3].m128_f32[2]);
			ImGui::SameLine();
			ImGui::PushItemWidth(100);
			ImGui::InputFloat("mat33", &statProj.r[3].m128_f32[3]);

			ImGui::PushItemWidth(100);
			ImGui::InputFloat("xtestoff", &xtestoffset);
			ImGui::SameLine();
			ImGui::PushItemWidth(100);
			ImGui::InputFloat("ytestoff", &ytestoffset);
		}

		ImGui::Checkbox("drawDebugMat", &drawDebugMat);

		ImGui::Checkbox("drawMap", &drawMap);
		if (drawMap) {
			ImGui::PushItemWidth(150);
			ImGui::InputFloat("xoff", &xoffset);
			ImGui::SameLine();
			ImGui::PushItemWidth(150);
			ImGui::InputFloat("yoff", &yoffset);
			ImGui::InputFloat("scale", &scale);
		}
		*/
		ImGui::End();
	}
}