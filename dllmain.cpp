#pragma once
#include <Windows.h>
#include <thread>

#include "src/hooks/hooks.hpp"
#include "src/entry/init_cheat.hpp"
#include "src/fivem/classes/classes.hpp"
#include "src/fivem/memory/memory.hpp"
#include "src/fivem/native/invoker.hpp"


#define CURL_STATICLIB 

char rawPathName[MAX_PATH];



BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	if (fdwReason == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hinstDLL);

		GetModuleFileNameA(hinstDLL, rawPathName, MAX_PATH);

	    //fivem::ViewPort = Memory::PatternScan(E("48 8B 15 ?? ?? ?? ?? 48 8D 2D ?? ?? ?? ?? 48 8B CD"), NULL, 7);
		//fivem::World = Memory::PatternScan(E("48 8B 05 ? ? ? ? 48 8B 48 08 48 85 C9 74 52 8B 81"), NULL, 7);
		//fivem::ReplayInterface = Memory::PatternScan(E("48 8D 0D ?? ?? ?? ?? E8 ?? ?? ?? ?? 48 8D 4C 24 ?? E8 ?? ?? ?? ?? 48 8D 4C 24 ?? E8 ?? ?? ?? ?? 48 8B 9C 24"), NULL, 7);
		//fivem::Camera = Memory::PatternScan(E("48 8B 05 ? ? ? ? 48 8B 98 ? ? ? ? EB"), NULL, 7);
		
		//fivem::GetPlayerNamess = (decltype(fivem::GetPlayerNamess))Memory::PatternScanEx((uint64_t)GetModuleHandleA(E("citizen-playernames-five.dll")), E("40 57 48 83 EC ? 48 8B 05"), NULL);
	
	//	fivem::Target_write_player_game_state_data_node = (fivem::write_player_game_state_data_node)Memory::PatternScan(E("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 54 41 55 41 56 41 57 48 83 EC 30 0F B7 81"), 0, 0);

	//	fivem::swapchain = Memory::PatternScan(E("48 8B 0D ? ? ? ? 48 8B 01 44 8D 43 01 33 D2 FF 50 40 8B C8"), NULL, 7);
		//fivem::pointer_to_handle = reinterpret_cast<fivem::pizza_to_spaghetti_t>(Memory::PatternScan(E("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 8B 15 ? ? ? ? 48 8B F9 48 83 C1 10 33 DB"), NULL, NULL));
		//fivem::handle_to_pointer = reinterpret_cast<fivem::spaghetti_to_pizza_t>(Memory::PatternScan(E("83 F9 FF 74 31 4C 8B 0D"), NULL, NULL));
	//   fivem::dwThreadCollectionPtr = Memory::PatternScan(E("63 6F 6D 6D 6F 6E 3A 2F 64 61 74 61 2F 73 63 72 69 70 74 4D 65 74 61 64 61 74 61"), NULL, NULL);

		//fivem::dwThreadCollectionPtr = Memory::PatternScan(E("48 8B ? ? ? ? ? 8B CA 4C 8B 0C C8 45"), NULL, 7);
		//fivem::activeThreadTlsOffset = Memory::PatternScan("48 8B 04 D0 4A 8B 14 00 48 8B 01 F3 44 0F 2C 42 20", NULL, NULL);
	//	fivem::g_OrigScriptThreads = reinterpret_cast<fivem::RunScriptThreads_t>(Memory::PatternScan(E("48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 20 48 8B 3D ?? ?? ?? ?? 33 DB 33 F6 39"), 0, 0));
	/*	std::uint64_t rage_base = (uint64_t)GetModuleHandleA(E("rage-scripting-five.dll"));

		g_fastPathMap = *(g_fastPathMap_t*)(Memory::PatternScanNewEx(rage_base, E("48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8B 08 48 89 59 ? 4C 8B 4C 24"), NULL, 7));
		g_mappingTable = *(g_mappingTable_t*)(Memory::PatternScanNewEx(rage_base, E("48 8D 0D ? ? ? ? E8 ? ? ? ? 41 8B 06"), NULL, 7));*/
	//	ScanMap();

		//GetNativeHandlerDo_Old = (decltype(GetNativeHandlerDo_Old))(Memory::PatternScanEx(rage_base, E("40 55 56 57 48 83 EC"), NULL));
		//GetNativeHandlerDo_Obfuscated = (decltype(GetNativeHandlerDo_Obfuscated))(Memory::PatternScanEx(rage_base, E("4C 8B DC 55 56 57 41 57"), NULL));
		if (SAFE_CALL(GetModuleHandleA)(E("FiveM_b2944_GameProcess.exe")) || SAFE_CALL(GetModuleHandleA)(E("FiveM_b2944_GTAProcess.exe")))
		{


			fivem::activeThreadTlsOffset = 0x848;
			fivem::EntityType = 0x1098;
			fivem::Armor = 0x150C;
			fivem::VehicleManager = 0xD1;
			fivem::WeaponManager = 0x10B8;
			fivem::PlayerInfo = 0x10A8;
			fivem::Recoil = 0x2F4;
			fivem::Spread = 0x84;
			fivem::ReloadMultiplier = 0x134;
			fivem::AmmoType = 0x20;

			fivem::WeaponName = 0x5F0;
			fivem::IsInAVehicule = 0x144B;
			fivem::Range = 0x28C;
			fivem::FiveM_2802 = true;
		}
		if (SAFE_CALL(GetModuleHandleA)(E("FiveM_b2802_GameProcess.exe")) || SAFE_CALL(GetModuleHandleA)(E("FiveM_b2802_GTAProcess.exe")))
		{
			fivem::activeThreadTlsOffset = 0x848;

			fivem::EntityType = 0x1098;
			fivem::Armor = 0x150C;
			fivem::VehicleManager = 0x0D10;

			fivem::WeaponManager = 0x10B8;
			fivem::PlayerInfo = 0x10A8;
			fivem::Recoil = 0x2F4;
			fivem::Spread = 0x84;
			fivem::ReloadMultiplier = 0x134;
			fivem::AmmoType = 0x20;

			fivem::WeaponName = 0x5F0;
			fivem::IsInAVehicule = 0x144B;
			fivem::Range = 0x28C;
			fivem::FiveM_2802 = true;
		}

		if (SAFE_CALL(GetModuleHandleA)(E("Fivem_b2612_GameProcess.exe")) || SAFE_CALL(GetModuleHandleA)(E("FiveM_b2612_GTAProcess.exe")) || SAFE_CALL(GetModuleHandleA)("FiveM_b2699_GTAProcess.exe") || SAFE_CALL(GetModuleHandleA)("FiveM_b2699_GameProcess.exe"))
		{

			fivem::activeThreadTlsOffset = 0x840;
			if (SAFE_CALL(GetModuleHandleA)(E("Fivem_b2612_GameProcess.exe")) || SAFE_CALL(GetModuleHandleA)(E("FiveM_b2612_GTAProcess.exe")))
			{
				fivem::activeThreadTlsOffset = 0x828;

			}
			fivem::EntityType = 0x10B8;
			fivem::Armor = 0x1530;
			fivem::VehicleManager = 0xD1;

			fivem::WeaponManager = 0x10D8;
			fivem::PlayerInfo = 0x10C8;
			fivem::Recoil = 0x2F4;
			fivem::Spread = 0x84;
			fivem::ReloadMultiplier = 0x134;
			fivem::AmmoType = 0x20;
			fivem::WeaponName = 0x5F0;
			fivem::IsInAVehicule = 0x146B;
			fivem::Range = 0x28C;
		}
		if (SAFE_CALL(GetModuleHandleA)(E("Fivem_b2545_GameProcess.exe")) || SAFE_CALL(GetModuleHandleA)(E("Fivem_b2545_GTAProcess.exe")))
		{
			fivem::activeThreadTlsOffset = 0x828;

			fivem::EntityType = 0x10B8;
			fivem::Armor = 0x14E0 + 0x50;
			fivem::VehicleManager = 0xD30;

			fivem::WeaponManager = 0x10D8;
			fivem::PlayerInfo = 0x10C8;
			fivem::Recoil = 0x2F4;
			fivem::Spread = 0x84;
			fivem::ReloadMultiplier = 0x134;
			fivem::AmmoType = 0x20;
			fivem::WeaponName = 0x5F0;
			fivem::IsInAVehicule = 0x146B;
			fivem::Range = 0x28C;
		}
		if (SAFE_CALL(GetModuleHandleA)(E("Fivem_b2372_GameProcess.exe")) || SAFE_CALL(GetModuleHandleA)(E("Fivem_b2372_GTAProcess.exe")))
		{
			fivem::activeThreadTlsOffset = 0x828;

			fivem::EntityType = 0x10B8;
			fivem::Armor = 0x14E0;
			fivem::VehicleManager = 0xD30;

			fivem::WeaponManager = 0x10D8;
			fivem::PlayerInfo = 0x10C8;
			fivem::Recoil = 0x2F4;
			fivem::Spread = 0x84;
			fivem::ReloadMultiplier = 0x134;
			fivem::AmmoType = 0x20;
			fivem::WeaponName = 0x5F0;
			fivem::IsInAVehicule = 0x141B;
			fivem::Range = 0x28C;
			fivem::is2372 = true;

		}
		if (SAFE_CALL(GetModuleHandleA)(E("Fivem_b2189_GameProcess.exe")) || SAFE_CALL(GetModuleHandleA)(E("Fivem_b2189_GTAProcess.exe")))
		{
			fivem::activeThreadTlsOffset = 0x830;

			fivem::EntityType = 0x10B8;
			fivem::Armor = 0x14E0;
			fivem::VehicleManager = 0xD1;

			fivem::WeaponManager = 0x10D8;
			fivem::PlayerInfo = 0x10C8;
			fivem::Recoil = 0x2F4;
			fivem::Spread = 0x84;
			fivem::ReloadMultiplier = 0x134;
			fivem::AmmoType = 0x20;
			fivem::EngineHealth = 0x908;
			fivem::WeaponName = 0x5F0;
			fivem::IsInAVehicule = 0x141B;
			fivem::Range = 0x28C;
		}

		if (SAFE_CALL(GetModuleHandleA)(E("Fivem_b2060_GameProcess.exe")) || SAFE_CALL(GetModuleHandleA)(E("Fivem_b2060_GTAProcess.exe")))
		{
			fivem::activeThreadTlsOffset = 0x830;

			fivem::EntityType = 0x10B8;
			fivem::Armor = 0x14E0;
			fivem::VehicleManager = 0xD30;

			fivem::WeaponManager = 0x10D8;
			fivem::PlayerInfo = 0x10B8;
			fivem::Recoil = 0x2F4;
			fivem::Spread = 0x84;
			fivem::ReloadMultiplier = 0x134;
			fivem::AmmoType = 0x20;

			fivem::WeaponName = 0x5F0;
			fivem::IsInAVehicule = 0x141B;
			fivem::Range = 0x28C;
		}

		if (SAFE_CALL(GetModuleHandleA)(E("Fivem_GameProcess.exe")) || SAFE_CALL(GetModuleHandleA)(E("Fivem_GTAProcess.exe")))
		{
			fivem::activeThreadTlsOffset = 0x830;
			fivem::EntityType = 0x10A8;
			fivem::Armor = 0x14B8;
			fivem::VehicleManager = 0x0D28;

			fivem::WeaponManager = 0x10C8;
			fivem::PlayerInfo = 0x10B8;

			fivem::Recoil = 0x2E8;
			fivem::Spread = 0x74;
			fivem::ReloadMultiplier = 0x12C;
			fivem::AmmoType = 0x20;
			fivem::WeaponName = 0x5E0;
			fivem::IsInAVehicule = 0x13FB;
			fivem::Range = 0x25C;
		}

		//settings::can_use_menu = true;
		//settings::auth = 2;
		//Auth::Login(Auth::GetHWID());



		SAFE_CALL(_beginthreadex)(0, 0, (_beginthreadex_proc_type)cheat_init, 0, 0, 0);
		
		//HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, reinterpret_cast<_beginthreadex_proc_type>(cheat_init), NULL, 0, NULL);

	//	if (hThread != NULL) {
		//	CloseHandle(hThread);
	//	}
	}
	return TRUE;
}