#pragma once

#include <thread>

#include "hooks.hpp"
#include "../api/hook/hook.hpp"

#include "graphics/input/wndproc_hook.cpp"
#include "graphics/directx/directx11_hook.cpp"
#include <src/fivem/classes/classes.hpp>
#include <src/menu/bytes.hpp>
#include <src/minhook/MinHook.h>
#include <font_awesome.hpp>
#include "C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\D3DX11.h"
#include <src/fivem/native/invoker.hpp>
#include "../../scroupthick.hpp"
#pragma comment (lib, "d3dx11.lib")

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void InitImGui()
{
	using namespace DirectX;

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;

	ImFontConfig font_config;
	font_config.PixelSnapH = false;
	font_config.FontDataOwnedByAtlas = false;
	font_config.OversampleH = 5;
	font_config.OversampleV = 5;
	font_config.RasterizerMultiply = 1.2f;

	static const ImWchar ranges[] = {
		0x0020, 0x00FF, // Basic Latin + Latin Supplement
		0x0400, 0x052F, // Cyrillic + Cyrillic Supplement
		0x2DE0, 0x2DFF, // Cyrillic Extended-A
		0xA640, 0xA69F, // Cyrillic Extended-B
		0xE000, 0xE226, // icons
		0,
	};

	font_config.GlyphRanges = ranges;
	static const ImWchar icons_rangess[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
	ImFontConfig icons_configg;
	icons_configg.MergeMode = true;
	icons_configg.PixelSnapH = true;
	io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\tahoma.ttf", 14, &font_config, ranges);
	io.Fonts->AddFontFromMemoryTTF(icons_binary, sizeof icons_binary, 15, &font_config, ranges);
	io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 15, &icons_configg, icons_rangess);


	ImGuiStyle* Style = &ImGui::GetStyle();
	ImVec4* Colors = Style->Colors;
	Colors[ImGuiCol_FrameBg] = ImVec4(ImColor(24, 25, 31));
	Colors[ImGuiCol_FrameBgHovered] = ImVec4(ImColor(24, 25, 31));
	Colors[ImGuiCol_FrameBgActive] = ImVec4(ImColor(24, 25, 31));
	// Our state
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	ImGui_ImplWin32_Init(Window);
	ImGui_ImplDX11_Init(pDevice, pContext);
	D3DX11CreateShaderResourceViewFromMemory(DirectX::pDevice, aspera, sizeof(aspera), &iInfo, threadPump, &logo/*shader*/, 0);

	//Snowflake::CreateSnowFlakes(snow, SNOW_LIMIT, 5.f/*minimum size*/, 25.f/*maximum size*/, 0/*imgui window x position*/, 0/*imgui window y position*/, WINDOW_WIDTH, WINDOW_HEIGHT, Snowflake::vec3(0.f, 0.005f)/*gravity*/, IM_COL32(255,255, 255, 100)/*color*/);

}

LRESULT __stdcall WindowHandler(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (menu::show_menu)
	{
		ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
		return true;
	}

	return SAFE_CALL(CallWindowProcA)(DirectX::WindowEx, hWnd, uMsg, wParam, lParam);
}

