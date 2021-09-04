#include "dxHooks.h"
#include "hookUtils.h"
#include <Windows.h>
#include <D3Dcompiler.h> //generateshader
#include "MinHook.h" //detour x86&x64
#pragma comment(lib, "D3dcompiler.lib")
#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>
#include <dxgidebug.h>
#include "physics.h"
#include "gameHooks.h"
#include <PxRigidActor.h>
#include <PxScene.h>
#include <PxAggregate.h>
#include <PxRigidBody.h>
#include <PxRigidStatic.h>

//DX Includes
#include <DirectXMath.h>
using namespace DirectX;

D3D11CreateDeviceAndSwapChain_type or_D3D11CreateDeviceAndSwapChain;
D3D11CreateDevice_type or_D3D11CreateDevice;

IDXGISwapChain* pSwapChain;


typedef HRESULT(__stdcall* D3D11PresentHook) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef HRESULT(__stdcall* D3D11Present1Hook) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags, const DXGI_PRESENT_PARAMETERS* pPresentParameters);
typedef HRESULT(__stdcall* D3D11ResizeBuffersHook) (IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);

typedef void(__stdcall* D3D11DrawIndexedHook) (ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation);
typedef void(__stdcall* D3D11DrawIndexedInstancedHook) (ID3D11DeviceContext* pContext, UINT IndexCountPerInstance, UINT InstanceCount, UINT StartIndexLocation, INT BaseVertexLocation, UINT StartInstanceLocation);
typedef void(__stdcall* D3D11DrawHook) (ID3D11DeviceContext* pContext, UINT VertexCount, UINT StartVertexLocation);

typedef void(__stdcall* D3D11PSSetShaderResourcesHook) (ID3D11DeviceContext* pContext, UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews);
typedef void(__stdcall* D3D11VSSetConstantBuffersHook) (ID3D11DeviceContext* pContext, UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers);


D3D11PresentHook phookD3D11Present = NULL;
D3D11Present1Hook phookD3D11Present1 = NULL;

D3D11ResizeBuffersHook phookD3D11ResizeBuffers = NULL;

D3D11DrawIndexedHook phookD3D11DrawIndexed = NULL;
D3D11DrawIndexedInstancedHook phookD3D11DrawIndexedInstanced = NULL;
D3D11DrawHook phookD3D11Draw = NULL;

D3D11PSSetShaderResourcesHook phookD3D11PSSetShaderResources = NULL;
D3D11VSSetConstantBuffersHook phookD3D11VSSetConstantBuffers = NULL;


ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;

DWORD_PTR* pSwapChainVtable = NULL;
DWORD_PTR* pContextVTable = NULL;
DWORD_PTR* pDeviceVTable = NULL;

#include "dxHookUtils.h"

float worldView[4][4];
//==========================================================================================================================

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
HWND window = NULL;
WNDPROC oWndProc;

void InitImGuiD3D11()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

	ImGui::StyleColorsClassic();

	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) {
		return true;
	}
	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

//==========================================================================================================================

HRESULT __stdcall hookD3D11ResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{
	ImGui_ImplDX11_InvalidateDeviceObjects();
	if (nullptr != mainRenderTargetViewD3D11) { mainRenderTargetViewD3D11->Release(); mainRenderTargetViewD3D11 = nullptr; }

	HRESULT toReturn = phookD3D11ResizeBuffers(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);

	ImGui_ImplDX11_CreateDeviceObjects();

	return phookD3D11ResizeBuffers(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);
}

//==========================================================================================================================

HRESULT __stdcall hookD3D11Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!initonce)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetViewD3D11);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGuiD3D11();

			// Create depthstencil state
			D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
			depthStencilDesc.DepthEnable = TRUE;
			depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
			depthStencilDesc.DepthFunc = D3D11_COMPARISON_ALWAYS;
			depthStencilDesc.StencilEnable = FALSE;
			depthStencilDesc.StencilReadMask = 0xFF;
			depthStencilDesc.StencilWriteMask = 0xFF;
			// Stencil operations if pixel is front-facing
			depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
			depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
			// Stencil operations if pixel is back-facing
			depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
			depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
			pDevice->CreateDepthStencilState(&depthStencilDesc, &DepthStencilState_FALSE);

			GenerateTexture(0xff00ff00, DXGI_FORMAT_R10G10B10A2_UNORM); //DXGI_FORMAT_R32G32B32A32_FLOAT); //DXGI_FORMAT_R8G8B8A8_UNORM; 

			//load cfg settings
			LoadCfg();

			initonce = true;
		}
		else
			return phookD3D11Present(pSwapChain, SyncInterval, Flags);
	}

	//create shaders
	if (!sGreen)
		GenerateShader(pDevice, &sGreen, 0.0f, 1.0f, 0.0f); //green

	if (!sMagenta)
		GenerateShader(pDevice, &sMagenta, 1.0f, 0.0f, 1.0f); //magenta

	//recreate rendertarget on reset
	if (mainRenderTargetViewD3D11 == NULL)
	{
		ID3D11Texture2D* pBackBuffer = NULL;
		pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
		pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetViewD3D11);
		pBackBuffer->Release();
	}

	//get imgui displaysize
	ImGuiIO io = ImGui::GetIO();
	ViewportWidth = io.DisplaySize.x;
	ViewportHeight = io.DisplaySize.y;
	ScreenCenterX = ViewportWidth / 2.0f;
	ScreenCenterY = ViewportHeight / 2.0f;

	if (GetAsyncKeyState(VK_INSERT) & 1) {
		SaveCfg(); //save settings
		showmenu = !showmenu;
	}


	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (showmenu) {

		ImGui::Begin("Hack Menu");
		ImGui::Checkbox("Wallhack", &wallhack);
		ImGui::Checkbox("Chams", &chams);
		ImGui::Checkbox("Esp", &esp);
		//circle esp
		//line esp
		//text esp
		//distance esp
		ImGui::Checkbox("Aimbot", &aimbot);
		ImGui::SliderInt("Aimsens", &aimsens, 0, 10);
		ImGui::Text("Aimkey");
		const char* aimkey_Options[] = { "Shift", "Right Mouse", "Left Mouse", "Middle Mouse", "Ctrl", "Alt", "Capslock", "Space", "X", "C", "V" };
		ImGui::SameLine();
		ImGui::Combo("##AimKey", (int*)&aimkey, aimkey_Options, IM_ARRAYSIZE(aimkey_Options));
		ImGui::SliderInt("Aimfov", &aimfov, 0, 10);
		ImGui::SliderInt("Aimspeed uses distance", &aimspeed_isbasedon_distance, 0, 4);
		ImGui::SliderInt("Aimspeed", &aimspeed, 0, 100);
		ImGui::SliderInt("Aimheight", &aimheight, 0, 200);
		ImGui::Checkbox("Autoshoot", &autoshoot);
		ImGui::SliderInt("As xhair dst", &as_xhairdst, 0, 20);
		//as_compensatedst

		ImGui::Checkbox("Modelrecfinder", &modelrecfinder);
		if (modelrecfinder == 1)
		{
			if (check_draw_result == 1)ImGui::Text("Draw called."); ImGui::SameLine();
			if (check_drawindexed_result == 1)ImGui::Text("DrawIndexed called."); ImGui::SameLine();
			if (check_drawindexedinstanced_result == 1)ImGui::Text("DrawIndexedInstanced called.");

			//ImGui::SliderInt("Modelfind Mode", &modelfindmode, 1, 3);
			ImGui::NewLine();
			if (modelfindmode == 1)ImGui::SliderInt("Modelfind Mode 1 (Step 10)", &modelfindmode, 1, 3);
			else if (modelfindmode == 2)ImGui::SliderInt("Modelfind Mode 2 (Step 100)", &modelfindmode, 1, 3);
			else if (modelfindmode == 3)ImGui::SliderInt("Modelfind Mode 3 (Step 1000)", &modelfindmode, 1, 3);

			//bruteforce
			ImGui::SliderInt("find Stride", &countStride, -1, 100);
			ImGui::SliderInt("find IndexCount", &countIndexCount, -1, 100);
			ImGui::SliderInt("find veWidth", &countveWidth, -1, 100);
			ImGui::SliderInt("find pscWidth", &countpscWidth, -1, 100);

		}
		ImGui::Checkbox("Dump Shader", &dumpshader);

		ImGui::Checkbox("Wtsfinder", &wtsfinder);
		if (wtsfinder == 1)
		{
			ImGui::Text("valid vscStartSlot = %d", validvscStartSlot);
			ImGui::Checkbox("method1", &method1);
			ImGui::Checkbox("method2", &method2);
			ImGui::Checkbox("method3", &method3);
			ImGui::Checkbox("method4", &method4);

			DWORD dwTicks = GetTickCount();
			if ((dwTicks - g_dwLastAction) >= 1000)
			{
				//reset buffer every second while bruteforcing values
				//Log("do something if 1 second has passed");

				//reset to avoid wrong values
				pStageBufferA = NULL;
				pStageBufferB = NULL;

				//reset var to current ticks
				g_dwLastAction = dwTicks;
			}
			//bruteforce
			ImGui::SliderInt("WorldViewCBnum", &WorldViewCBnum, 0, 10);
			ImGui::SliderInt("ProjCBnum", &ProjCBnum, 0, 10);
			ImGui::SliderInt("matProjnum", &matProjnum, 0, 100);//240
		}

		ImGui::End();
	}


	targetfound = false;
	//do esp
	if (esp == 1)
	{
		ImGui::Begin("Transparent", reinterpret_cast<bool*>(true), ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBackground);
		ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
		ImGui::SetWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y), ImGuiCond_Always);

		if (AimEspInfo.size() != NULL)
		{
			for (unsigned int i = 0; i < AimEspInfo.size(); i++)
			{
				if (AimEspInfo[i].vOutX > 1 && AimEspInfo[i].vOutY > 1 && AimEspInfo[i].vOutX < ViewportWidth && AimEspInfo[i].vOutY < ViewportHeight)
				{
					//text esp
					ImGui::GetWindowDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(AimEspInfo[i].vOutX, AimEspInfo[i].vOutY), ImColor(255, 255, 255, 255), "Model", 0, 0.0f, 0); //draw text
				}
			}
		}
		ImGui::End();
	}

	if (aimkey == 0) Daimkey = VK_SHIFT;
	if (aimkey == 1) Daimkey = VK_RBUTTON;
	if (aimkey == 2) Daimkey = VK_LBUTTON;
	if (aimkey == 3) Daimkey = VK_MBUTTON;
	if (aimkey == 4) Daimkey = VK_CONTROL;
	if (aimkey == 5) Daimkey = VK_MENU;
	if (aimkey == 6) Daimkey = VK_CAPITAL;
	if (aimkey == 7) Daimkey = VK_SPACE;
	if (aimkey == 8) Daimkey = 0x58; //X
	if (aimkey == 9) Daimkey = 0x43; //C
	if (aimkey == 10) Daimkey = 0x56; //V

	//aimbot
	if (aimbot == 1)//aimbot pve, aimbot pvp
		if (AimEspInfo.size() != NULL)
		{
			UINT BestTarget = -1;
			DOUBLE fClosestPos = 99999;

			for (unsigned int i = 0; i < AimEspInfo.size(); i++)
			{
				//aimfov
				float radiusx = (aimfov * 10.0f) * (ScreenCenterX / 100.0f);
				float radiusy = (aimfov * 10.0f) * (ScreenCenterY / 100.0f);

				//get crosshairdistance
				AimEspInfo[i].CrosshairDst = GetDst(AimEspInfo[i].vOutX, AimEspInfo[i].vOutY, ViewportWidth / 2.0f, ViewportHeight / 2.0f);

				//if in fov
				if (AimEspInfo[i].vOutX >= ScreenCenterX - radiusx && AimEspInfo[i].vOutX <= ScreenCenterX + radiusx && AimEspInfo[i].vOutY >= ScreenCenterY - radiusy && AimEspInfo[i].vOutY <= ScreenCenterY + radiusy)

					//get closest/nearest target to crosshair
					if (AimEspInfo[i].CrosshairDst < fClosestPos)
					{
						fClosestPos = AimEspInfo[i].CrosshairDst;
						BestTarget = i;
					}
			}

			//if nearest target to crosshair
			if (BestTarget != -1)
			{
				//double DistX = AimEspInfo[BestTarget].vOutX - ScreenCenterX;
				//double DistY = AimEspInfo[BestTarget].vOutY - ScreenCenterY;

				//DistX /= aimsens * 0.5f;
				//DistY /= aimsens * 0.5f;

				//aim
				//if (GetAsyncKeyState(Daimkey) & 0x8000)
					//mouse_event(MOUSEEVENTF_MOVE, (float)DistX, (float)DistY, 0, NULL);

				//aim
				if (GetAsyncKeyState(Daimkey) & 0x8000)
					AimAtPos(AimEspInfo[BestTarget].vOutX, AimEspInfo[BestTarget].vOutY);

				//get crosshairdistance
				//AimEspInfo[BestTarget].CrosshairDst = GetDst(AimEspInfo[BestTarget].vOutX, AimEspInfo[BestTarget].vOutY, ViewportWidth / 2.0f, ViewportHeight / 2.0f);

				//stabilise aim
				if (aimspeed_isbasedon_distance == 0) //default steady aimsens
					AimSpeed = aimsens;
				else if (aimspeed_isbasedon_distance == 1)
					AimSpeed = aimsens + (AimEspInfo[BestTarget].CrosshairDst * 0.008f); //0.01f the bigger the distance the slower the aimspeed
				else if (aimspeed_isbasedon_distance == 2)
					AimSpeed = aimsens + (AimEspInfo[BestTarget].CrosshairDst * 0.01f); //0.01f the bigger the distance the slower the aimspeed
				else if (aimspeed_isbasedon_distance == 3)
					AimSpeed = aimsens + (AimEspInfo[BestTarget].CrosshairDst * 0.012f); //0.01f the bigger the distance the slower the aimspeed
					//AimSpeed = aimsens + (rand() % 100 / CrosshairDst);     
				else if (aimspeed_isbasedon_distance == 4)
				{
					AimSpeed = aimsens + (75.0f / AimEspInfo[BestTarget].CrosshairDst); //100.0f the bigger the distance the faster the aimspeed
					//AimSpeed = aimsens + (50.0f / CrosshairDst); //50.0f the bigger the distance the faster the aimspeed
					//float randomnb = rand() % 2; //both
					//if (randomnb == 0) AimSpeed = aimsens + (75.0f / CrosshairDst); //the bigger the distance the faster the aimspeed
					//else if (randomnb == 1) AimSpeed = aimsens + (CrosshairDst * 0.01f); //the bigger the distance the slower the aimspeed
				}

				//autoshoot on
				if (autoshoot == 1 && !IsPressed && !GetAsyncKeyState(VK_LBUTTON) && GetAsyncKeyState(Daimkey) & 0x8000 && AimEspInfo[BestTarget].CrosshairDst <= as_xhairdst)//if crosshairdst smaller than as_xhairdist then fire                            
				{
					mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
					IsPressed = true;
				}
			}
		}
	AimEspInfo.clear();

	//autoshoot off
	if ((autoshoot == 1 && IsPressed && !targetfound) || (autoshoot == 1 && IsPressed && !GetAsyncKeyState(Daimkey)))
	{
		IsPressed = false;
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	}


	//ImGui::EndFrame();
	ImGui::Render();
	pContext->OMSetRenderTargets(1, &mainRenderTargetViewD3D11, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	return phookD3D11Present(pSwapChain, SyncInterval, Flags);
}
//==========================================================================================================================

