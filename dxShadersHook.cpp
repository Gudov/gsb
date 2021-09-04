#include "dxShadersHook.h"
#include "MinHook.h" //detour x86&x64
#include <d3d11.h>
#include <D3Dcompiler.h>
#include <dxgidebug.h>
#include <DirectXMath.h>
#include "dxShadersDump.h"

#pragma comment(lib, "D3dcompiler.lib")
using namespace DirectX;

static HRESULT(WINAPI* d3d11_CreatePixelShader)(ID3D11Device*, const void*, SIZE_T, ID3D11ClassLinkage*, ID3D11PixelShader**);
static HRESULT(WINAPI* d3d11_CreateVertexShader)(ID3D11Device*, const void*, SIZE_T, ID3D11ClassLinkage*, ID3D11VertexShader**);
static HRESULT(WINAPI* d3d11_CreateComputeShader)(ID3D11Device*, const void*, SIZE_T, ID3D11ClassLinkage*, ID3D11ComputeShader**);
static HRESULT(WINAPI* d3d11_CreateHullShader)(ID3D11Device*, const void*, SIZE_T, ID3D11ClassLinkage*, ID3D11HullShader**);
static HRESULT(WINAPI* d3d11_CreateDomainShader)(ID3D11Device*, const void*, SIZE_T, ID3D11ClassLinkage*, ID3D11DomainShader**);
static HRESULT(WINAPI* d3d11_CreateGeometryShader)(ID3D11Device*, const void*, SIZE_T, ID3D11ClassLinkage*, ID3D11GeometryShader**);
static HRESULT(WINAPI* d3d11_CreateGeometryShaderWithStreamOutput)(ID3D11Device*, const void*, SIZE_T, const D3D11_SO_DECLARATION_ENTRY*, UINT, const UINT*, UINT, UINT, ID3D11ClassLinkage*, ID3D11GeometryShader**);

static bool dumpshader = false;

static HRESULT WINAPI PixelShaderHook(ID3D11Device* pDevice, const void* bytecode, SIZE_T length, ID3D11ClassLinkage* linkage, ID3D11PixelShader** shader)
{
	//Log("A");
	if (shader && dumpshader)
		ShaderHook(pDevice, "ps", &bytecode, &length);
	return d3d11_CreatePixelShader(pDevice, bytecode, length, linkage, shader);
}

static HRESULT WINAPI VertexShaderHook(ID3D11Device* pDevice, const void* bytecode, SIZE_T length, ID3D11ClassLinkage* linkage, ID3D11VertexShader** shader)
{
	//Log("B");
	if (shader && dumpshader)
		ShaderHook(pDevice, "vs", &bytecode, &length);
	return d3d11_CreateVertexShader(pDevice, bytecode, length, linkage, shader);
}

static HRESULT WINAPI ComputeShaderHook(ID3D11Device* pDevice, const void* bytecode, SIZE_T length, ID3D11ClassLinkage* linkage, ID3D11ComputeShader** shader)
{
	if (shader)
		ShaderHook(pDevice, "cs", &bytecode, &length);
	return d3d11_CreateComputeShader(pDevice, bytecode, length, linkage, shader);
}

static HRESULT WINAPI HullShaderHook(ID3D11Device* pDevice, const void* bytecode, SIZE_T length, ID3D11ClassLinkage* linkage, ID3D11HullShader** shader)
{
	if (shader)
		ShaderHook(pDevice, "hs", &bytecode, &length);
	return d3d11_CreateHullShader(pDevice, bytecode, length, linkage, shader);
}

static HRESULT WINAPI DomainShaderHook(ID3D11Device* pDevice, const void* bytecode, SIZE_T length, ID3D11ClassLinkage* linkage, ID3D11DomainShader** shader)
{
	if (shader)
		ShaderHook(pDevice, "ds", &bytecode, &length);
	return d3d11_CreateDomainShader(pDevice, bytecode, length, linkage, shader);
}

static HRESULT WINAPI GeometryShaderHook(ID3D11Device* pDevice, const void* bytecode, SIZE_T length, ID3D11ClassLinkage* linkage, ID3D11GeometryShader** shader)
{
	if (shader)
		ShaderHook(pDevice, "gs", &bytecode, &length);
	return d3d11_CreateGeometryShader(pDevice, bytecode, length, linkage, shader);
}

