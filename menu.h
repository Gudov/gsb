#pragma once
#include <string>
#include <imgui.h>
#include "colors.h"
#include <variant>
#include <unordered_map>

//const char* configName = "gsb.cfg";

using SettingsMeta = std::variant<bool*, float*, ImColor*, std::string*>;
using SettingsMap = std::unordered_map<std::string, SettingsMeta>;
SettingsMap *getSettingsMap();

template<typename T>
T getOption(std::string name) {
	SettingsMap *settings = getSettingsMap();
	auto find = settings->find(name);
	if (find == settings->end()) {
		return T();
	}

	if (T** pval = std::get_if<T*>(&(find->second))) {
		return **pval;
	}

	return T();
}

void drawMenu();