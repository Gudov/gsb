#pragma once
#include <dxgi.h>
#include <d3d11.h>
#include <dxgi1_2.h>

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

void initDxHooks2();