int DrawIndexedInstanced = 0;
int Draw = 0;
int DrawIndexed = 0;

void addToScreeen(DirectX::XMMATRIX viewProjMatrix, DirectX::XMVECTOR Pos, char* buff) {
	//normal
	DirectX::XMMATRIX WorldViewProj = viewProjMatrix; //normal

	float mx = Pos.m128_f32[0] * WorldViewProj.r[0].m128_f32[0] + Pos.m128_f32[1] * WorldViewProj.r[1].m128_f32[0] + Pos.m128_f32[2] * WorldViewProj.r[2].m128_f32[0] + WorldViewProj.r[3].m128_f32[0];
	float my = Pos.m128_f32[0] * WorldViewProj.r[0].m128_f32[1] + Pos.m128_f32[1] * WorldViewProj.r[1].m128_f32[1] + Pos.m128_f32[2] * WorldViewProj.r[2].m128_f32[1] + WorldViewProj.r[3].m128_f32[1];
	float mz = Pos.m128_f32[0] * WorldViewProj.r[0].m128_f32[2] + Pos.m128_f32[1] * WorldViewProj.r[1].m128_f32[2] + Pos.m128_f32[2] * WorldViewProj.r[2].m128_f32[2] + WorldViewProj.r[3].m128_f32[2];
	float mw = Pos.m128_f32[0] * WorldViewProj.r[0].m128_f32[3] + Pos.m128_f32[1] * WorldViewProj.r[1].m128_f32[3] + Pos.m128_f32[2] * WorldViewProj.r[2].m128_f32[3] + WorldViewProj.r[3].m128_f32[3];

	float xx, yy;
	xx = ((mx / mw) * (ViewportWidth / 2.0f)) + (ViewportWidth / 2.0f);
	yy = (ViewportHeight / 2.0f) - ((my / mw) * (ViewportHeight / 2.0f)); //- or + depends on the game

	ImGui::GetWindowDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(2560 - xx, yy), ImColor(255, 255, 255, 255), buff, 0, 0.0f, 0); //draw text
	ImGui::GetWindowDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(2560 - xx, 1440 - yy), ImColor(0, 255, 255, 255), buff, 0, 0.0f, 0); //draw text
	ImGui::GetWindowDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(xx, 1440 - yy), ImColor(255, 0, 255, 255), buff, 0, 0.0f, 0); //draw text
}

