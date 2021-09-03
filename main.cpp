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
#include "dxHooks.h"
#include "physics.h"

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
	initDxHook();

	pauseAllThreads(false);

	while (true) {
		char buff[4096];
		//fscanf(Con::fpin, "%s", buff);
		fgets(buff, 4000, Con::fpin);
		if (buff[0] == '$') {
			//FILE* f = fopen("objects.txt", "w");
			
			void* phys = getPhysClass();
			for (int i = 0; i < 0xFFFFFF; i++) {
				if (physList[i].entry != nullptr
				 && ((physList[i].entry->id & 0xFFFFFF) == (physList[i].id & 0xFFFFFF))) {
					physx::PxActor* actor = physList[i].entry->actor;
					physx::PxRigidActor* rigid = actor->is<physx::PxRigidActor>();
					physx::PxVec3 pos = rigid->getGlobalPose().p;
					bool isBody = actor->is<physx::PxRigidBody>() != nullptr;
					bool isStatic = actor->is<physx::PxRigidBody>() != nullptr;
					float mass = -1;
					if (isBody) {
						physx::PxRigidBody* body = actor->is<physx::PxRigidBody>();
						mass = body->getMass();
					}
					fprintf(Con::fpout, "pos %.2f %.2f %.2f %d %.2f %llx %llx\n", pos.x, pos.y, pos.z, int(isBody), mass, actor->userData, actor);
					fflush(Con::fpout);
				} else {
					if ((physList[i].id & 0xFFFFFF) != (i & 0xFFFFFF)) {
						break;
					}
				}
/*				if (physList[i].actor != nullptr) {
					if (physList[i].id != i) {
						break;
					}
					physx::PxActor* actor = physList[i].actor;
					physx::PxRigidActor* rigid = actor->is<physx::PxRigidActor>();
					physx::PxVec3 pos = rigid->getGlobalPose().p;
					fprintf(Con::fpout, "pos %.2f %.2f %.2f\n", pos.x, pos.y, pos.z);
					fflush(Con::fpout);
				}*/
			}
			fflush(Con::fpout);
			//fclose(f);
			//maybeOpenDebug();
		} else {
			setRunString(buff);
		}
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