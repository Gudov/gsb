#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <thread>
#include <tlhelp32.h>
#include <MinHook.h>
#include <stdlib.h>
#include <dxgi.h>
#include <PxActor.h>
#include <PxRigidActor.h>
#include <PxScene.h>
#include <PxAggregate.h>
#include <PxRigidBody.h>
#include <PxRigidStatic.h>

#include "threads.h"
#include "console.h"
#include "luaHooks.h"
#include "gameHooks.h"
#include "luaExecutor.h"
#include "hookUtils.h"
//#include "dxHooks.h"
#include "physics.h"
#include "dxHooks2.h"

static bool __fastcall comapreClass(__int64 a1, __int64 a2)
{
	__int64 v3; // rdi

	if (a1 == a2)
		return 1;
	v3 = *(unsigned int*)(a2 + 24);
	return (unsigned int)v3 < *(uint32_t*)(a1 + 24)
		&& *(uint64_t*)((*(uint64_t*)(a1 + 16) & 0xFFFFFFFFFFFFFFFCui64) + 8 * v3) == a2;
}

int main()
{
	Con::init();
	Con::enableStdout(true);
	pauseAllThreads(true);

	MH_Initialize();
	//initLuaHook();
	initGameHooks();
	//initDxHook();
	initDxHooks2();

	pauseAllThreads(false);

	while (true) {
		char buff[4096];
		//fscanf(Con::fpin, "%s", buff);
		fgets(buff, 4000, Con::fpin);
		setRunString(buff);
	}

	return 0;
}

BOOL APIENTRY DllMain(HINSTANCE hinstDLL,
	DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)main, NULL, 0, NULL);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)updatePhysicsThread, NULL, 0, NULL);
	}
	return TRUE;
}