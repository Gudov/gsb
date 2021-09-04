#include "render.h"
#include <foundation/PxVec2.h>

static DirectX::XMMATRIX statProj{
			1, 0, 0, 0,
			0, 1.78f, 0, 0,
			0, 0, -1.9f, -1,
			0, 0, 0, 0
};

float ViewportWidth;
float ViewportHeight;

float worldView[4][4];

float* getStaticGameWorldView() {
	return (float*)worldView;
}

void setDisplaySize(float w, float h)
{
	ViewportHeight = h;
	ViewportWidth = w;
}

DirectX::XMMATRIX& getStaticProjMat()
{
	return statProj;
}

DirectX::XMMATRIX transformGameViewMateix(float viewMat[4][4])
{
	viewMat[3][0] = 0;
	viewMat[3][3] = 1;
	DirectX::XMMATRIX localWorld = DirectX::XMMatrixTranspose(*((DirectX::FXMMATRIX*)viewMat));
	return localWorld;
}

DirectX::XMMATRIX& getViewProjMat(DirectX::XMMATRIX& viewMat, DirectX::XMMATRIX& projMat)
{
	DirectX::XMMATRIX viewProjMatrix = DirectX::XMMatrixMultiply(viewMat, projMat);
	return viewProjMatrix;
}

physx::PxVec2 worldToScreen(physx::PxVec3 worldPos, physx::PxVec3 camPos, DirectX::XMMATRIX& WorldViewProj)
{
	physx::PxVec3 localPos = camPos - worldPos;
	DirectX::XMVECTOR Pos = DirectX::XMVectorSet(localPos.x, localPos.y, localPos.z, 1.0f);

	float mx = Pos.m128_f32[0] * WorldViewProj.r[0].m128_f32[0] + Pos.m128_f32[1] * WorldViewProj.r[1].m128_f32[0] + Pos.m128_f32[2] * WorldViewProj.r[2].m128_f32[0] + WorldViewProj.r[3].m128_f32[0];
	float my = Pos.m128_f32[0] * WorldViewProj.r[0].m128_f32[1] + Pos.m128_f32[1] * WorldViewProj.r[1].m128_f32[1] + Pos.m128_f32[2] * WorldViewProj.r[2].m128_f32[1] + WorldViewProj.r[3].m128_f32[1];
	float mz = Pos.m128_f32[0] * WorldViewProj.r[0].m128_f32[2] + Pos.m128_f32[1] * WorldViewProj.r[1].m128_f32[2] + Pos.m128_f32[2] * WorldViewProj.r[2].m128_f32[2] + WorldViewProj.r[3].m128_f32[2];
	float mw = Pos.m128_f32[0] * WorldViewProj.r[0].m128_f32[3] + Pos.m128_f32[1] * WorldViewProj.r[1].m128_f32[3] + Pos.m128_f32[2] * WorldViewProj.r[2].m128_f32[3] + WorldViewProj.r[3].m128_f32[3];

	float xx, yy;
	xx = ((mx / mw) * (ViewportWidth / 2.0f)) + (ViewportWidth / 2.0f);
	yy = (ViewportHeight / 2.0f) - ((my / mw) * (ViewportHeight / 2.0f)); //- or + depends on the game

	if (mw > 0.0f) {
		return physx::PxVec2(ViewportWidth - xx, ViewportWidth - yy);
	}
	return physx::PxVec2(-100, -100);
}
