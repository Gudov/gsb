#pragma once

#include <PxActor.h>
#include <DirectXMath.h>

float* getStaticGameWorldView();
void setDisplaySize(float w, float h);
DirectX::XMMATRIX &getStaticProjMat();
void updateWorldViewProj();
physx::PxVec2 worldToScreen(physx::PxVec3 worldPos);
physx::PxVec2 worldToScreenIgnoreDirection(physx::PxVec3 worldPos);
void setCamPos(physx::PxVec3 camPos);