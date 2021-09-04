#pragma once
#include <string>

bool getOptionBool(std::string name, bool def);
float getOptionFloat(std::string name, float def);
char *getOptionString(std::string name, const char* def);

void drawMenu();