HRESULT __stdcall hookD3D11Present1(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags, const DXGI_PRESENT_PARAMETERS* pPresentParameters)
{
	if (!initonce)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetViewD3D11);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGuiD3D11();

			// Create depthstencil state
			D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
			depthStencilDesc.DepthEnable = TRUE;
			depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
			depthStencilDesc.DepthFunc = D3D11_COMPARISON_ALWAYS;
			depthStencilDesc.StencilEnable = FALSE;
			depthStencilDesc.StencilReadMask = 0xFF;
			depthStencilDesc.StencilWriteMask = 0xFF;
			// Stencil operations if pixel is front-facing
			depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
			depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
			// Stencil operations if pixel is back-facing
			depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
			depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
			pDevice->CreateDepthStencilState(&depthStencilDesc, &DepthStencilState_FALSE);

			GenerateTexture(0xff00ff00, DXGI_FORMAT_R10G10B10A2_UNORM); //DXGI_FORMAT_R32G32B32A32_FLOAT); //DXGI_FORMAT_R8G8B8A8_UNORM; 

			//load cfg settings
			LoadCfg();

			initonce = true;
		}
		else
			return phookD3D11Present(pSwapChain, SyncInterval, Flags);
	}

	Draw = 0;

	//create shaders
	if (!sGreen)
		GenerateShader(pDevice, &sGreen, 0.0f, 1.0f, 0.0f); //green

	if (!sMagenta)
		GenerateShader(pDevice, &sMagenta, 1.0f, 0.0f, 1.0f); //magenta

	//recreate rendertarget on reset
	if (mainRenderTargetViewD3D11 == NULL)
	{
		ID3D11Texture2D* pBackBuffer = NULL;
		pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
		pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetViewD3D11);
		pBackBuffer->Release();
	}

	//get imgui displaysize
	ImGuiIO io = ImGui::GetIO();
	ViewportWidth = io.DisplaySize.x;
	ViewportHeight = io.DisplaySize.y;
	ScreenCenterX = ViewportWidth / 2.0f;
	ScreenCenterY = ViewportHeight / 2.0f;

	if (GetAsyncKeyState(VK_INSERT) & 1) {
		SaveCfg(); //save settings
		showmenu = !showmenu;
	}


	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	static bool drawMap = false;
	static float xoffset = 0;
	static float yoffset = 0;
	static float scale = 0;
	static bool drawDebugMat = false;

	if (showmenu) {

		ImGui::Begin("Hack Menu");
		ImGui::Checkbox("Wallhack", &wallhack);
		ImGui::Checkbox("Chams", &chams);
		ImGui::Checkbox("Esp", &esp);
		//circle esp
		//line esp
		//text esp
		//distance esp
		ImGui::Checkbox("Aimbot", &aimbot);
		ImGui::SliderInt("Aimsens", &aimsens, 0, 10);
		ImGui::Text("Aimkey");
		const char* aimkey_Options[] = { "Shift", "Right Mouse", "Left Mouse", "Middle Mouse", "Ctrl", "Alt", "Capslock", "Space", "X", "C", "V" };
		ImGui::SameLine();
		ImGui::Combo("##AimKey", (int*)&aimkey, aimkey_Options, IM_ARRAYSIZE(aimkey_Options));
		ImGui::SliderInt("Aimfov", &aimfov, 0, 10);
		ImGui::SliderInt("Aimspeed uses distance", &aimspeed_isbasedon_distance, 0, 4);
		ImGui::SliderInt("Aimspeed", &aimspeed, 0, 100);
		ImGui::SliderInt("Aimheight", &aimheight, 0, 200);
		ImGui::Checkbox("Autoshoot", &autoshoot);
		ImGui::SliderInt("As xhair dst", &as_xhairdst, 0, 20);
		//as_compensatedst

		ImGui::Checkbox("Modelrecfinder", &modelrecfinder);
		if (modelrecfinder == 1)
		{
			if (check_draw_result == 1)ImGui::Text("Draw called."); ImGui::SameLine();
			if (check_drawindexed_result == 1)ImGui::Text("DrawIndexed called."); ImGui::SameLine();
			if (check_drawindexedinstanced_result == 1)ImGui::Text("DrawIndexedInstanced called.");

			//ImGui::SliderInt("Modelfind Mode", &modelfindmode, 1, 3);
			ImGui::NewLine();
			if (modelfindmode == 1)ImGui::SliderInt("Modelfind Mode 1 (Step 10)", &modelfindmode, 1, 3);
			else if (modelfindmode == 2)ImGui::SliderInt("Modelfind Mode 2 (Step 100)", &modelfindmode, 1, 3);
			else if (modelfindmode == 3)ImGui::SliderInt("Modelfind Mode 3 (Step 1000)", &modelfindmode, 1, 3);

			//bruteforce
			ImGui::SliderInt("find Stride", &countStride, -1, 100);
			ImGui::SliderInt("find IndexCount", &countIndexCount, -1, 100);
			ImGui::SliderInt("find veWidth", &countveWidth, -1, 100);
			ImGui::SliderInt("find pscWidth", &countpscWidth, -1, 100);

		}
		ImGui::Checkbox("Dump Shader", &dumpshader);

		ImGui::Checkbox("Wtsfinder", &wtsfinder);
		if (wtsfinder == 1)
		{
			ImGui::Text("valid vscStartSlot = %d", validvscStartSlot);
			ImGui::Checkbox("method1", &method1);
			ImGui::Checkbox("method2", &method2);
			ImGui::Checkbox("method3", &method3);
			ImGui::Checkbox("method4", &method4);

			DWORD dwTicks = GetTickCount();
			if ((dwTicks - g_dwLastAction) >= 1000)
			{
				//reset buffer every second while bruteforcing values
				//Log("do something if 1 second has passed");

				//reset to avoid wrong values
				pStageBufferA = NULL;
				pStageBufferB = NULL;

				//reset var to current ticks
				g_dwLastAction = dwTicks;
			}
			//bruteforce
			ImGui::SliderInt("WorldViewCBnum", &WorldViewCBnum, 0, 10);
			ImGui::SliderInt("ProjCBnum", &ProjCBnum, 0, 10);
			ImGui::SliderInt("matProjnum", &matProjnum, 0, 100);//240
		}

		static bool editProjMat = false;
		ImGui::Checkbox("editProjMat", &editProjMat);
		if (editProjMat) {
			ImGui::PushItemWidth(100);
			ImGui::InputFloat("mat00", &statProj.r[0].m128_f32[0]);
			ImGui::SameLine();
			ImGui::PushItemWidth(100);
			ImGui::InputFloat("mat01", &statProj.r[0].m128_f32[1]);
			ImGui::SameLine();
			ImGui::PushItemWidth(100);
			ImGui::InputFloat("mat02", &statProj.r[0].m128_f32[2]);
			ImGui::SameLine();
			ImGui::PushItemWidth(100);
			ImGui::InputFloat("mat03", &statProj.r[0].m128_f32[3]);

			ImGui::PushItemWidth(100);
			ImGui::InputFloat("mat10", &statProj.r[1].m128_f32[0]);
			ImGui::SameLine();
			ImGui::PushItemWidth(100);
			ImGui::InputFloat("mat11", &statProj.r[1].m128_f32[1]);
			ImGui::SameLine();
			ImGui::PushItemWidth(100);
			ImGui::InputFloat("mat12", &statProj.r[1].m128_f32[2]);
			ImGui::SameLine();
			ImGui::PushItemWidth(100);
			ImGui::InputFloat("mat13", &statProj.r[1].m128_f32[3]);

			ImGui::PushItemWidth(100);
			ImGui::InputFloat("mat20", &statProj.r[2].m128_f32[0]);
			ImGui::SameLine();
			ImGui::PushItemWidth(100);
			ImGui::InputFloat("mat21", &statProj.r[2].m128_f32[1]);
			ImGui::SameLine();
			ImGui::PushItemWidth(100);
			ImGui::InputFloat("mat22", &statProj.r[2].m128_f32[2]);
			ImGui::SameLine();
			ImGui::PushItemWidth(100);
			ImGui::InputFloat("mat23", &statProj.r[2].m128_f32[3]);

			ImGui::PushItemWidth(100);
			ImGui::InputFloat("mat30", &statProj.r[3].m128_f32[0]);
			ImGui::SameLine();
			ImGui::PushItemWidth(100);
			ImGui::InputFloat("mat31", &statProj.r[3].m128_f32[1]);
			ImGui::SameLine();
			ImGui::PushItemWidth(100);
			ImGui::InputFloat("mat32", &statProj.r[3].m128_f32[2]);
			ImGui::SameLine();
			ImGui::PushItemWidth(100);
			ImGui::InputFloat("mat33", &statProj.r[3].m128_f32[3]);

			ImGui::PushItemWidth(100);
			ImGui::InputFloat("xtestoff", &xtestoffset);
			ImGui::SameLine();
			ImGui::PushItemWidth(100);
			ImGui::InputFloat("ytestoff", &ytestoffset);
		}

		ImGui::Checkbox("drawDebugMat", &drawDebugMat);

		ImGui::Checkbox("drawMap", &drawMap);
		if (drawMap) {
			ImGui::PushItemWidth(150);
			ImGui::InputFloat("xoff", &xoffset);
			ImGui::SameLine();
			ImGui::PushItemWidth(150);
			ImGui::InputFloat("yoff", &yoffset);
			ImGui::InputFloat("scale", &scale);
		}

		ImGui::End();
	}


	targetfound = false;
	//do esp
	if (esp == 1)
	{
		ImGui::Begin("Transparent", reinterpret_cast<bool*>(true), ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBackground);
		ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
		ImGui::SetWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y), ImGuiCond_Always);
		
		matWorldView[3][0] = 0;
		matWorldView[3][3] = 1;

		if (drawMap) {
			std::vector<bodyData> bodys;

			for (int i = 0; i < 0xFFFFFF; i++) {
				if (physList[i].entry != nullptr
					&& (physList[i].id & 0xFFFFFF) == i
					&& ((physList[i].entry->id & 0xFFFFFF) == (physList[i].id & 0xFFFFFF))) {
					physx::PxActor* actor = physList[i].entry->actor;
					if (actor == nullptr) {
						continue;
					}
					physx::PxRigidActor* rigid = actor->is<physx::PxRigidActor>();
					if (rigid == nullptr || (uint64_t)rigid > 0xFFFF'FFFF'FFFF'0000) {
						continue;
					}
					physx::PxVec3 pos = rigid->getGlobalPose().p;
					bool isBody = actor->is<physx::PxRigidBody>() != nullptr;
					bool isStatic = actor->is<physx::PxRigidBody>() != nullptr;
					float mass = -1;
					if (isBody) {
						physx::PxRigidBody* body = actor->is<physx::PxRigidBody>();
						mass = body->getMass();
						bodys.push_back({ pos, mass });
					}
				}
				else {
					if ((physList[i].id & 0xFFFFFF) != (i & 0xFFFFFF)) {
						break;
					}
				}
			}

			physx::PxVec3 plyPos;
			for (bodyData body : bodys) {
				if (cmpf(body.mass, 2.287f, 0.01f)) {
					plyPos = body.pos;
				}
			}

			char buff[256];
			sprintf(buff, "%f %f %f", plyPos.x, plyPos.y, plyPos.z);
			ImGui::GetWindowDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(20, 410), ImColor(0, 255, 255, 255), buff, 0, 0.0f, 0); //draw text

			DirectX::XMMATRIX maybeView;
			//DirectX::XMMATRIX localWorld = maybeView = DirectX::XMMatrixTranspose(*((FXMMATRIX*)matWorldView));
			DirectX::XMMATRIX localWorld = maybeView = DirectX::XMMatrixTranspose(*((FXMMATRIX*)worldView));
			maybeView.r[0] = localWorld.r[0];
			maybeView.r[1] = localWorld.r[1];
			maybeView.r[2] = localWorld.r[2];
			maybeView.r[3] = localWorld.r[3];

			if (drawDebugMat) {
				ImDrawList* drawList = ImGui::GetWindowDrawList();
				drawList->AddLine(ImVec2(100, 600), ImVec2(localWorld.r[0].m128_f32[0] * 50 + 100, localWorld.r[0].m128_f32[2] * 50 + 600), 0xFF0000FF, 2.0f);
				drawList->AddLine(ImVec2(100, 600), ImVec2(localWorld.r[1].m128_f32[0] * 50 + 100, localWorld.r[1].m128_f32[2] * 50 + 600), 0xFF00FF00, 2.0f);
				drawList->AddLine(ImVec2(100, 600), ImVec2(localWorld.r[2].m128_f32[0] * 50 + 100, localWorld.r[2].m128_f32[2] * 50 + 600), 0xFFFF0000, 2.0f);

				drawList->AddLine(ImVec2(200, 600), ImVec2(localWorld.r[0].m128_f32[1] * 50 + 200, localWorld.r[0].m128_f32[2] * 50 + 600), 0xFF0000FF, 2.0f);
				drawList->AddLine(ImVec2(200, 600), ImVec2(localWorld.r[1].m128_f32[1] * 50 + 200, localWorld.r[1].m128_f32[2] * 50 + 600), 0xFF00FF00, 2.0f);
				drawList->AddLine(ImVec2(200, 600), ImVec2(localWorld.r[2].m128_f32[1] * 50 + 200, localWorld.r[2].m128_f32[2] * 50 + 600), 0xFFFF0000, 2.0f);

				drawList->AddLine(ImVec2(300, 600), ImVec2(localWorld.r[0].m128_f32[0] * 50 + 300, localWorld.r[0].m128_f32[1] * 50 + 600), 0xFF0000FF, 2.0f);
				drawList->AddLine(ImVec2(300, 600), ImVec2(localWorld.r[1].m128_f32[0] * 50 + 300, localWorld.r[1].m128_f32[1] * 50 + 600), 0xFF00FF00, 2.0f);
				drawList->AddLine(ImVec2(300, 600), ImVec2(localWorld.r[2].m128_f32[0] * 50 + 300, localWorld.r[2].m128_f32[1] * 50 + 600), 0xFFFF0000, 2.0f);
			}

			DirectX::XMMATRIX viewProjMatrix = DirectX::XMMatrixMultiply(maybeView, statProj);//multipication order matters

			for (bodyData body : bodys) {
				physx::PxVec3 localPos = plyPos - body.pos;
				float x = (localPos.x + xoffset) / scale;
				float y = (localPos.y + yoffset) / scale;
				sprintf(buff, "%f", body.mass);
				//ImGui::GetWindowDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2((2560 / 2) + x, (1440 / 2) + y), ImColor(255, 255, 255, 255), buff, 0, 0.0f, 0); //draw text

				//DirectX::XMVECTOR Pos = XMVectorSet(localPos.x, localPos.y, localPos.z, 1.0f);
				DirectX::XMVECTOR Pos = XMVectorSet(localPos.x, localPos.y, localPos.z, 1.0f);

				//normal
				DirectX::XMMATRIX WorldViewProj = viewProjMatrix; //normal

				float mx = Pos.m128_f32[0] * WorldViewProj.r[0].m128_f32[0] + Pos.m128_f32[1] * WorldViewProj.r[1].m128_f32[0] + Pos.m128_f32[2] * WorldViewProj.r[2].m128_f32[0] + WorldViewProj.r[3].m128_f32[0];
				float my = Pos.m128_f32[0] * WorldViewProj.r[0].m128_f32[1] + Pos.m128_f32[1] * WorldViewProj.r[1].m128_f32[1] + Pos.m128_f32[2] * WorldViewProj.r[2].m128_f32[1] + WorldViewProj.r[3].m128_f32[1];
				float mz = Pos.m128_f32[0] * WorldViewProj.r[0].m128_f32[2] + Pos.m128_f32[1] * WorldViewProj.r[1].m128_f32[2] + Pos.m128_f32[2] * WorldViewProj.r[2].m128_f32[2] + WorldViewProj.r[3].m128_f32[2];
				float mw = Pos.m128_f32[0] * WorldViewProj.r[0].m128_f32[3] + Pos.m128_f32[1] * WorldViewProj.r[1].m128_f32[3] + Pos.m128_f32[2] * WorldViewProj.r[2].m128_f32[3] + WorldViewProj.r[3].m128_f32[3];

				float xx, yy;
				xx = ((mx / mw) * (ViewportWidth / 2.0f)) + (ViewportWidth / 2.0f);
				yy = (ViewportHeight / 2.0f) - ((my / mw) * (ViewportHeight / 2.0f)); //- or + depends on the game

				//ImGui::GetWindowDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(2560 - xx,yy), ImColor(255, 255, 255, 255), buff, 0, 0.0f, 0); //draw text
				if (mw > 0.0f) {
					ImGui::GetWindowDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(2560 - xx, 1440 - yy + 15), ImColor(0, 255, 255, 255), buff, 0, 0.0f, 0); //draw text
				}
				//ImGui::GetWindowDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(xx, 1440 - yy), ImColor(255, 0, 255, 255), buff, 0, 0.0f, 0); //draw text
				/*AimEspInfo_t pAimEspInfo = { static_cast<float>(xx), static_cast<float>(yy), static_cast<float>(mw) };
				AimEspInfo.push_back(pAimEspInfo);*/
			}

			uint32_t maxObjects = *(uint32_t*)(objectManager + 0x60068);
			//0x0000'0231'14D4'1EE0
			//0x3c3f'ffff'03fc'9401
			for (uint32_t i = 0; i < maxObjects; i++) {
				//asteroidStruct* object = (*(asteroidStruct***)(objectManager + 0x60060))[i];
				asteroidStruct* object = (asteroidStruct*)((*(uint64_t*)(objectManager + 0x60060) & 0xFFFFFFFFFFFFFFFCui64) + (0x120 * i));
				if ((uint64_t)object < 0x10'0000'0000
				 || (uint64_t)object > 0x1'0000'0000'0000
				 /*|| object->ptr0 < 0x1000'0000
				 || !(object->ptr_data_0_0 & 0xFF) || !(object->ptr_data_0_1 & 0xFF)
				 || object->ptr1 < 0x1000'0000
				 || !(object->ptr_data_1_0 & 0xFF) || !(object->ptr_data_1_1 & 0xFF)
				 || object->ptr2 < 0x1000'0000
				 || !(object->ptr_data_2_0 & 0xFF) || !(object->ptr_data_2_1 & 0xFF)
				 || object->ptr3 < 0x1000'0000
				 || !(object->ptr_data_3_0 & 0xFF) || !(object->ptr_data_3_1 & 0xFF)
				 || object->ptr4 < 0x1000'0000
				 || !(object->ptr_data_4_0 & 0xFF) || !(object->ptr_data_4_1 & 0xFF)
				 || object->ptr5 < 0x1000'0000
				 || !(object->ptr_data_5_0 & 0xFF) || !(object->ptr_data_5_1 & 0xFF)
				 || object->ptr6 < 0x1000'0000
				 || !(object->ptr_data_6_0 & 0xFF) || !(object->ptr_data_6_1 & 0xFF)
				 || object->ptr7 < 0x1000'0000
				 || !(object->ptr_data_7_0 & 0xFF) || !(object->ptr_data_7_1 & 0xFF)
				 || object->ptr8 < 0x1000'0000
				 || !(object->ptr_data_8_0 & 0xFF) || !(object->ptr_data_8_1 & 0xFF)
				 || object->ptr9 < 0x1000'0000
				 || !(object->ptr_data_9_0 & 0xFF) || !(object->ptr_data_9_1 & 0xFF)*/) {
					continue;
				}

				if (!strstr(object->type, "ore")) {
					continue;
				}

				physx::PxVec3 localPos = plyPos - physx::PxVec3{object->x, object->y, object->z};
				float dist = sqrtf((localPos.x * localPos.x) + (localPos.y * localPos.y) + (localPos.z * localPos.z));

				if (asteroidsSubData.size() <= i) {
					asteroidsSubData.resize(i * 1.2f);
				}

				if (dist > 200) {
					AsteroidSubData& subData = asteroidsSubData[i];
					if (subData.ptr != object || subData.subPtr != (void*)object->ptr0) {
						subData.ptr = object;
						subData.maxDist = dist;
						subData.subPtr = (void*)object->ptr0;
					} else if (subData.maxDist < dist) {
						subData.maxDist = dist;
					}

				}

				DirectX::XMVECTOR Pos = XMVectorSet(localPos.x, localPos.y, localPos.z, 1.0f);

				//normal
				DirectX::XMMATRIX WorldViewProj = viewProjMatrix; //normal

				float mx = Pos.m128_f32[0] * WorldViewProj.r[0].m128_f32[0] + Pos.m128_f32[1] * WorldViewProj.r[1].m128_f32[0] + Pos.m128_f32[2] * WorldViewProj.r[2].m128_f32[0] + WorldViewProj.r[3].m128_f32[0];
				float my = Pos.m128_f32[0] * WorldViewProj.r[0].m128_f32[1] + Pos.m128_f32[1] * WorldViewProj.r[1].m128_f32[1] + Pos.m128_f32[2] * WorldViewProj.r[2].m128_f32[1] + WorldViewProj.r[3].m128_f32[1];
				float mz = Pos.m128_f32[0] * WorldViewProj.r[0].m128_f32[2] + Pos.m128_f32[1] * WorldViewProj.r[1].m128_f32[2] + Pos.m128_f32[2] * WorldViewProj.r[2].m128_f32[2] + WorldViewProj.r[3].m128_f32[2];
				float mw = Pos.m128_f32[0] * WorldViewProj.r[0].m128_f32[3] + Pos.m128_f32[1] * WorldViewProj.r[1].m128_f32[3] + Pos.m128_f32[2] * WorldViewProj.r[2].m128_f32[3] + WorldViewProj.r[3].m128_f32[3];

				float xx, yy;
				xx = ((mx / mw) * (ViewportWidth / 2.0f)) + (ViewportWidth / 2.0f);
				yy = (ViewportHeight / 2.0f) - ((my / mw) * (ViewportHeight / 2.0f)); //- or + depends on the game

				if (mw > 0.0f) {
					sprintf(buff, "%s %.0f %0.f", object->type, asteroidsSubData[i].maxDist, dist);
					if (asteroidsSubData[i].ptr == object && asteroidsSubData[i].maxDist > 3300) {
						ImGui::GetWindowDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(2560 - xx, 1440 - yy), ImColor(193, 137, 0, 255), buff, 0, 0.0f, 0);
					} else if (asteroidsSubData[i].ptr == object && asteroidsSubData[i].maxDist > 2700) {
						ImGui::GetWindowDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(2560 - xx, 1440 - yy), ImColor(255, 128, 128, 255), buff, 0, 0.0f, 0);
					} else {
						//ImGui::GetWindowDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(2560 - xx, 1440 - yy), ImColor(0, 255, 255, 255), buff, 0, 0.0f, 0);
					}
				}
			}
		}


		char buff[256];
		if (drawDebugMat) {
			sprintf(buff, "DrawIndexedInstanced %d", DrawIndexedInstanced);
			ImGui::GetWindowDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(20, 350), ImColor(255, 255, 255, 255), buff, 0, 0.0f, 0); //draw text
			sprintf(buff, "Draw %d", Draw);
			ImGui::GetWindowDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(20, 365), ImColor(255, 255, 255, 255), buff, 0, 0.0f, 0); //draw text
			sprintf(buff, "DrawIndexed %d", DrawIndexed);
			ImGui::GetWindowDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(20, 380), ImColor(255, 255, 255, 255), buff, 0, 0.0f, 0); //draw text
			DrawIndexedInstanced = 0;
			Draw = 0;
			DrawIndexed = 0;

			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					sprintf(buff, "%.2f", matWorldView[j][i]);
					ImGui::GetWindowDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(20 + i * 40, 140 + j * 20), ImColor(255, 255, 255, 255), buff, 0, 0.0f, 0); //draw text
				}
			}

			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					sprintf(buff, "%.2f", matProj[j][i]);
					ImGui::GetWindowDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(20 + i * 40, 240 + j * 20), ImColor(255, 255, 255, 255), buff, 0, 0.0f, 0); //draw text
				}
			}

			int indCounter = 0;
			for (int ind : goodView) {
				indCounter++;
				sprintf(buff, "%d", ind);
				ImGui::GetWindowDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(20, 395 + indCounter * 15), ImColor(255, 255, 255, 255), buff, 0, 0.0f, 0); //draw text
			}

			if (AimEspInfo.size() != NULL)
			{
				for (unsigned int i = 0; i < AimEspInfo.size(); i++)
				{
					if (AimEspInfo[i].vOutX > 1 && AimEspInfo[i].vOutY > 1 && AimEspInfo[i].vOutX < ViewportWidth && AimEspInfo[i].vOutY < ViewportHeight)
					{
						//text esp
						ImGui::GetWindowDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(AimEspInfo[i].vOutX, 1440 - AimEspInfo[i].vOutY), ImColor(255, 255, 255, 255), "Model", 0, 0.0f, 0); //draw text
					}
				}
			}
		}
		ImGui::End();
	}

	if (aimkey == 0) Daimkey = VK_SHIFT;
	if (aimkey == 1) Daimkey = VK_RBUTTON;
	if (aimkey == 2) Daimkey = VK_LBUTTON;
	if (aimkey == 3) Daimkey = VK_MBUTTON;
	if (aimkey == 4) Daimkey = VK_CONTROL;
	if (aimkey == 5) Daimkey = VK_MENU;
	if (aimkey == 6) Daimkey = VK_CAPITAL;
	if (aimkey == 7) Daimkey = VK_SPACE;
	if (aimkey == 8) Daimkey = 0x58; //X
	if (aimkey == 9) Daimkey = 0x43; //C
	if (aimkey == 10) Daimkey = 0x56; //V

	//aimbot
	if (aimbot == 1)//aimbot pve, aimbot pvp
		if (AimEspInfo.size() != NULL)
		{
			UINT BestTarget = -1;
			DOUBLE fClosestPos = 99999;

			for (unsigned int i = 0; i < AimEspInfo.size(); i++)
			{
				//aimfov
				float radiusx = (aimfov * 10.0f) * (ScreenCenterX / 100.0f);
				float radiusy = (aimfov * 10.0f) * (ScreenCenterY / 100.0f);

				//get crosshairdistance
				AimEspInfo[i].CrosshairDst = GetDst(AimEspInfo[i].vOutX, AimEspInfo[i].vOutY, ViewportWidth / 2.0f, ViewportHeight / 2.0f);

				//if in fov
				if (AimEspInfo[i].vOutX >= ScreenCenterX - radiusx && AimEspInfo[i].vOutX <= ScreenCenterX + radiusx && AimEspInfo[i].vOutY >= ScreenCenterY - radiusy && AimEspInfo[i].vOutY <= ScreenCenterY + radiusy)

					//get closest/nearest target to crosshair
					if (AimEspInfo[i].CrosshairDst < fClosestPos)
					{
						fClosestPos = AimEspInfo[i].CrosshairDst;
						BestTarget = i;
					}
			}

			//if nearest target to crosshair
			if (BestTarget != -1)
			{
				//double DistX = AimEspInfo[BestTarget].vOutX - ScreenCenterX;
				//double DistY = AimEspInfo[BestTarget].vOutY - ScreenCenterY;

				//DistX /= aimsens * 0.5f;
				//DistY /= aimsens * 0.5f;

				//aim
				//if (GetAsyncKeyState(Daimkey) & 0x8000)
					//mouse_event(MOUSEEVENTF_MOVE, (float)DistX, (float)DistY, 0, NULL);

				//aim
				if (GetAsyncKeyState(Daimkey) & 0x8000)
					AimAtPos(AimEspInfo[BestTarget].vOutX, AimEspInfo[BestTarget].vOutY);

				//get crosshairdistance
				//AimEspInfo[BestTarget].CrosshairDst = GetDst(AimEspInfo[BestTarget].vOutX, AimEspInfo[BestTarget].vOutY, ViewportWidth / 2.0f, ViewportHeight / 2.0f);

				//stabilise aim
				if (aimspeed_isbasedon_distance == 0) //default steady aimsens
					AimSpeed = aimsens;
				else if (aimspeed_isbasedon_distance == 1)
					AimSpeed = aimsens + (AimEspInfo[BestTarget].CrosshairDst * 0.008f); //0.01f the bigger the distance the slower the aimspeed
				else if (aimspeed_isbasedon_distance == 2)
					AimSpeed = aimsens + (AimEspInfo[BestTarget].CrosshairDst * 0.01f); //0.01f the bigger the distance the slower the aimspeed
				else if (aimspeed_isbasedon_distance == 3)
					AimSpeed = aimsens + (AimEspInfo[BestTarget].CrosshairDst * 0.012f); //0.01f the bigger the distance the slower the aimspeed
					//AimSpeed = aimsens + (rand() % 100 / CrosshairDst);     
				else if (aimspeed_isbasedon_distance == 4)
				{
					AimSpeed = aimsens + (75.0f / AimEspInfo[BestTarget].CrosshairDst); //100.0f the bigger the distance the faster the aimspeed
					//AimSpeed = aimsens + (50.0f / CrosshairDst); //50.0f the bigger the distance the faster the aimspeed
					//float randomnb = rand() % 2; //both
					//if (randomnb == 0) AimSpeed = aimsens + (75.0f / CrosshairDst); //the bigger the distance the faster the aimspeed
					//else if (randomnb == 1) AimSpeed = aimsens + (CrosshairDst * 0.01f); //the bigger the distance the slower the aimspeed
				}

				//autoshoot on
				if (autoshoot == 1 && !IsPressed && !GetAsyncKeyState(VK_LBUTTON) && GetAsyncKeyState(Daimkey) & 0x8000 && AimEspInfo[BestTarget].CrosshairDst <= as_xhairdst)//if crosshairdst smaller than as_xhairdist then fire                            
				{
					mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
					IsPressed = true;
				}
			}
		}
	AimEspInfo.clear();

	//autoshoot off
	if ((autoshoot == 1 && IsPressed && !targetfound) || (autoshoot == 1 && IsPressed && !GetAsyncKeyState(Daimkey)))
	{
		IsPressed = false;
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	}


	//ImGui::EndFrame();
	ImGui::Render();
	pContext->OMSetRenderTargets(1, &mainRenderTargetViewD3D11, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	return phookD3D11Present1(pSwapChain, SyncInterval, Flags, pPresentParameters);
}
//==========================================================================================================================


