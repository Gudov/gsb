#pragma once
#include <dxgi.h>
#include <d3d11.h>

#include <dxgi1_2.h>

typedef HRESULT (*D3D11CreateDeviceAndSwapChain_type)(
    _In_opt_ IDXGIAdapter* pAdapter,
    D3D_DRIVER_TYPE DriverType,
    HMODULE Software,
    UINT Flags,
    _In_reads_opt_(FeatureLevels) CONST D3D_FEATURE_LEVEL* pFeatureLevels,
    UINT FeatureLevels,
    UINT SDKVersion,
    _In_opt_ CONST DXGI_SWAP_CHAIN_DESC* pSwapChainDesc,
    _COM_Outptr_opt_ IDXGISwapChain** ppSwapChain,
    _COM_Outptr_opt_ ID3D11Device** ppDevice,
    _Out_opt_ D3D_FEATURE_LEVEL* pFeatureLevel,
    _COM_Outptr_opt_ ID3D11DeviceContext** ppImmediateContext);

typedef HRESULT(*D3D11CreateDevice_type)(
    _In_opt_ IDXGIAdapter* pAdapter,
    D3D_DRIVER_TYPE DriverType,
    HMODULE Software,
    UINT Flags,
    _In_reads_opt_(FeatureLevels) CONST D3D_FEATURE_LEVEL* pFeatureLevels,
    UINT FeatureLevels,
    UINT SDKVersion,
    _COM_Outptr_opt_ ID3D11Device** ppDevice,
    _Out_opt_ D3D_FEATURE_LEVEL* pFeatureLevel,
    _COM_Outptr_opt_ ID3D11DeviceContext** ppImmediateContext);

typedef HRESULT(STDMETHODCALLTYPE* CreateSwapChainForHwnd_type)(
    IDXGIFactory2* This,
    /* [annotation][in] */
    _In_  ID3D11Device* pDevice,
    /* [annotation][in] */
    _In_  HWND hWnd,
    /* [annotation][in] */
    _In_  const DXGI_SWAP_CHAIN_DESC1* pDesc,
    /* [annotation][in] */
    _In_opt_  const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* pFullscreenDesc,
    /* [annotation][in] */
    _In_opt_  IDXGIOutput* pRestrictToOutput,
    /* [annotation][out] */
    _COM_Outptr_  IDXGISwapChain1** ppSwapChain);

void initDxHook();