bool iniit = true;
bool BindD3DInfo(IDXGISwapChain* pSwapChain)
{
	if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&DirectX::pDevice)))
	{
		DirectX::pDevice->GetImmediateContext(&DirectX::pContext);
		DXGI_SWAP_CHAIN_DESC sd;

		pSwapChain->GetDesc(&sd);
		DirectX::Window = sd.OutputWindow;


		ID3D11Texture2D* pBackBuffer;

		pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
		DirectX::pDevice->CreateRenderTargetView(pBackBuffer, 0, &DirectX::renderTargetView);
		pBackBuffer->Release();

		DirectX::WindowEx = (WNDPROC)LI_FN(SetWindowLongPtrA).safe_cached()(DirectX::Window, GWLP_WNDPROC, (LONG_PTR)WindowHandler);

		InitImGui();

		iniit = false;


		return true;
	}

	return false;
}
HRESULT __stdcall PresentHook(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (iniit)
	{
		//KeyAuthApp.init();
		if (!BindD3DInfo(pSwapChain))
			return DirectX::OriginalPresent(pSwapChain, SyncInterval, Flags);
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	menu::render_menu();

	ImGui::Render();

	DirectX::pContext->OMSetRenderTargets(1, &DirectX::renderTargetView, 0);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	return DirectX::OriginalPresent( pSwapChain, SyncInterval, Flags);
}

bool SwapPresentVtab()
{
	//std::uint64_t ragee_base = (uint64_t)GetModuleHandleA(E("rage-graphics-five.dll"));
	//fivem::swapchain = ragee_base + 0x29886;

	DirectX::swapchain_vtables = *(DWORD_PTR**)(fivem::swapchain);
	DirectX::swapchain_vtables = (DWORD_PTR*)(DirectX::swapchain_vtables[0]);
	DirectX::swapchain_backup = DirectX::swapchain_vtables[8];
	SAFE_CALL(VirtualProtect)((LPVOID)DirectX::swapchain_vtables, sizeof(DWORD_PTR), (DWORD)PAGE_EXECUTE_READWRITE, (PDWORD)&DirectX::dwOld);
	DirectX::OriginalPresent = reinterpret_cast<Present>(DirectX::swapchain_vtables[8]);
	DirectX::swapchain_vtables[8] = (uintptr_t)&PresentHook;
	SAFE_CALL(VirtualProtect)((LPVOID)DirectX::swapchain_vtables, sizeof(DWORD_PTR), (DWORD)DirectX::dwOld, (PDWORD)&DirectX::dwOld);
	return true;
}
fivem::write_player_game_state_data_node Orin_write_player_game_state_data_node = nullptr;
void HK_write_player_game_state_data_node(uintptr_t* player, CPlayerGameStateDataNode* node)
{
	//Log::Msg("before call original m_is_invincible: %d", node->m_is_invincible);
	bool Successed = Orin_write_player_game_state_data_node(player, node);

	node->m_is_invincible = false;
	node->m_bullet_proof = false;
	node->m_collision_proof = false;
	node->m_explosion_proof = false;
	node->m_fire_proof = false;
	node->m_melee_proof = false;
	node->m_steam_proof = false;
	node->m_water_proof = false;
	node->m_is_spectating = false;
	node->m_spectating_net_id = 0;
	
}

bool HookDataNodes()
{
	MH_Initialize();
	if (MH_CreateHook(fivem::Target_write_player_game_state_data_node, HK_write_player_game_state_data_node, (void**)&Orin_write_player_game_state_data_node) != MH_OK
		|| MH_EnableHook(fivem::Target_write_player_game_state_data_node) != MH_OK)
	{
		return false;
	}
	return true;
}
void FindOffset() {
	std::uint64_t rage_base = (uint64_t)GetModuleHandleA(E("rage-scripting-five.dll"));
	orin_fastPathMap = reinterpret_cast<g_fastPathMap_t*>((rage_base + 0x313460));
	ScanMap();
	g_mappingTable = *(g_mappingTable_t*)(rage_base + 0x3132f0);
	GetNativeHandlerDo_Old = (decltype(GetNativeHandlerDo_Old)(rage_base + 0x1357c0));
	GetNativeHandlerDo_Obfuscated = (decltype(GetNativeHandlerDo_Obfuscated)(rage_base + 0x134410));

	//orin_fastPathMap = reinterpret_cast<g_fastPathMap_t*>(Memory::PatternScanNewEx(rage_base, E("48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8B 08 48 89 59 ? 4C 8B 4C 24"), NULL, 7));
	//g_mappingTable = *(g_mappingTable_t*)(Memory::PatternScanNewEx(rage_base, E("48 8D 0D ? ? ? ? E8 ? ? ? ? 41 8B 06"), NULL, 7));

	//GetNativeHandlerDo_Old = (decltype(GetNativeHandlerDo_Old))(Memory::PatternScanEx(rage_base, E("40 55 56 57 48 83 EC"), NULL));
	//GetNativeHandlerDo_Obfuscated = (decltype(GetNativeHandlerDo_Obfuscated))(Memory::PatternScanEx(rage_base, E("4C 8B DC 55 56 57 41 57"), NULL));
	std::uint64_t Gtabase = (uint64_t)GetModuleHandleA(nullptr);

	if (SAFE_CALL(GetModuleHandleA)(E("FiveM_b2944_GameProcess.exe")) || SAFE_CALL(GetModuleHandleA)(E("FiveM_b2944_GTAProcess.exe")))
	{
		fivem::World = (Gtabase + 0x257BEA0);
		fivem::ViewPort = (Gtabase + (0x1FEAAC0));
		fivem::ReplayInterface = (Gtabase + 0x1F42068);
		fivem::Camera = (Gtabase + 0x1FEB968);
		fivem::swapchain = (Gtabase + 0x2CAA600);
		fivem::dwThreadCollectionPtr = (Gtabase + 0x1A9D618);
		fivem::g_OrigScriptThreads = reinterpret_cast<fivem::RunScriptThreads_t>(Gtabase + 0xA52334);
		fivem::modelspawnbypass = (void*)(Gtabase + 0xA421CA);

		fivem::is2944 = true;
		fivem::pointer_to_handle = reinterpret_cast<fivem::pizza_to_spaghetti_t>(Gtabase + 0x160FF90);
	}
	if (SAFE_CALL(GetModuleHandleA)(E("FiveM_b2802_GameProcess.exe")) || SAFE_CALL(GetModuleHandleA)(E("FiveM_b2802_GTAProcess.exe")))
	{
		fivem::World = (Gtabase + 0x254D448);
		fivem::ViewPort = (Gtabase + 0x1FBC100);
		fivem::ReplayInterface = (Gtabase + 0x1F5B820);
		fivem::Camera = (Gtabase + 0x1FBCCD8);
		fivem::swapchain = (Gtabase + 0x2C6B100);
		fivem::dwThreadCollectionPtr = (Gtabase + 0x1A73CD0);
		fivem::modelspawnbypass = (void*)(Gtabase + 0xA40C76);

	//	fivem::g_OrigScriptThreads = reinterpret_cast<fivem::RunScriptThreads_t>(Gtabase + 0xA50C8C);
		fivem::FiveM_2802 = true;
		fivem::pointer_to_handle = reinterpret_cast<fivem::pizza_to_spaghetti_t>(Gtabase + 0x15EA290);

	}

	if (SAFE_CALL(GetModuleHandleA)("FiveM_b2699_GTAProcess.exe") || SAFE_CALL(GetModuleHandleA)("FiveM_b2699_GameProcess.exe"))
	{
		fivem::World = (Gtabase + 0x26684D8);
		fivem::ViewPort = (Gtabase + 0x20D8C90);
		fivem::ReplayInterface = (Gtabase + 0x20304C8);
		fivem::Camera = (Gtabase + 0x20D9868);
		fivem::swapchain = (Gtabase + 0x2D38D88);
		fivem::dwThreadCollectionPtr = (Gtabase + 0x1A58E38);
		//fivem::g_OrigScriptThreads = reinterpret_cast<fivem::RunScriptThreads_t>(Gtabase + 0xA4A810);
		fivem::modelspawnbypass = (void*)(Gtabase + 0xA3A736);

		fivem::pointer_to_handle = reinterpret_cast<fivem::pizza_to_spaghetti_t>(Gtabase + 0x15D6CEC);



	}
	if (SAFE_CALL(GetModuleHandleA)(E("Fivem_b2612_GameProcess.exe")) || SAFE_CALL(GetModuleHandleA)(E("FiveM_b2612_GTAProcess.exe")))
	{
		fivem::World = (Gtabase + 0x2567DB0);
		fivem::ViewPort = (Gtabase + 0x1FD8570);
		fivem::ReplayInterface = (Gtabase + 0x1F77EF0);
		fivem::Camera = (Gtabase + 0x1FD9148);
		fivem::swapchain = (Gtabase + 0x2BCB7D0);
		fivem::dwThreadCollectionPtr = (Gtabase + 0x19DEF40);
		fivem::modelspawnbypass = (void*)(Gtabase + 0xA37192);

	//	fivem::g_OrigScriptThreads = reinterpret_cast<fivem::RunScriptThreads_t>(Gtabase + 0xA471AC);
		fivem::is2612 = true;
		fivem::pointer_to_handle = reinterpret_cast<fivem::pizza_to_spaghetti_t>(Gtabase + 0x15DFE20);

	}
	if (SAFE_CALL(GetModuleHandleA)(E("Fivem_b2545_GameProcess.exe")) || SAFE_CALL(GetModuleHandleA)(E("Fivem_b2545_GTAProcess.exe")))
	{
		fivem::World = (Gtabase + 0x25667E8);
		fivem::ViewPort = (Gtabase + 0x1FD6F70);
		fivem::ReplayInterface = (Gtabase + 0x1F2E7A8);
		fivem::Camera = (Gtabase + 0x1FD7B48);
		fivem::swapchain = (Gtabase + 0x2BCA050);
		fivem::dwThreadCollectionPtr = (Gtabase + 0x19DDE90);
	//	fivem::g_OrigScriptThreads = reinterpret_cast<fivem::RunScriptThreads_t>(Gtabase + 0xA46B28);
		fivem::modelspawnbypass = (void*)(Gtabase + 0xA36A6A);

		fivem::pointer_to_handle = reinterpret_cast<fivem::pizza_to_spaghetti_t>(Gtabase + 0x15DEEB0);

	}
	if (SAFE_CALL(GetModuleHandleA)(E("Fivem_b2372_GameProcess.exe")) || SAFE_CALL(GetModuleHandleA)(E("Fivem_b2372_GTAProcess.exe")))
	{
		fivem::World = (Gtabase + 0x252DCD8);
		fivem::ViewPort = (Gtabase + 0x1F9E9F0);
		fivem::ReplayInterface = (Gtabase + 0x1F05208);
		fivem::Camera = (Gtabase + 0x1F9F5C8);
		fivem::swapchain = (Gtabase + 0x2B8F708);
		fivem::dwThreadCollectionPtr = (Gtabase + 0x19BC5D8);
	//	fivem::g_OrigScriptThreads = reinterpret_cast<fivem::RunScriptThreads_t>(Gtabase + 0xA41778);
		fivem::modelspawnbypass = (void*)(Gtabase + 0xA317DE);

		fivem::pointer_to_handle = reinterpret_cast<fivem::pizza_to_spaghetti_t>(Gtabase + 0x15CD2C0);

	}
	if (SAFE_CALL(GetModuleHandleA)(E("Fivem_b2189_GameProcess.exe")) || SAFE_CALL(GetModuleHandleA)(E("Fivem_b2189_GTAProcess.exe")))
	{
		fivem::World = (Gtabase + 0x24E6D90);
		fivem::ViewPort = (Gtabase + 0x1F888C0);
		fivem::ReplayInterface = (Gtabase + 0x1EE18A8);
		fivem::Camera = (Gtabase + 0x1F89498);
		fivem::swapchain = (Gtabase + 0x2B580C0);
		fivem::dwThreadCollectionPtr = (Gtabase + 0x199BCE0);
	//	fivem::g_OrigScriptThreads = reinterpret_cast<fivem::RunScriptThreads_t>(Gtabase + 0xA3E2F4);
		fivem::is2189 = true;
		fivem::modelspawnbypass = (void*)(Gtabase + 0xA2E89E);

		fivem::pointer_to_handle = reinterpret_cast<fivem::pizza_to_spaghetti_t>(Gtabase + 0x15B1008);

	}

	if (SAFE_CALL(GetModuleHandleA)(E("Fivem_b2060_GameProcess.exe")) || SAFE_CALL(GetModuleHandleA)(E("Fivem_b2060_GTAProcess.exe")))
	{
		fivem::World = (Gtabase + 0x24C8858);
		fivem::ViewPort = (Gtabase + 0x1F6A7E0);
		fivem::ReplayInterface = (Gtabase + 0x1EC3828);
		fivem::Camera = (Gtabase + 0x1F6B3C0);
		fivem::swapchain = (Gtabase + 0x2B2C9C0);
		fivem::dwThreadCollectionPtr = (Gtabase + 0x1983758);
	//	fivem::g_OrigScriptThreads = reinterpret_cast<fivem::RunScriptThreads_t>(Gtabase + 0xA344E0);
		fivem::is2060 = true;
		fivem::modelspawnbypass = (void*)(Gtabase + 0xA2490E);

		fivem::pointer_to_handle = reinterpret_cast<fivem::pizza_to_spaghetti_t>(Gtabase + 0x159B224);

	}

	if (SAFE_CALL(GetModuleHandleA)(E("Fivem_GameProcess.exe")) || SAFE_CALL(GetModuleHandleA)(E("Fivem_GTAProcess.exe")))
	{
		fivem::World = (Gtabase + 0x247F840);
		fivem::ViewPort = (Gtabase + 0x2087780);
		fivem::ReplayInterface = (Gtabase + 0x1EFD4C8);
		fivem::Camera = (Gtabase + 0x2088360);
		fivem::swapchain = (Gtabase + 0x2AD7448);
		fivem::dwThreadCollectionPtr = (Gtabase + 0x1946DC8);
	//	fivem::g_OrigScriptThreads = reinterpret_cast<fivem::RunScriptThreads_t>(Gtabase + 0xA178AC);
		fivem::modelspawnbypass = (void*)(Gtabase + 0xA07FA2);

		fivem::pointer_to_handle = reinterpret_cast<fivem::pizza_to_spaghetti_t>(Gtabase + 0x1561E30);

	}
	fivem::IsOffsetWorking = true;
}
uintptr_t resolvePtr(const char* szModuleName, int64_t targetValue) {
	uintptr_t baseaddy = (uintptr_t)GetModuleHandleA(szModuleName);
	const auto dosHeader = (PIMAGE_DOS_HEADER)baseaddy;
	const auto ntHeaders = (PIMAGE_NT_HEADERS)((std::uint8_t*)baseaddy + dosHeader->e_lfanew);
	const auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;

	int64_t currentAddress = baseaddy;

	while (currentAddress < baseaddy + sizeOfImage) {
		if (*(int64_t*)currentAddress == targetValue) {
			return currentAddress;
		}
		currentAddress++;
	}

	return NULL;
}
void hooks::Initialize() {
	while (!FindWindowA("grcWindow",nullptr))
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

	}
	//MessageBoxA(NULL, "test", "test", NULL);

	//fivem::dwThreadCollectionPtr = Memory::PatternScan(E("63 6F 6D 6D 6F 6E 3A 2F 64 61 74 61 2F 73 63 72 69 70 74 4D 65 74 61 64 61 74 61"), NULL, NULL);

	FindOffset();
	//fivem::dwThreadCollectionPtr = Memory::PatternScan(E("63 6F 6D 6D 6F 6E 3A 2F 64 61 74 61 2F 73 63 72 69 70 74 4D 65 74 61 64 61 74 61"), NULL, NULL);
	//fivem::dwThreadCollectionPtr = (Memory::PatternScan(E("80 B9 ? 01 00 00 00 8B FA 48 8B D9 74 05"), NULL, NULL)- 0xF);
	//fivem::tickFuncPtr = resolvePtr(0, fivem::dwThreadCollectionPtr);
	SwapPresentVtab();
	//MessageBoxA(0, std::to_string(fivem::tickFuncPtr).c_str(), "caca", 0);
	g_tls_hook->Initialize(fivem::dwThreadCollectionPtr);
	//MessageBoxA(NULL, "test", "test", NULL);

	//HookDataNodes();
	/*g_funchookCtx = funchook_create();
	if (!g_funchookCtx) return;

	HookInputAPI();
	HookDX11GraphicsAPI();

	if (funchook_install(g_funchookCtx, 0) != FUNCHOOK_ERROR_SUCCESS) return; */
}

void hooks::Shutdown() {

}