void __stdcall hookD3D11DrawIndexed(ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation)
{
	DrawIndexed++;
	if (IndexCount > 0)
		check_drawindexed_result = 1;

	/*ID3D11Buffer* veBuffer;
	UINT veWidth;
	UINT Stride;
	UINT veBufferOffset;
	D3D11_BUFFER_DESC veDesc;

	//get models
	pContext->IAGetVertexBuffers(0, 1, &veBuffer, &Stride, &veBufferOffset);
	if (veBuffer) {
		veBuffer->GetDesc(&veDesc);
		veWidth = veDesc.ByteWidth;
	}
	if (NULL != veBuffer) {
		veBuffer->Release();
		veBuffer = NULL;
	}

	ID3D11Buffer* pscBuffer;
	UINT pscWidth;
	D3D11_BUFFER_DESC pscdesc;

	//get pscdesc.ByteWidth
	pContext->PSGetConstantBuffers(0, 1, &pscBuffer);
	if (pscBuffer) {
		pscBuffer->GetDesc(&pscdesc);
		pscWidth = pscdesc.ByteWidth;
	}
	if (NULL != pscBuffer) {
		pscBuffer->Release();
		pscBuffer = NULL;
	}

	//wallhack/chams
	if (wallhack == 1 || chams == 1) //if wallhack or chams option is enabled in menu
		if (((modelfindmode == 1) && (countStride == Stride || countIndexCount == IndexCount / 10 || countveWidth == veWidth / 100 || countpscWidth == pscWidth / 1)) ||	//model rec (replace later with logged values) <--
			((modelfindmode == 2) && (countStride == Stride || countIndexCount == IndexCount / 100 || countveWidth == veWidth / 1000 || countpscWidth == pscWidth / 10)) || //model rec (replace later with logged values) <--
			((modelfindmode == 3) && (countStride == Stride || countIndexCount == IndexCount / 1000 || countveWidth == veWidth / 10000 || countpscWidth == pscWidth / 100)))//model rec (replace later with logged values) <--
			
		{
			//get orig
			if (wallhack == 1)
				pContext->OMGetDepthStencilState(&DepthStencilState_ORIG, 0); //get original

			//set off
			if (wallhack == 1)
				pContext->OMSetDepthStencilState(DepthStencilState_FALSE, 0); //depthstencil off

			if (chams == 1)
				pContext->PSSetShader(sGreen, NULL, NULL);
			//pContext->PSSetShaderResources(0, 1, &textureColor); //magenta

			phookD3D11DrawIndexed(pContext, IndexCount, StartIndexLocation, BaseVertexLocation); //redraw

			if (chams == 1)
				pContext->PSSetShader(sMagenta, NULL, NULL);

			//restore orig
			if (wallhack == 1)
				pContext->OMSetDepthStencilState(DepthStencilState_ORIG, 0); //depthstencil on

			//release
			if (wallhack == 1)
				SAFE_RELEASE(DepthStencilState_ORIG); //release
		}

	//esp/aimbot
	if (esp == 1 || aimbot == 1) //if esp/aimbot option is enabled in menu
		if (((modelfindmode == 1) && (countStride == Stride || countIndexCount == IndexCount / 10 || countveWidth == veWidth / 100 || countpscWidth == pscWidth / 1)) ||	//model rec (replace later with logged values) <--
			((modelfindmode == 2) && (countStride == Stride || countIndexCount == IndexCount / 100 || countveWidth == veWidth / 1000 || countpscWidth == pscWidth / 10)) || //model rec (replace later with logged values) <--
			((modelfindmode == 3) && (countStride == Stride || countIndexCount == IndexCount / 1000 || countveWidth == veWidth / 10000 || countpscWidth == pscWidth / 100)))//model rec (replace later with logged values) <--
		{
			AddModel(pContext); //w2s
			targetfound = true;
		}


	//menu logger
	if (modelrecfinder == 1)
	{
		//log selected values
		if (((modelfindmode == 1) && (countStride == Stride || countIndexCount == IndexCount / 10 || countveWidth == veWidth / 100 || countpscWidth == pscWidth / 1)) ||	//model rec (replace later with logged values) <--
			((modelfindmode == 2) && (countStride == Stride || countIndexCount == IndexCount / 100 || countveWidth == veWidth / 1000 || countpscWidth == pscWidth / 10)) || //model rec (replace later with logged values) <--
			((modelfindmode == 3) && (countStride == Stride || countIndexCount == IndexCount / 1000 || countveWidth == veWidth / 10000 || countpscWidth == pscWidth / 100)))//model rec (replace later with logged values) <--
			if (GetAsyncKeyState(VK_END) & 1) //press END to log to log.txt
				Log("Stride == %d && IndexCount == %d && veWidth == %d && pscWidth == %d", Stride, IndexCount, veWidth, pscWidth);

		//highlight selected
		if (((modelfindmode == 1) && (countStride == Stride || countIndexCount == IndexCount / 10 || countveWidth == veWidth / 100 || countpscWidth == pscWidth / 1)) ||	//model rec (replace later with logged values) <--
			((modelfindmode == 2) && (countStride == Stride || countIndexCount == IndexCount / 100 || countveWidth == veWidth / 1000 || countpscWidth == pscWidth / 10)) || //model rec (replace later with logged values) <--
			((modelfindmode == 3) && (countStride == Stride || countIndexCount == IndexCount / 1000 || countveWidth == veWidth / 10000 || countpscWidth == pscWidth / 100)))//model rec (replace later with logged values) <--
		{
			validvscStartSlot = vscStartSlot;

			//pContext->PSSetShader(sGreen, NULL, NULL);
			return; //delete selected texture
		}
	}*/
	
	return phookD3D11DrawIndexed(pContext, IndexCount, StartIndexLocation, BaseVertexLocation);
}

