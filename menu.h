#pragma once
#include <string>
#include <imgui.h>
#include "colors.h"
bool getOptionBool(std::string name, bool def);
float getOptionFloat(std::string name, float def);
char *getOptionString(std::string name, const char* def);

void drawMenu();