#include "luaExecutor.h"

std::string code;
bool toRun = false;

void setRunString(std::string str) {
	code = str;
	toRun = true;
}

bool isRunString() {
	return toRun;
}

std::string getRunString() {
	toRun = false;
	return code;
}