//==========================================================================================================================

void __stdcall hookD3D11DrawIndexedInstanced(ID3D11DeviceContext* pContext, UINT IndexCountPerInstance, UINT InstanceCount, UINT StartIndexLocation, INT BaseVertexLocation, UINT StartInstanceLocation)
{
	if (IndexCountPerInstance > 0)
		check_drawindexedinstanced_result = 1;

	DrawIndexedInstanced++;

	/*ID3D11Buffer* veBuffer;
	UINT veWidth;
	UINT Stride;
	UINT veBufferOffset;
	D3D11_BUFFER_DESC veDesc;

	//get models
	pContext->IAGetVertexBuffers(0, 1, &veBuffer, &Stride, &veBufferOffset);
	if (veBuffer) {
		veBuffer->GetDesc(&veDesc);
		veWidth = veDesc.ByteWidth;
	}
	if (NULL != veBuffer) {
		veBuffer->Release();
		veBuffer = NULL;
	}

	ID3D11Buffer* pscBuffer;
	UINT pscWidth;
	D3D11_BUFFER_DESC pscdesc;

	//get pscdesc.ByteWidth
	pContext->PSGetConstantBuffers(0, 1, &pscBuffer);
	if (pscBuffer) {
		pscBuffer->GetDesc(&pscdesc);
		pscWidth = pscdesc.ByteWidth;
	}
	if (NULL != pscBuffer) {
		pscBuffer->Release();
		pscBuffer = NULL;
	}

	//wallhack/chams
	if (wallhack == 1 || chams == 1) //if wallhack or chams option is enabled in menu
		if (((modelfindmode == 1) && (countStride == Stride || countIndexCount == IndexCountPerInstance / 10 || countveWidth == veWidth / 100 || countpscWidth == pscWidth / 1)) ||	//model rec (replace later with logged values) <--
			((modelfindmode == 2) && (countStride == Stride || countIndexCount == IndexCountPerInstance / 100 || countveWidth == veWidth / 1000 || countpscWidth == pscWidth / 10)) || //model rec (replace later with logged values) <--
			((modelfindmode == 3) && (countStride == Stride || countIndexCount == IndexCountPerInstance / 1000 || countveWidth == veWidth / 10000 || countpscWidth == pscWidth / 100)))//model rec (replace later with logged values) <--
		{
			//get orig
			if (wallhack == 1)
				pContext->OMGetDepthStencilState(&DepthStencilState_ORIG, 0); //get original

			//set off
			if (wallhack == 1)
				pContext->OMSetDepthStencilState(DepthStencilState_FALSE, 0); //depthstencil off

			if (chams == 1)
				pContext->PSSetShader(sGreen, NULL, NULL);
			//pContext->PSSetShaderResources(0, 1, &textureColor); //magenta

			phookD3D11DrawIndexedInstanced(pContext, IndexCountPerInstance, InstanceCount, StartIndexLocation, BaseVertexLocation, StartInstanceLocation); //redraw

			if (chams == 1)
				pContext->PSSetShader(sMagenta, NULL, NULL);

			//restore orig
			if (wallhack == 1)
				pContext->OMSetDepthStencilState(DepthStencilState_ORIG, 0); //depthstencil on

			//release
			if (wallhack == 1)
				SAFE_RELEASE(DepthStencilState_ORIG); //release
		}

	//esp/aimbot
	if (esp == 1 || aimbot == 1) //if esp/aimbot option is enabled in menu
		if (((modelfindmode == 1) && (countStride == Stride || countIndexCount == IndexCountPerInstance / 10 || countveWidth == veWidth / 100 || countpscWidth == pscWidth / 1)) ||	//model rec (replace later with logged values) <--
			((modelfindmode == 2) && (countStride == Stride || countIndexCount == IndexCountPerInstance / 100 || countveWidth == veWidth / 1000 || countpscWidth == pscWidth / 10)) || //model rec (replace later with logged values) <--
			((modelfindmode == 3) && (countStride == Stride || countIndexCount == IndexCountPerInstance / 1000 || countveWidth == veWidth / 10000 || countpscWidth == pscWidth / 100)))//model rec (replace later with logged values) <--
		{
			AddModel(pContext); //w2s
			targetfound = true;
		}


	//menu logger
	if (modelrecfinder == 1)
	{
		//log selected values
		if (((modelfindmode == 1) && (countStride == Stride || countIndexCount == IndexCountPerInstance / 10 || countveWidth == veWidth / 100 || countpscWidth == pscWidth / 1)) ||	//model rec (replace later with logged values) <--
			((modelfindmode == 2) && (countStride == Stride || countIndexCount == IndexCountPerInstance / 100 || countveWidth == veWidth / 1000 || countpscWidth == pscWidth / 10)) || //model rec (replace later with logged values) <--
			((modelfindmode == 3) && (countStride == Stride || countIndexCount == IndexCountPerInstance / 1000 || countveWidth == veWidth / 10000 || countpscWidth == pscWidth / 100)))//model rec (replace later with logged values) <--
			if (GetAsyncKeyState(VK_END) & 1) //press END to log to log.txt
				Log("Stride == %d && IndexCount == %d && veWidth == %d && pscWidth == %d", Stride, IndexCountPerInstance, veWidth, pscWidth);

		//highlight selected
		if (((modelfindmode == 1) && (countStride == Stride || countIndexCount == IndexCountPerInstance / 10 || countveWidth == veWidth / 100 || countpscWidth == pscWidth / 1)) ||	//model rec (replace later with logged values) <--
			((modelfindmode == 2) && (countStride == Stride || countIndexCount == IndexCountPerInstance / 100 || countveWidth == veWidth / 1000 || countpscWidth == pscWidth / 10)) || //model rec (replace later with logged values) <--
			((modelfindmode == 3) && (countStride == Stride || countIndexCount == IndexCountPerInstance / 1000 || countveWidth == veWidth / 10000 || countpscWidth == pscWidth / 100)))//model rec (replace later with logged values) <--
		{
			validvscStartSlot = vscStartSlot;

			//pContext->PSSetShader(sGreen, NULL, NULL);
			return; //delete selected texture
		}
	}*/

	return phookD3D11DrawIndexedInstanced(pContext, IndexCountPerInstance, InstanceCount, StartIndexLocation, BaseVertexLocation, StartInstanceLocation);
}

