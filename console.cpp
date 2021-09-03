#include "console.h"
#include <Windows.h>
#include <fcntl.h>
#include <io.h>

FILE* Con::fpout;
FILE* Con::fpin;

void Con::init() {
	int hConHandle;
	long lStdHandle;

	AllocConsole();

	lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fpin = _fdopen(hConHandle, "r");

	lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fpout = _fdopen(hConHandle, "w");
}

void Con::enableStdout(bool state) {
	const char* pipe = state ? "CONOUT$" : "NUL:";
	freopen(pipe, "w", stdout);
}