#pragma once

#include <PxActor.h>
#include <DirectXMath.h>

float* getStaticGameWorldView();
void setDisplaySize(float w, float h);
DirectX::XMMATRIX &getStaticProjMat();
DirectX::XMMATRIX transformGameViewMateix(float viewMat[4][4]);
DirectX::XMMATRIX &getViewProjMat(DirectX::XMMATRIX &viewMat, DirectX::XMMATRIX &projMat);
physx::PxVec2 worldToScreen(physx::PxVec3 worldPos, physx::PxVec3 camPos, DirectX::XMMATRIX &viewProjMat);