//==========================================================================================================================

void __stdcall hookD3D11Draw(ID3D11DeviceContext* pContext, UINT VertexCount, UINT StartVertexLocation)
{
	if (VertexCount > 0)
		check_draw_result = 1;

	Draw++;

	DrawIndexedInstanced++;

	ID3D11Buffer* veBuffer;
	UINT veWidth;
	UINT Stride;
	UINT veBufferOffset;
	D3D11_BUFFER_DESC veDesc;

	//get models
	pContext->IAGetVertexBuffers(0, 1, &veBuffer, &Stride, &veBufferOffset);
	if (veBuffer) {
		veBuffer->GetDesc(&veDesc);
		veWidth = veDesc.ByteWidth;
	}
	if (NULL != veBuffer) {
		veBuffer->Release();
		veBuffer = NULL;
	}

	ID3D11Buffer* pscBuffer;
	UINT pscWidth = -1;
	D3D11_BUFFER_DESC pscdesc;

	//get pscdesc.ByteWidth
	pContext->PSGetConstantBuffers(0, 1, &pscBuffer);
	if (pscBuffer) {
		pscBuffer->GetDesc(&pscdesc);
		pscWidth = pscdesc.ByteWidth;
	}
	if (NULL != pscBuffer) {
		pscBuffer->Release();
		pscBuffer = NULL;
	}

	if (initonce && veWidth / 100 == 24) {
		ID3D11Buffer* pWorldViewCB;
		pContext->VSGetConstantBuffers(0, 1, &pWorldViewCB);
		ID3D11Buffer* m_pCurWorldViewCB = NULL;
		m_pCurWorldViewCB = CopyBufferToCpuA(pWorldViewCB);

		float* worldviewPtr;
		MapBuffer(m_pCurWorldViewCB, (void**)&worldviewPtr, NULL);
		memcpy(worldView, &worldviewPtr[0], sizeof(worldView));
		UnmapBuffer(m_pCurWorldViewCB);
	}

	//wallhack/chams
	if (wallhack == 1 || chams == 1) //if wallhack or chams option is enabled in menu
		if (((modelfindmode == 1) && (countStride == Stride || countIndexCount == VertexCount / 10 || countveWidth == veWidth / 100 || countpscWidth == pscWidth / 1)) ||	//model rec (replace later with logged values) <--
			((modelfindmode == 2) && (countStride == Stride || countIndexCount == VertexCount / 100 || countveWidth == veWidth / 1000 || countpscWidth == pscWidth / 10)) || //model rec (replace later with logged values) <--
			((modelfindmode == 3) && (countStride == Stride || countIndexCount == VertexCount / 1000 || countveWidth == veWidth / 10000 || countpscWidth == pscWidth / 100)))//model rec (replace later with logged values) <--
			/*
			//unreal4 models
			if ((Stride == 32 && IndexCount == 10155) ||
				(Stride == 44 && IndexCount == 11097) ||
				(Stride == 40 && IndexCount == 11412) ||
				(Stride == 40 && IndexCount == 11487) ||
				(Stride == 44 && IndexCount == 83262) ||
				(Stride == 40 && IndexCount == 23283))
			*/
		{
			//get orig
			if (wallhack == 1)
				pContext->OMGetDepthStencilState(&DepthStencilState_ORIG, 0); //get original

			//set off
			if (wallhack == 1)
				pContext->OMSetDepthStencilState(DepthStencilState_FALSE, 0); //depthstencil off

			if (chams == 1)
				pContext->PSSetShader(sGreen, NULL, NULL);
			//pContext->PSSetShaderResources(0, 1, &textureColor); //magenta

			phookD3D11Draw(pContext, VertexCount, StartVertexLocation); //redraw

			if (chams == 1)
				pContext->PSSetShader(sMagenta, NULL, NULL);

			//restore orig
			if (wallhack == 1)
				pContext->OMSetDepthStencilState(DepthStencilState_ORIG, 0); //depthstencil on

			//release
			if (wallhack == 1)
				SAFE_RELEASE(DepthStencilState_ORIG); //release
		}

	//esp/aimbot
	if (esp == 1 || aimbot == 1) //if esp/aimbot option is enabled in menu
		if (((modelfindmode == 1) && (countStride == Stride || countIndexCount == VertexCount / 10 || countveWidth == veWidth / 100 || countpscWidth == pscWidth / 1)) ||	//model rec (replace later with logged values) <--
			((modelfindmode == 2) && (countStride == Stride || countIndexCount == VertexCount / 100 || countveWidth == veWidth / 1000 || countpscWidth == pscWidth / 10)) || //model rec (replace later with logged values) <--
			((modelfindmode == 3) && (countStride == Stride || countIndexCount == VertexCount / 1000 || countveWidth == veWidth / 10000 || countpscWidth == pscWidth / 100)))//model rec (replace later with logged values) <--
			/*
			//unreal4 models
			if ((Stride == 32 && IndexCount == 10155) ||
				(Stride == 44 && IndexCount == 11097) ||
				(Stride == 40 && IndexCount == 11412) ||
				(Stride == 40 && IndexCount == 11487) ||
				(Stride == 44 && IndexCount == 83262) ||
				(Stride == 40 && IndexCount == 23283))
			*/
		{
			AddModel(pContext); //w2s
			targetfound = true;
		}


	//menu logger
	if (modelrecfinder == 1)
	{
		//log selected values
		if (((modelfindmode == 1) && (countStride == Stride || countIndexCount == VertexCount / 10 || countveWidth == veWidth / 100 || countpscWidth == pscWidth / 1)) ||	//model rec (replace later with logged values) <--
			((modelfindmode == 2) && (countStride == Stride || countIndexCount == VertexCount / 100 || countveWidth == veWidth / 1000 || countpscWidth == pscWidth / 10)) || //model rec (replace later with logged values) <--
			((modelfindmode == 3) && (countStride == Stride || countIndexCount == VertexCount / 1000 || countveWidth == veWidth / 10000 || countpscWidth == pscWidth / 100)))//model rec (replace later with logged values) <--
			if (GetAsyncKeyState(VK_END) & 1) //press END to log to log.txt
				Log("Stride == %d && IndexCount == %d && veWidth == %d && pscWidth == %d", Stride, VertexCount, veWidth, pscWidth);

		//highlight selected
		if (((modelfindmode == 1) && (countStride == Stride || countIndexCount == VertexCount / 10 || countveWidth == veWidth / 100 || countpscWidth == pscWidth / 1)) ||	//model rec (replace later with logged values) <--
			((modelfindmode == 2) && (countStride == Stride || countIndexCount == VertexCount / 100 || countveWidth == veWidth / 1000 || countpscWidth == pscWidth / 10)) || //model rec (replace later with logged values) <--
			((modelfindmode == 3) && (countStride == Stride || countIndexCount == VertexCount / 1000 || countveWidth == veWidth / 10000 || countpscWidth == pscWidth / 100)))//model rec (replace later with logged values) <--
		{
			validvscStartSlot = vscStartSlot;

			//pContext->PSSetShader(sGreen, NULL, NULL);
			return; //delete selected texture
		}
	}

	return phookD3D11Draw(pContext, VertexCount, StartVertexLocation);
}