static HRESULT WINAPI GeometryShaderWithStreamOutputHook(ID3D11Device* pDevice, const void* bytecode, SIZE_T length, const D3D11_SO_DECLARATION_ENTRY* entries, UINT entry_count, const UINT* strides, UINT stride_count, UINT stream, ID3D11ClassLinkage* linkage, ID3D11GeometryShader** shader)
{
	if (shader)
		ShaderHook(pDevice, "gs", &bytecode, &length);
	return d3d11_CreateGeometryShaderWithStreamOutput(pDevice, bytecode, length, entries, entry_count, strides, stride_count, stream, linkage, shader);
}


void initDxSharesHooks(DWORD_PTR* pDeviceVTable) {
	if (MH_CreateHook((DWORD_PTR*)pDeviceVTable[15], PixelShaderHook, reinterpret_cast<void**>(&d3d11_CreatePixelShader)) != MH_OK) { MessageBoxA(nullptr, "PixelShaderHook", "PixelShaderHook", MB_OK); }
	if (MH_EnableHook((DWORD_PTR*)pDeviceVTable[15]) != MH_OK) { MessageBoxA(nullptr, "PixelShaderHook", "PixelShaderHook", MB_OK); }
	if (MH_CreateHook((DWORD_PTR*)pDeviceVTable[12], VertexShaderHook, reinterpret_cast<void**>(&d3d11_CreateVertexShader)) != MH_OK) { MessageBoxA(nullptr, "VertexShaderHook", "VertexShaderHook", MB_OK); }
	if (MH_EnableHook((DWORD_PTR*)pDeviceVTable[12]) != MH_OK) { MessageBoxA(nullptr, "VertexShaderHook", "VertexShaderHook", MB_OK); }
	if (MH_CreateHook((DWORD_PTR*)pDeviceVTable[18], ComputeShaderHook, reinterpret_cast<void**>(&d3d11_CreateComputeShader)) != MH_OK) { MessageBoxA(nullptr, "ComputeShaderHook", "ComputeShaderHook", MB_OK); }
	if (MH_EnableHook((DWORD_PTR*)pDeviceVTable[18]) != MH_OK) { MessageBoxA(nullptr, "ComputeShaderHook", "ComputeShaderHook", MB_OK); }
	if (MH_CreateHook((DWORD_PTR*)pDeviceVTable[16], HullShaderHook, reinterpret_cast<void**>(&d3d11_CreateHullShader)) != MH_OK) { MessageBoxA(nullptr, "HullShaderHook", "HullShaderHook", MB_OK); }
	if (MH_EnableHook((DWORD_PTR*)pDeviceVTable[16]) != MH_OK) { MessageBoxA(nullptr, "HullShaderHook", "HullShaderHook", MB_OK); }
	if (MH_CreateHook((DWORD_PTR*)pDeviceVTable[17], DomainShaderHook, reinterpret_cast<void**>(&d3d11_CreateDomainShader)) != MH_OK) { MessageBoxA(nullptr, "DomainShaderHook", "DomainShaderHook", MB_OK); }
	if (MH_EnableHook((DWORD_PTR*)pDeviceVTable[17]) != MH_OK) { MessageBoxA(nullptr, "DomainShaderHook", "DomainShaderHook", MB_OK); }
	if (MH_CreateHook((DWORD_PTR*)pDeviceVTable[13], GeometryShaderHook, reinterpret_cast<void**>(&d3d11_CreateGeometryShader)) != MH_OK) { MessageBoxA(nullptr, "GeometryShaderHook", "GeometryShaderHook", MB_OK); }
	if (MH_EnableHook((DWORD_PTR*)pDeviceVTable[13]) != MH_OK) { MessageBoxA(nullptr, "GeometryShaderHook", "GeometryShaderHook", MB_OK); }
	if (MH_CreateHook((DWORD_PTR*)pDeviceVTable[14], GeometryShaderWithStreamOutputHook, reinterpret_cast<void**>(&d3d11_CreateGeometryShaderWithStreamOutput)) != MH_OK) { MessageBoxA(nullptr, "GeometryShaderWithStreamOutputHook", "GeometryShaderWithStreamOutputHook", MB_OK); }
	if (MH_EnableHook((DWORD_PTR*)pDeviceVTable[14]) != MH_OK) { MessageBoxA(nullptr, "GeometryShaderWithStreamOutputHook", "GeometryShaderWithStreamOutputHook", MB_OK); }
}
