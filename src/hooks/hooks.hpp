#pragma once
#include <Windows.h>
#include <iostream>
#include <d3d11.h>
#include "../../../../../../../Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include/D3DX11core.h"

namespace hooks {

    void Initialize();
    void Shutdown();

}  // namespace hooks
typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
static uint64_t* g_methodsTable = 0;
D3DX11_IMAGE_LOAD_INFO iInfo;
ID3DX11ThreadPump* threadPump{ nullptr };
ID3D11ShaderResourceView* logo = nullptr;
namespace DirectX
{
	bool OverlayHooked = false;
	Present OriginalPresent = 0;
	HWND Window = 0;
	WNDPROC WindowEx = 0;
	ID3D11Device* pDevice = 0;
	ID3D11DeviceContext* pContext = 0;
	ID3D11RenderTargetView* renderTargetView = 0;


	


	DWORD_PTR swapchain_backup = 0x0;
	uintptr_t* swapchain_vtables{ 0 };
	DWORD dwOld = 0x0;
}