//==========================================================================================================================

void __stdcall hookD3D11PSSetShaderResources(ID3D11DeviceContext* pContext, UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews)
{
	//pssrStartSlot = StartSlot;

	/*
	//texture stuff usually not needed
	for (UINT j = 0; j < NumViews; j++)
	{
		//resources loop
		ID3D11ShaderResourceView* pShaderResView = ppShaderResourceViews[j];
		if (pShaderResView)
		{
			pShaderResView->GetDesc(&Descr);

			ID3D11Resource* Resource;
			pShaderResView->GetResource(&Resource);
			ID3D11Texture2D* Texture = (ID3D11Texture2D*)Resource;
			Texture->GetDesc(&texdesc);

			SAFE_RELEASE(Resource);
			SAFE_RELEASE(Texture);
		}
	}
	*/
	return phookD3D11PSSetShaderResources(pContext, StartSlot, NumViews, ppShaderResourceViews);
}

//==========================================================================================================================

void __stdcall hookD3D11VSSetConstantBuffers(ID3D11DeviceContext* pContext, UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers)
{
	//can tell us WorldViewCBnum & ProjCBnum
	vscStartSlot = StartSlot;

	return phookD3D11VSSetConstantBuffers(pContext, StartSlot, NumBuffers, ppConstantBuffers);
}

