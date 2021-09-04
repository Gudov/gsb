#pragma once
#include <stdint.h>
#include <d3d11.h>
#include <Windows.h>

ID3D11Buffer* CopyBufferToCpuA(ID3D11DeviceContext* pContext, ID3D11Device* pDevice, ID3D11Buffer* pBufferA);
void GenerateTexture(ID3D11Device* pDevice, uint32_t pixelcolor, DXGI_FORMAT format);
void MapBuffer(ID3D11DeviceContext* pContext, ID3D11Buffer* pStageBuffer, void** ppData, UINT* pByteWidth);
void UnmapBuffer(ID3D11DeviceContext* pContext, ID3D11Buffer* pStageBuffer);