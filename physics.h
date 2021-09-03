#pragma once
#include <PxActor.h>
#include <atomic>
#include <memory>
#include <vector>

struct bodyData {
	physx::PxVec3 pos;
	float mass;
};

extern std::shared_ptr<std::vector<bodyData>> bodys;

int updatePhysicsThread();