//==========================================================================================================================

static HRESULT(WINAPI* d3d11_CreatePixelShader)(ID3D11Device*, const void*, SIZE_T, ID3D11ClassLinkage*, ID3D11PixelShader**);
static HRESULT(WINAPI* d3d11_CreateVertexShader)(ID3D11Device*, const void*, SIZE_T, ID3D11ClassLinkage*, ID3D11VertexShader**);
static HRESULT(WINAPI* d3d11_CreateComputeShader)(ID3D11Device*, const void*, SIZE_T, ID3D11ClassLinkage*, ID3D11ComputeShader**);
static HRESULT(WINAPI* d3d11_CreateHullShader)(ID3D11Device*, const void*, SIZE_T, ID3D11ClassLinkage*, ID3D11HullShader**);
static HRESULT(WINAPI* d3d11_CreateDomainShader)(ID3D11Device*, const void*, SIZE_T, ID3D11ClassLinkage*, ID3D11DomainShader**);
static HRESULT(WINAPI* d3d11_CreateGeometryShader)(ID3D11Device*, const void*, SIZE_T, ID3D11ClassLinkage*, ID3D11GeometryShader**);
static HRESULT(WINAPI* d3d11_CreateGeometryShaderWithStreamOutput)(ID3D11Device*, const void*, SIZE_T, const D3D11_SO_DECLARATION_ENTRY*, UINT, const UINT*, UINT, UINT, ID3D11ClassLinkage*, ID3D11GeometryShader**);


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

//==========================================================================================================================


const int MultisampleCount = 1;

CreateSwapChainForHwnd_type or_CreateSwapChainForHwnd;

HRESULT STDMETHODCALLTYPE CreateSwapChainForHwnd_hook(
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
    _COM_Outptr_  IDXGISwapChain1** ppSwapChain) 
{
	HRESULT result = FnCast("CreateSwapChainForHwnd", or_CreateSwapChainForHwnd)(This, pDevice, hWnd, pDesc, pFullscreenDesc, pRestrictToOutput, ppSwapChain);

	pSwapChainVtable = (DWORD_PTR*)dynamic_cast<IDXGISwapChain*>(*ppSwapChain);
	pSwapChainVtable = (DWORD_PTR*)pSwapChainVtable[0];

	pDevice->GetImmediateContext((ID3D11DeviceContext**)&pContextVTable);
	pContextVTable = (DWORD_PTR*)pContextVTable[0];

	pDeviceVTable = (DWORD_PTR*)pDevice;
	pDeviceVTable = (DWORD_PTR*)pDeviceVTable[0];
	//pDevice->shader

	MH_Initialize();
	//if (status != MH_OK) { MessageBoxA(nullptr, "MH_Initialize", "MH_Initialize", MB_OK); }
	// if (MH_CreateHook((DWORD_PTR*)pSwapChainVtable[8], hookD3D11Present, reinterpret_cast<void**>(&phookD3D11Present)) != MH_OK) { MessageBoxA(nullptr, "hookD3D11Present", "hookD3D11Present", MB_OK); }
	// if (MH_EnableHook((DWORD_PTR*)pSwapChainVtable[8]) != MH_OK) { MessageBoxA(nullptr, "hookD3D11Present", "hookD3D11Present", MB_OK); }
	if (MH_CreateHook((DWORD_PTR*)pSwapChainVtable[22], hookD3D11Present1, reinterpret_cast<void**>(&phookD3D11Present1)) != MH_OK) { MessageBoxA(nullptr, "hookD3D11Present1", "hookD3D11Present1", MB_OK); }
	if (MH_EnableHook((DWORD_PTR*)pSwapChainVtable[22]) != MH_OK) { MessageBoxA(nullptr, "hookD3D11Present1", "hookD3D11Present1", MB_OK); }
	// if (MH_CreateHook((DWORD_PTR*)pSwapChainVtable[13], hookD3D11ResizeBuffers, reinterpret_cast<void**>(&phookD3D11ResizeBuffers)) != MH_OK) { MessageBoxA(nullptr, "hookD3D11ResizeBuffers", "hookD3D11ResizeBuffers", MB_OK); }
	// if (MH_EnableHook((DWORD_PTR*)pSwapChainVtable[13]) != MH_OK) { MessageBoxA(nullptr, "hookD3D11ResizeBuffers", "hookD3D11ResizeBuffers", MB_OK); }

	//MessageBoxA(nullptr, "Present", "Present", MB_OK);
	//(*ppSwapChain)->Present(1,2); // 8
	//(*ppSwapChain)->Present1(1, 2, nullptr); // 22

	// if (MH_CreateHook((DWORD_PTR*)pContextVTable[12], hookD3D11DrawIndexed, reinterpret_cast<void**>(&phookD3D11DrawIndexed)) != MH_OK) { MessageBoxA(nullptr, "A", "B", MB_OK); }
	// if (MH_EnableHook((DWORD_PTR*)pContextVTable[12]) != MH_OK) { MessageBoxA(nullptr, "A", "B", MB_OK); }
	// if (MH_CreateHook((DWORD_PTR*)pContextVTable[20], hookD3D11DrawIndexedInstanced, reinterpret_cast<void**>(&phookD3D11DrawIndexedInstanced)) != MH_OK) { MessageBoxA(nullptr, "A", "B", MB_OK); }
	// if (MH_EnableHook((DWORD_PTR*)pContextVTable[20]) != MH_OK) { MessageBoxA(nullptr, "A", "B", MB_OK); }
	if (MH_CreateHook((DWORD_PTR*)pContextVTable[13], hookD3D11Draw, reinterpret_cast<void**>(&phookD3D11Draw)) != MH_OK) { MessageBoxA(nullptr, "A", "B", MB_OK); }
	if (MH_EnableHook((DWORD_PTR*)pContextVTable[13]) != MH_OK) { MessageBoxA(nullptr, "A", "B", MB_OK); }
	//DrawInstanced
	//DrawInstancedIndirect
	//DrawIndexedInstancedIndirect

	//if (MH_CreateHook((DWORD_PTR*)pContextVTable[8], hookD3D11PSSetShaderResources, reinterpret_cast<void**>(&phookD3D11PSSetShaderResources)) != MH_OK) { return 1; }
	//if (MH_EnableHook((DWORD_PTR*)pContextVTable[8]) != MH_OK) { return 1; }
	// if (MH_CreateHook((DWORD_PTR*)pContextVTable[7], hookD3D11VSSetConstantBuffers, reinterpret_cast<void**>(&phookD3D11VSSetConstantBuffers)) != MH_OK) { MessageBoxA(nullptr, "hookD3D11VSSetConstantBuffers", "hookD3D11VSSetConstantBuffers", MB_OK); }
	// if (MH_EnableHook((DWORD_PTR*)pContextVTable[7]) != MH_OK) { MessageBoxA(nullptr, "hookD3D11VSSetConstantBuffers", "hookD3D11VSSetConstantBuffers", MB_OK); }

	//dump shader
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


	DWORD dwOld;
	VirtualProtect(phookD3D11Present, 2, PAGE_EXECUTE_READWRITE, &dwOld);

	fprintf(Con::fpout, "CreateSwapChainForHwnd_hook work\n");
	fflush(Con::fpout);

	return result;
}

void initDxHook()
{
	HMODULE d3d11 = LoadLibraryA("d3d11.dll");
	or_D3D11CreateDeviceAndSwapChain = (D3D11CreateDeviceAndSwapChain_type)GetProcAddress(d3d11, "D3D11CreateDeviceAndSwapChain");
	or_D3D11CreateDevice = (D3D11CreateDevice_type)GetProcAddress(d3d11, "D3D11CreateDevice");
	
	HMODULE gameOverlayRenderer = LoadLibraryA("GameOverlayRenderer64.dll");

	const char* CreateSwapChainForHwnd_pattern = "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 56 48 83 EC 40 48 8B F1 49 8B D9 48 8D 0D ? ? ? ? 49 8B F8 4C 8B F2 E8 ? ? ? ? 48 8B 44 24";
	or_CreateSwapChainForHwnd = findSignature<CreateSwapChainForHwnd_type>((unsigned char*)gameOverlayRenderer, CreateSwapChainForHwnd_pattern);
	placeHook("CreateSwapChainForHwnd", or_CreateSwapChainForHwnd, CreateSwapChainForHwnd_hook);

	//CreateSwapChainForHwnd;
	//placeHook("D3D11CreateDevice", or_D3D11CreateDevice, D3D11CreateDevice_hook);
}
