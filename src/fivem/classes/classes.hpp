#pragma once

#include "../includes/includes.hpp"
#include "../settings.hpp"

#include "C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\d3d9.h"
#include "C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\d3dx9.h"
#include "../../../GameState.hpp"
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include <iostream>
#include <directxmath.h>
#include <variant>
#include <deque>
#include <string>
inline std::deque<std::string> messagess;
inline void Print(const std::string& message) {
	messagess.push_back(message);
}
inline void ClearConsole() {
	messagess.clear();
}

const std::deque<std::string>& GetMessages() {
	return messagess;
}
struct netIpAddress
{
	union
	{
		uint32_t addr;
		uint8_t bytes[4];
	};
};

struct netSocketAddress
{
	netIpAddress ip;
	uint16_t port;
};

struct netPeerId
{
	uint64_t val;
};

struct rlGamerHandle
{
	uint8_t handle[16];
};

struct netAddress
{
	netSocketAddress proxyAddr;
	netSocketAddress publicAddr;
	netPeerId peerId;
	netIpAddress unkAddr;
	uint16_t unkPort;
	char unk1Eh[2];
};

struct netPeerAddress
{
public:
	struct Impl505
	{
		uint64_t unkKey1;
		uint64_t unkKey2;
		uint32_t secKeyTime; // added in 393
		netSocketAddress relayAddr;
		netSocketAddress publicAddr;
		netSocketAddress localAddr;
		uint32_t newVal; // added in 372
		uint64_t rockstarAccountId; // 463/505
	};

	struct Impl2060
	{
		uint64_t unkKey1;
		uint64_t unkKey2;
		uint32_t secKeyTime;
		netSocketAddress relayAddr;
		netSocketAddress publicAddr;
		netSocketAddress localAddr;
		netSocketAddress unkAddr; // added in 2060
		uint32_t newVal;
		uint64_t rockstarAccountId;
	};

	// unions used here are to retain accessors for external usage
#pragma pack(push, 4)
	struct Impl2372
	{
		netPeerId peerId;

		// gamer handle + pad
		union
		{
			rlGamerHandle gamerHandle;

			// compat
			struct
			{
				uint64_t rockstarAccountId;
				char pad22[8];
			};
		};

		// peer key
		union
		{
			// compat
			struct
			{
				uint64_t unkKey1;
				uint64_t unkKey2;
				char pad3[16];
				uint32_t secKeyTime;
			};

			// real
			struct
			{
				uint8_t peerKey[32];
				uint8_t hasPeerKey;
			};
		};

		netSocketAddress relayAddr;
		netSocketAddress unkAddr;
		netSocketAddress publicAddr;
		netSocketAddress localAddr;

		uint32_t newVal;
	};
#pragma pack(pop)

#pragma pack(push, 4)
	struct Impl2824
	{
		char unk0h[8];
		netPeerId peerId;

		// gamer handle + pad
		union
		{
			rlGamerHandle gamerHandle;

			// compat
			struct
			{
				uint64_t rockstarAccountId;
				char pad22[8];
			};
		};

		// peer key
		union
		{
			// compat
			struct
			{
				uint64_t unkKey1;
				uint64_t unkKey2;
				char pad3[16];
				uint32_t secKeyTime;
			};

			// real
			struct
			{
				uint8_t peerKey[32];
				uint8_t hasPeerKey;
			};
		};

		union
		{
			// real
			struct
			{
				char pad4[4];
				netAddress relayAddrStruct;
			};

			// compat
			struct
			{
				char pad4[4];
				netSocketAddress relayAddr;
				char pad5[24];
			};
		};

		union
		{
			// real
			struct
			{
				char unk68h[64];
			};

			// compat
			struct
			{
				netSocketAddress unkAddr;
				char pad6[48];
			};
		};

		netSocketAddress publicAddr;
		netSocketAddress localAddr;

		uint32_t newVal;

		char unkBCh[4];
	};
#pragma pack(pop)

	union Impls
	{
		Impl505 m1604;
		Impl2060 m2060;
		Impl2372 m2372;
		Impl2824 m2824;
	};


};

template<int Build>
struct netPeerAddressStorage : netPeerAddress
{
};

template<>
struct netPeerAddressStorage<1604> : netPeerAddress
{
	uint8_t data[sizeof(Impl505)];
};

template<>
struct netPeerAddressStorage<2060> : netPeerAddress
{
	uint8_t data[sizeof(Impl2060)];
};

template<>
struct netPeerAddressStorage<2372> : netPeerAddress
{
	uint8_t data[sizeof(Impl2372)];
};

template<>
struct netPeerAddressStorage<2824> : netPeerAddress
{
	uint8_t data[sizeof(Impl2824)];
};

template<int Build>
using PeerAddress = std::conditional_t<(Build >= 2824), netPeerAddressStorage<2824>, std::conditional_t<(Build >= 2372), netPeerAddressStorage<2372>, std::conditional_t<(Build >= 2060), netPeerAddressStorage<2060>, netPeerAddressStorage<1604>>>>;

static_assert(sizeof(PeerAddress<1604>) == 56);
static_assert(sizeof(PeerAddress<2060>) == 64);
static_assert(sizeof(PeerAddress<2372>) == 96);
static_assert(sizeof(PeerAddress<2824>) == 192);

using namespace std;


class Vector3 final
{
public:

	float x, y, z;
	Vector3() : x(0.0f), y(0.0f), z(0.0f) {}

	Vector3(const float x, const float y, const float z) : x(x), y(y), z(z) {}
	Vector3 operator + (const Vector3& rhs) const { return Vector3(x + rhs.x, y + rhs.y, z + rhs.z); }
	Vector3 operator - (const Vector3& rhs) const { return Vector3(x - rhs.x, y - rhs.y, z - rhs.z); }
	Vector3 operator * (const float& rhs) const { return Vector3(x * rhs, y * rhs, z * rhs); }
	Vector3 operator / (const float& rhs) const { return Vector3(x / rhs, y / rhs, z / rhs); }
	bool operator == (const Vector3& rhs) const { return x == rhs.x && y == rhs.y && z == rhs.z; }
	Vector3& operator += (const Vector3& rhs) { return *this = *this + rhs; }
	Vector3& operator -= (const Vector3& rhs) { return *this = *this - rhs; }
	Vector3& operator *= (const float& rhs) { return *this = *this * rhs; }
	Vector3& operator /= (const float& rhs) { return *this = *this / rhs; }
	float Length() const { return sqrt(x * x + y * y + z * z); }
	Vector3 Normalize() const { return *this * (1 / Length()); }
	float Distance(const Vector3& rhs) const { return (*this - rhs).Length(); }
	void Invert() { *this *= -1; }
	static Vector3 FromM128(__m128 in) { return Vector3(in.m128_f32[0], in.m128_f32[1], in.m128_f32[2]); }
};

class Vector4
{
public:
	float x, y, z, w;
};

inline ImVec2 GetWindowSize()
{
	RECT rect;
	HWND hwnd = GetActiveWindow();
	if (GetWindowRect(hwnd, &rect))
	{
		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;
		return ImVec2(width, height);
	}
	return ImVec2(0, 0);
}

struct Matrix
{
	float m[4][4];

	Matrix() {}

	Matrix(float _11, float _12, float _13, float _14,
		float _21, float _22, float _23, float _24,
		float _31, float _32, float _33, float _34,
		float _41, float _42, float _43, float _44)
	{
		m[0][0] = _11; m[0][1] = _12; m[0][2] = _13; m[0][3] = _14;
		m[1][0] = _21; m[1][1] = _22; m[1][2] = _23; m[1][3] = _24;
		m[2][0] = _31; m[2][1] = _32; m[2][2] = _33; m[2][3] = _34;
		m[3][0] = _41; m[3][1] = _42; m[3][2] = _43; m[3][3] = _44;
	}
	// Functions for manipulating the matrix
	void Identity()
	{
		memset(m, 0, sizeof(Matrix));
		m[0][0] = 1.0f;
		m[1][1] = 1.0f;
		m[2][2] = 1.0f;
		m[3][3] = 1.0f;
	}
};
inline void transposeMatrix(Matrix& matrix) {
	for (int i = 0; i < 4; i++) {
		for (int j = i + 1; j < 4; j++) {
			std::swap(matrix.m[i][j], matrix.m[j][i]);
		}
	}
}

class Vector3Fix {
public:
	Vector3Fix() = default;

	Vector3Fix(float x, float y, float z) :
		x(x), y(y), z(z)
	{}

	// Conversion de Vector3Fix en Vector3
	operator Vector3() const {
		return Vector3(x, y, z);
	}

public:
	float x{};
private:
	char m_padding1[0x04]{};
public:
	float y{};
private:
	char m_padding2[0x04]{};
public:
	float z{};
private:
	char m_padding3[0x04]{};
};

namespace fivem {
	using namespace fivem;
	inline bool is2944 = false;
	inline bool is2372 = false;
	inline bool is2060 = false;
	inline bool is2189 = false;
	inline bool is2612 = false;

	inline bool IsPoolHooked = false;
	inline bool IsOffsetWorking = true;
	typedef BOOL(__fastcall* write_player_game_state_data_node)(uintptr_t* PlayerNetObject, CPlayerGameStateDataNode* node);
	inline write_player_game_state_data_node Target_write_player_game_state_data_node = nullptr;
	inline uint64_t PatchX;
	inline uint64_t PatchY;
	inline uint64_t PatchZ;
	inline void* modelspawnbypass;

	typedef void(*RunScriptThreads_t)();
	RunScriptThreads_t g_OrigScriptThreads = NULL;
	inline uint64_t World, ReplayInterface, BonePos, Camera, ViewPort,swapchain;
	inline DWORD64 dwThreadCollectionPtr;
	inline uintptr_t tickFuncPtr;
	inline UINT32 activeThreadTlsOffset;
	typedef __int64(__fastcall* HandleBullet_t)(__int64 BulletPtr, class CWeaponInfo* CWeaponInfo, Vector3 StartPos, Vector3 EndPos, float Range, int weaponHash, char a7, char a8);
	inline DWORD Armor, EntityType, VehicleManager , WeaponManager, PlayerInfo, Recoil, Spread, AmmoType, WeaponName, Range, ReloadMultiplier, VehiculeReloadMultiplier, IsInAVehicule, EngineHealth, BodyHealth, HealthOfVehicle;
	inline bool FiveM_2802 = false;
	inline const char* (__fastcall* GetPlayerNamess)(void*);
	inline ImVec2 WindowSize = ImVec2(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	using pizza_to_spaghetti_t = int32_t(*)(intptr_t pointer); //le truc pr convert un ped en handle
	inline std::vector<std::string> Friend;

	inline pizza_to_spaghetti_t pointer_to_handle;
	using spaghetti_to_pizza_t = intptr_t(*)(int32_t pointer); //le truc pr convert un handle en ped
	inline spaghetti_to_pizza_t handle_to_pointer;

	typedef BOOL(__fastcall* g_bone_mask_t)(DWORD64 CPed, __m128* virtualbonepos, unsigned int bone);
	
//	using write_player_game_state_data_node = bool (*)(rage::netObject* plr, CPlayerGameStateDataNode* node);



	 inline DWORD64 GetCamera()
	{
		if (Camera)
			return *(DWORD64*)(Camera);
	}

	inline ImVec2 WorldToScreen(Vector3 pos)
	{
		uint64_t viewport = *(uint64_t*)(fivem::ViewPort);

		D3DXMATRIX matrix = *(D3DXMATRIX*)(viewport + 0x24C);

		D3DXVECTOR3 screenPosition;

		D3DXMatrixTranspose(&matrix, &matrix);
		D3DXVECTOR4 vectorX = D3DXVECTOR4(matrix._21, matrix._22, matrix._23, matrix._24);
		D3DXVECTOR4 vectorY = D3DXVECTOR4(matrix._31, matrix._32, matrix._33, matrix._34);
		D3DXVECTOR4 vectorZ = D3DXVECTOR4(matrix._41, matrix._42, matrix._43, matrix._44);

		screenPosition.x = (vectorX.x * pos.x) + (vectorX.y * pos.y) + (vectorX.z * pos.z) + vectorX.w;
		screenPosition.y = (vectorY.x * pos.x) + (vectorY.y * pos.y) + (vectorY.z * pos.z) + vectorY.w;
		screenPosition.z = (vectorZ.x * pos.x) + (vectorZ.y * pos.y) + (vectorZ.z * pos.z) + vectorZ.w;
		if (screenPosition.z <= 0.01f)
			return ImVec2(0, 0);

		screenPosition.z = 1.0f / screenPosition.z;
		screenPosition.x *= screenPosition.z;
		screenPosition.y *= screenPosition.z;

		float xTmp = fivem::WindowSize.x / 2;
		float yTmp = fivem::WindowSize.y / 2;

		screenPosition.x += xTmp + (int)(0.5f * screenPosition.x * 1920 + 0.5f);
		screenPosition.y = yTmp - (int)(0.5f * screenPosition.y * 1080 + 0.5f);

		return ImVec2(screenPosition.x, screenPosition.y);
	}

	inline float pythag(ImVec2 src, ImVec2 dst)
	{
		return sqrtf(pow(src.x - dst.x, 2) + pow(src.y - dst.y, 2));
	}

	inline float pythagVec3(Vector3 src, Vector3 dst)
	{
		return sqrtf(pow(src.x - dst.x, 2) + pow(src.y - dst.y, 2) + pow(src.z - dst.z, 2));
	}
	enum class ePedBoneType
	{
		HEAD,
		L_FOOT,
		R_FOOT,
		L_ANKLE,
		R_ANKLE,
		L_HAND,
		R_HAND,
		NECK,
		ABDOMEN
	};
	/*// Basic
	inline Vector3 GetBonePos(const uint64_t cPed, const int32_t wMask)
	{
		__m128 tempVec4;
		reinterpret_cast<void* (__fastcall*)(uint64_t, __m128*, int32_t)>(BonePos)(cPed, &tempVec4, wMask);
		return Vector3::FromM128(tempVec4);
	}
	inline ImVec2 GetBonePosW2S(const uint64_t cPed, const int32_t wMask)
	{
		__m128 tempVec4;
		reinterpret_cast<void* (__fastcall*)(uint64_t, __m128*, int32_t)>(BonePos)(cPed, &tempVec4, wMask);
		return WorldToScreen(Vector3::FromM128(tempVec4));
	}
	//*/
	// Array
	inline Vector3 GetBoneArrayPos(const uint64_t cPed, int wMask)
	{

		D3DXMATRIX matrix = *(D3DXMATRIX*)(cPed + 0x60);
		D3DXVECTOR3 bone = *(D3DXVECTOR3*)(cPed + (FiveM_2802 ? 0x410 : 0x430) + (wMask * 0x10));
		D3DXVECTOR4 transform;
		D3DXVec3Transform(&transform, &bone, &matrix);

		return Vector3(transform.x, transform.y, transform.z);
	}
	inline ImVec2 GetBoneArrayW2SPos(const uint64_t cPed, int wMask)
	{
		return WorldToScreen(GetBoneArrayPos(cPed, wMask));
	}
	//
	inline Vector3 GetBonePosMatrix(const uint64_t cPed, int bone)
	{
		return GetBoneArrayPos(cPed, bone);
	}
	inline ImVec2 GetBonePosMatrixW2S(const uint64_t cPed, int bone)
	{
		return GetBoneArrayW2SPos(cPed, bone);
	}
}

inline const char* Get_player_name(__int64 num)
{
	//using GetName_t = const char* (*)(__int64 num);
	//static auto GetName = (GetName_t)(Memory::PatternScan(E("40 53 48 83 EC ? 80 3D ? ? ? ? ? 8B D9 74 ? 33 D2"), NULL, NULL));
	//	(CustomAPII::ScanSignature(NULL, "40 53 48 83 EC ? 80 3D ? ? ? ? ? 8B D9 74 ? 33 D2"));
//	return GetName(num);
}

inline auto DrawOutlinedText(ImFont* font, const std::string& text, const ImVec2& pos, float size, ImU32 color, bool center) -> VOID {
	ImGui::GetBackgroundDrawList()->PushTextureID(font->ContainerAtlas->TexID);

	std::stringstream stream(text);
	std::string line;

	float y = 0.0f;
	int index = 0;

	while (std::getline(stream, line)) {
		ImVec2 textSize = font->CalcTextSizeA(size, FLT_MAX, 0.0f, line.c_str());

		ImGui::GetBackgroundDrawList()->AddText(font, font->FontSize, ImVec2((pos.x - textSize.x / 2.0f) + 1, (pos.y + textSize.y * index)), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());
		ImGui::GetBackgroundDrawList()->AddText(font, font->FontSize, ImVec2((pos.x - textSize.x / 2.0f) - 1, (pos.y + textSize.y * index)), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());
		ImGui::GetBackgroundDrawList()->AddText(font, font->FontSize, ImVec2(pos.x - textSize.x / 2.0f, pos.y + textSize.y * index), ImGui::GetColorU32(color), line.c_str());

		if (center) {
			ImGui::GetBackgroundDrawList()->AddText(font, font->FontSize, ImVec2((pos.x - textSize.x / 2.0f) + 1, (pos.y + textSize.y * index)), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());
			ImGui::GetBackgroundDrawList()->AddText(font, font->FontSize, ImVec2((pos.x - textSize.x / 2.0f) - 1, (pos.y + textSize.y * index)), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());
			ImGui::GetBackgroundDrawList()->AddText(font, font->FontSize, ImVec2(pos.x - textSize.x / 2.0f, pos.y + textSize.y * index), ImGui::GetColorU32(color), line.c_str());
		}
		else {
			ImGui::GetBackgroundDrawList()->AddText(font, font->FontSize + 1, ImVec2((pos.x) + 1, (pos.y + textSize.y * index)), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());
			ImGui::GetBackgroundDrawList()->AddText(font, font->FontSize, ImVec2(pos.x, pos.y + textSize.y * index), ImGui::GetColorU32(color), line.c_str());
		}
	}
}

inline bool IsOnScreen(ImVec2 coords)
{
	if (coords.x < 0.1f || coords.y < 0.1 || coords.x > ImGui::GetIO().DisplaySize.x || coords.y > ImGui::GetIO().DisplaySize.y)
	{
		return false;
	}
	else {
		return true;
	}
}
inline void DrawHealthBar(ImVec2 pos, ImVec2 dim, ImColor col)
{
	if (IsOnScreen(pos))
	{
		ImGui::GetBackgroundDrawList()->AddRect(pos, ImVec2(pos.x + 1, pos.y + 1 - dim.y), ImColor(0, 0, 0, 255), dim.x);
		ImGui::GetBackgroundDrawList()->AddRect(pos, ImVec2(pos.x - 1, pos.y - 1 - dim.y), ImColor(0, 0, 0, 255), dim.x);
		ImGui::GetBackgroundDrawList()->AddRect(pos, ImVec2(pos.x, pos.y - dim.y), ImColor(80, 80, 80, 125), dim.x);
		ImGui::GetBackgroundDrawList()->AddRectFilled(pos, ImVec2(pos.x, pos.y - dim.y), col, dim.x);
	}
}
inline void DrawHealthBarhorizontal(ImVec2 pos, ImVec2 pos2, ImVec2 dim, ImColor col)
{
	if (IsOnScreen(pos))
	{
		ImGui::GetBackgroundDrawList()->AddRect(ImVec2(pos.x + dim.y, pos.y), ImVec2(pos2.x + 1, pos.y + 1), ImColor(0, 0, 0, 255), dim.x);
		ImGui::GetBackgroundDrawList()->AddRect(ImVec2(pos.x + dim.y, pos.y), ImVec2(pos2.x - 1, pos.y - 1), ImColor(0, 0, 0, 255), dim.x);
		ImGui::GetBackgroundDrawList()->AddRect(ImVec2(pos.x + dim.y, pos.y), ImVec2(pos2.x, pos.y), ImColor(80, 80, 80, 125), dim.x);
		ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(pos.x + dim.y, pos.y), ImVec2(pos2.x, pos.y), col, dim.x);
	}
}

inline const char* get_weapon_name(DWORD hash)
{
	//removed xoring, cba to do properly.
	const char* dagger = ("Dagger");
	const char* bat = ("Bat");
	const char* bottle = ("Bottle");
	const char* crowbar = ("Crow Bar");
	const char* unarmed = ("None");
	const char* flashlight = ("Flash Light");
	const char* golfclub = ("Golf club");
	const char* hammer = ("Hammer");
	const char* hatchet = ("Hatchet");
	const char* knuckle = ("Knuckle");
	const char* knife = ("Knife");
	const char* machete = ("Machete");
	const char* switchblade = ("Switch Blade");
	const char* nightstick = ("Night Stick");
	const char* wrench = ("Wrench");
	const char* battleaxe = ("Battle Axe");
	const char* poolcue = ("Pool Cue");
	const char* pistol = ("Pistol");
	const char* pistolmk2 = ("Pistol MK2");
	const char* combatpistol = ("Combat Pistol");
	const char* appistol = ("AP Pistol");
	const char* stungun = ("Stungun");
	const char* pistol50 = ("Pistol 50");
	const char* snspistol = ("SNS PISTOL");
	const char* snspistolmk2 = ("SNS Pistol MK2");
	const char* heavypistol = ("Heavy Pistol");
	const char* vintagepistol = ("Vintage Pisol");
	const char* flaregun = ("Flare Gun");
	const char* marksmanpistol = ("marksmanpistol");
	const char* revolver = ("Revolver");
	const char* revolvermk2 = ("Revolver MK2");
	static auto doubleaction = ("Double Action");
	static auto microsmg = ("Micro Smg");
	static auto smg = ("Smg");
	static auto smgmk2 = ("Smg MK2");
	static auto assaultsmg = ("Assault Smg");
	static auto combatpdw = ("Combat PDW");
	static auto machinepistol = ("Machine Pistol");
	static auto minismg = ("Mini Smg");
	static auto pumpshotgun = ("Pump Shotgun");
	static auto pumpshotgun_mk2 = ("Pump Shotgun MK2");
	static auto sawnoffshotgun = ("Sawnoff Shotgun");
	static auto assaultshotgun = ("Sssault Shotgun");
	static auto bullpupshotgun = ("Bullpup Shotgun");
	static auto musket = ("Musket");
	static auto heavyshotgun = ("Heavy Shotgun");
	static auto dbshotgun = ("DB Shotgun");
	static auto autoshotgun = ("Auto Shotgun");
	static auto assaultrifle = ("Assault Rifle");
	static auto assaultrifle_mk2 = ("Assault Rifle MK2");
	static auto carbinerifle = ("Carbine Rifle");
	static auto carbinerifle_mk2 = ("Carbine Rifle MK2");
	static auto advancedrifle = ("Advanced Rifle");
	static auto specialcarbine = ("Special Carbine");
	static auto specialcarbine_mk2 = ("Special Carbine MK2");
	static auto bullpuprifle = ("Bullpup Rifle");
	static auto bullpuprifle_mk2 = ("Bullpup Rifle MK2");
	static auto compactrifle = ("Compact Rifle");
	static auto machine_gun = ("Machine Gun");
	static auto combatmg = ("Combat MG");
	static auto combatmg_mk2 = ("Combat MG MK2");
	static auto gusenberg = ("GUSENBERG");
	static auto sniperrifle = ("Sniper Rifle");
	static auto heavysniper = ("AWP");
	static auto heavysniper_mk2 = ("AWP MK2");
	static auto marksmanrifle = ("Marksman Rifle");
	static auto marksmanrifle_mk2 = ("Marksman Rifle MK2");
	static auto rpg = ("RPG");
	static auto grenadelauncher = ("Grenade Launcher");
	static auto grenadelauncher_smoke = ("Grenade Launcher Smoke");
	static auto minigun = ("MiniGun");
	static auto firework = ("FireWork");
	static auto railgun = ("RailGun");
	static auto hominglauncher = ("Homing Launcher");
	static auto compactlauncher = ("Compact Launcher");
	static auto grenade = ("Grenade");
	static auto bzgas = ("BZGAS");
	static auto smokegrenade = ("Smoke Grenade");
	static auto flare = ("Flare");
	static auto molotov = ("Molotov");
	static auto stickybomb = ("Sticky BOMB");
	static auto proxmine = ("Prox Mine");
	static auto snowball = ("SnowBall");
	static auto pipebomb = ("Pipe Bomb");
	static auto ball = ("Ball");
	static auto petrolcan = ("Petrol Can");
	static auto fireextinguisher = ("Fire Extinguisher");
	static auto parachute = ("Parachute");

	static auto weapon_militaryrifle = ("Military Rifle");
	static auto weapon_heavyrifle = ("Heavy Rifle");
	static auto weapon_tacticalrifle = ("Tactical Rifle");

	static auto weapon_precisionrifle = ("Precision Rifle");

	static auto weapon_emplauncher = ("Compact EMP Launcher");
	static auto weapon_rayminigun = ("RayMiniGun");

	switch (hash)
	{
	case 0x92A27487:
		return dagger; break;
	case 0x958A4A8F:
		return bat; break;
	case 0xF9E6AA4B:
		return bottle; break;
	case 0x84BD7BFD:
		return crowbar; break;
	case 0xA2719263:
		return unarmed; break;
	case 0x8BB05FD7:
		return flashlight; break;
	case 0x440E4788:
		return golfclub; break;
	case 0x4E875F73:
		return hammer; break;
	case 0xF9DCBF2D:
		return hatchet; break;
	case 0xD8DF3C3C:
		return knuckle; break;
	case 0x99B507EA:
		return knife; break;
	case 0xDD5DF8D9:
		return machete; break;
	case 0xDFE37640:
		return switchblade; break;
	case 0x678B81B1:
		return nightstick; break;
	case 0x19044EE0:
		return wrench; break;
	case 0xCD274149:
		return battleaxe; break;
	case 0x94117305:
		return poolcue; break;
	case 0x1B06D571:
		return pistol; break;
	case 0xBFE256D4:
		return pistolmk2; break;
	case 0x5EF9FEC4:
		return combatpistol; break;
	case 0x22D8FE39:
		return appistol; break;
	case 0x3656C8C1:
		return stungun; break;
	case 0x99AEEB3B:
		return pistol50; break;
	case 0xBFD21232:
		return snspistol; break;
	case 0x88374054:
		return snspistolmk2; break;
	case 0xD205520E:
		return heavypistol; break;
	case 0x83839C4:
		return vintagepistol; break;
	case 0x47757124:
		return flaregun; break;
	case 0xDC4DB296:
		return marksmanpistol; break;
	case 0xC1B3C3D1:
		return revolver; break;
	case 0xCB96392F:
		return revolvermk2; break;
	case 0x97EA20B8:
		return doubleaction; break;
	case 0x13532244:
		return microsmg; break;
	case 0x2BE6766B:
		return smg; break;
	case 0x78A97CD0:
		return smgmk2; break;
	case 0xEFE7E2DF:
		return assaultsmg; break;
	case 0xA3D4D34:
		return combatpdw; break;
	case 0xDB1AA450:
		return machinepistol; break;
	case 0xBD248B55:
		return minismg; break;
	case 0x1D073A89:
		return pumpshotgun; break;
	case 0x555AF99A:
		return pumpshotgun_mk2; break;
	case 0x7846A318:
		return sawnoffshotgun; break;
	case 0xE284C527:
		return assaultshotgun; break;
	case 0x9D61E50F:
		return bullpupshotgun; break;
	case 0xA89CB99E:
		return musket; break;
	case 0x3AABBBAA:
		return heavyshotgun; break;
	case 0xEF951FBB:
		return dbshotgun; break;
	case 0x12E82D3D:
		return autoshotgun; break;
	case 0xBFEFFF6D:
		return assaultrifle; break;
	case 0x394F415C:
		return assaultrifle_mk2; break;
	case 0x83BF0278:
		return carbinerifle; break;
	case 0xFAD1F1C9:
		return carbinerifle_mk2; break;
	case 0xAF113F99:
		return advancedrifle; break;
	case 0xC0A3098D:
		return specialcarbine; break;
	case 0x969C3D67:
		return specialcarbine_mk2; break;
	case 0x7F229F94:
		return bullpuprifle; break;
	case 0x84D6FAFD:
		return bullpuprifle_mk2; break;
	case 0x624FE830:
		return compactrifle; break;
	case 0x9D07F764:
		return machine_gun; break;
	case 0x7FD62962:
		return combatmg; break;
	case 0xDBBD7280:
		return combatmg_mk2; break;
	case 0x61012683:
		return gusenberg; break;
	case 0x5FC3C11:
		return sniperrifle; break;
	case 0xC472FE2:
		return heavysniper; break;
	case 0xA914799:
		return heavysniper_mk2; break;
	case 0xC734385A:
		return marksmanrifle; break;
	case 0x6A6C02E0:
		return marksmanrifle_mk2; break;
	case 0xB1CA77B1:
		return rpg; break;
	case 0xA284510B:
		return grenadelauncher; break;
	case 0x4DD2DC56:
		return grenadelauncher_smoke; break;
	case 0x42BF8A85:
		return minigun; break;
	case 0x7F7497E5:
		return firework; break;
	case 0x6D544C99:
		return railgun; break;
	case 0x63AB0442:
		return hominglauncher; break;
	case 0x781FE4A:
		return compactlauncher; break;
	case 0x93E220BD:
		return grenade; break;
	case 0xA0973D5E:
		return bzgas; break;
	case 0xFDBC8A50:
		return smokegrenade; break;
	case 0x497FACC3:
		return flare; break;
	case 0x24B17070:
		return molotov; break;
	case 0x2C3731D9:
		return stickybomb; break;
	case 0xAB564B93:
		return proxmine; break;
	case 0x787F0BB:
		return snowball; break;
	case 0xBA45E8B8:
		return pipebomb; break;
	case 0x23C9F95C:
		return ball; break;
	case 0x34A67B97:
		return petrolcan; break;
	case 0x60EC506:
		return fireextinguisher; break;
	case 0xFBAB5776:
		return parachute; break;
	case 0x9D1F17E6:
		return weapon_militaryrifle; break;
	case 0xC78D71B4:
		return weapon_heavyrifle; break;
	case 0xD1D5F52B:
		return weapon_tacticalrifle; break;
	case 0x6E7DDDEC:
		return weapon_precisionrifle; break;

	case 0xDB26713A:
		return weapon_emplauncher; break;
	case 0xB62D1F67:
		return weapon_rayminigun; break;
	default:
		return unarmed; break;
	}
}

class  hk_FixedAmmoCount
{
public:

	float SetAmmo(float caca)
	{
		if (!this) return 0;
		return *(uint32_t*)(this + 0x18) = caca;
	}
};

class hk_AmmoCount
{
public:

	hk_FixedAmmoCount* FixedAmmoCount()
	{
		if (!this) return 0;
		return (hk_FixedAmmoCount*)(*(uint64_t*)(this + 0x0));
	}
};
class hk_AmmoInfo
{
public:

	hk_AmmoCount* AmmoCount()
	{
		if (!this) return 0;
		return (hk_AmmoCount*)(*(uint64_t*)(this + 0x8));
	}

	float SetSpeedBullet(float value)
	{
		if (!this) return 0;
		return *(float*)(this + 0x58) = value;
	}
};

class hk_WeaponInfo
{
public:

	float SetMultiBulletSpread(float caca)
	{
		if (!this) return NULL;
		return *(float*)(this + 0x011C) = caca;
	}

	float Damage_boost(float caca)
	{
		if (!this) return NULL;
		return *(float*)(this + 0x00B0) = caca;
	}

	std::int32_t SetBulletPerShot(std::int32_t caca)
	{
		if (!this) return NULL;
		return *(std::int32_t*)(this + 0x0118) = caca;
	}
	uint64_t GetHash()
	{
		if (!this) return NULL;
		return *(uint64_t*)(this + 0x10);
	}

	uint64_t SetHash(DWORD caca)
	{
		if (!this) return NULL;
		return *(uint64_t*)(this + 0x10) = caca;
	}
	float SetSpread(float value)
	{
		if (!this) return 0;
		return *(float*)(this + fivem::Spread) = value;
	}

	float SetRecoil(float value)
	{
		if (!this) return 0;
		return *(float*)(this + fivem::Recoil) = value;
	}
	float SetDamage(float value)
	{
		if (!this) return 0;
		return *(float*)(this + 0xB0) = value;
	}

	hk_AmmoInfo* AmmoInfo()
	{
		if (!this) return 0;
		return (hk_AmmoInfo*)(*(uint64_t*)(this + 0x60));
	}

	float SetReload(float value)
	{
		if (!this) return 0;
		return *(float*)(this + fivem::ReloadMultiplier) = value;
	}

	float Fov(float value) {
		if (!this) return 0;
		return *(float*)(this + 0x02FC) = value;
	}
	float RFov(float value) {
		if (!this) return 0;
		return *(float*)(this + 0x0308) = value;
	}
	float SFov(float value) {
		if (!this) return 0;
		return *(float*)(this + 0x0300) = value;
	}
	float SetRange(float value)
	{
		if (!this) return 0;
		return *(float*)(this + fivem::Range) = value;
	}
	int32_t  SetAmmoType(float value)
	{
		if (!this) return 0;
		return *(int32_t*)(this + fivem::AmmoType) = value;
	}
};
class hk_ObjectNavigationVehicle
{
public:
	Vector3 GetCoordinate()
	{
		if (!this) return Vector3{ 0,0,0 };
		return *(Vector3*)(this + 0x50);
	}
	Vector3 SetCoordinate(Vector3 Cords)
	{
		if (!this) return Vector3{ 0,0,0 };
		return *(Vector3*)(this + 0x50) = Cords;
	}

	Vector4 SetRotation(Vector4 Coords)
	{
		if (!this) return Vector4{ 0,0,0,0 };
		return *(Vector4*)(this + 0x30) = Coords;
	}
};
class hk_WeaponManager
{
public:
	hk_WeaponInfo* WeaponInfo()
	{
		if (!this) return 0;
		return (hk_WeaponInfo*)(*(uint64_t*)(this + 0x20));
	}

	Vector3 GetWeaponCoordinate()
	{
		if (!this) return Vector3{ 0,0,0 };
		return *(Vector3*)(this + 0x1A0);
	}
	Vector3 SetWeaponCoordinate(Vector3 point)
	{
		if (!this) return Vector3{ 0,0,0 };
		return *(Vector3*)(this + 0x1A0) = point;
	}
};

class hk_ObjectNavigationPed
{
public:
	Vector3 GetCoordinate()
	{
		if (!this) return Vector3{ 0,0,0 };
		return *(Vector3*)(this + 0x50);
	}
	Vector3 SetCoordinate(Vector3 Cords)
	{
		if (!this) return Vector3{ 0,0,0 };
		return *(Vector3*)(this + 0x50) = Cords;
	}

	Vector4 SetRotation(Vector4 Coords)
	{
		if (!this) return Vector4{ 0,0,0 ,0 };
		return *(Vector4*)(this + 0x30) = Coords;
	}
};
class hk_VehicleModelInfo
{
public:

	char* GetCharName()
	{
		if (!this) return 0;
		return (char*)(this + 0x298);
	}
};

class hk_VehicleHandlingInfo
{
public:

	float SetMass(float Health)
	{
		if (!this) return 0;
		return *(float*)(this + 0x0C) = Health;
	}
	float SetAcceleration(float Health)
	{
		if (!this) return 0;
		return *(float*)(this + 0x4C) = Health;
	}
	float SetHandBrake(float Health)
	{
		if (!this) return 0;
		return *(float*)(this + 0x7C) = Health;
	}
	float SetBrake(float Health)
	{
		if (!this) return 0;
		return *(float*)(this + 0x6C) = Health;
	}
};
class hk_Vehicle
{
public:
	hk_VehicleModelInfo* VehicleModelInfo()
	{
		if (!this) return 0;
		return (hk_VehicleModelInfo*)(*(uint64_t*)(this + 0x20));
	}
	hk_VehicleHandlingInfo* VehicleHandlingInfo()
	{
		if (!this) return 0;
		return (hk_VehicleHandlingInfo*)(*(uint64_t*)(this + 0x938));
	}
	hk_ObjectNavigationVehicle* ObjectNavigation()
	{
		if (!this) return 0;
		return (hk_ObjectNavigationVehicle*)(*(uint64_t*)(this + 0x30));
	}
	Vector3 GetCoordinate()
	{
		if (!this) return Vector3{ 0,0,0 };
		return *(Vector3*)(this + 0x90);
	}
	Vector3 SetCoordinate(Vector3 Cords)
	{
		if (!this) return Vector3{ 0,0,0 };
		return *(Vector3*)(this + 0x90) = Cords;
	}
	Vector3 GetVelocity()
	{
		if (!this) return Vector3{ 0,0,0 };
		return *(Vector3*)(this + 0x07D0);
	}
	Vector3 SetVelocity()
	{
		if (!this) return Vector3{ 0,0,0 };
		return *(Vector3*)(this + 0x320) = Vector3(0, 0, 0);
	}
	float GetHealth()
	{
		if (!this) return 0;
		return *(float*)(this + 0x280);
	}
	bool Godmode(bool value)
	{
		if (!this) return 0;
		return *(bool*)(this + 0x189) = value;
	}
	float GetMaxHealth()
	{
		if (!this) return 0;
		return *(float*)(this + 0x284);
	}
	float SetHealth(float Health)
	{
		if (!this) return 0;
		return *(float*)(this + 0x280) = Health;
	}
	float SetGravity(float Health)
	{
		if (!this) return 0;
		return *(float*)(this + 0xC5C) = Health;
	}
	float SetBodyHealth(float Health)
	{
		if (!this) return 0;
		return *(float*)(this + 0x840) = Health;
	}
	float SetEngineHealth(float Health)
	{
		if (!this) return 0;
		return *(float*)(this + 0x908) = Health;
	}
};

class hk_Gravity
{
public:

	bool IsNoGravity()
	{
		if (*(uint16_t*)(this + 0x1A) == 780)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	uint16_t SetNoGravity(bool caca)
	{
		if (!this) return 0;
		if (caca)
			return *(uint16_t*)(this + 0x1A) = 0x30C;
		else
			return *(uint16_t*)(this + 0x1A) = 0x304;
	}
};
class hk_PlayerInfo
{
public:

	uintptr_t NetInfo()
	{
		if (!this) return 0;
		return *(DWORD64*)(this + 0x0020);
	}
	uint32_t SetSuperJump(bool toggle)
	{
		if (toggle)
		{
			if (!this) return 0;
			return *(BYTE*)(this + 0x218) |= 1 << 14;;
		}
		else
		{
			if (!this) return 0;
			return *(BYTE*)(this + 0x218) = 0;
		}
	}

	float SetSpeed(float value)
	{
		if (!this) return 0;
		return *(float*)(this + 0x0CF0) = value;
	}
};
class hk_PedModelInfo
{
public:

	Vector3 GetMin()
	{
		if (!this) return Vector3{ 0,0,0 };
		return *(Vector3*)(this + 0x30);
	}
	Vector3 GetMax()
	{
		if (!this) return Vector3{ 0,0,0 };
		return *(Vector3*)(this + 0x40);
	}
};

class hk_Ped
{
public:
	hk_PedModelInfo* PedModelInfo()
	{
		if (!this) return 0;
		return (hk_PedModelInfo*)(*(uint64_t*)(this + 0x20));
	}
	hk_PlayerInfo* PlayerInfo()
	{
		if (!this) return 0;
		return (hk_PlayerInfo*)(*(uint64_t*)(this + fivem::PlayerInfo));
	}
	hk_WeaponManager* WeaponManager()
	{
		if (!this) return 0;
		return (hk_WeaponManager*)(*(uint64_t*)(this + fivem::WeaponManager));
	}
	hk_Gravity* GravityManager()
	{
		if (!this) return 0;
		return (hk_Gravity*)(*(uintptr_t*)(this + 0x1110));
	}
	hk_Vehicle* VehicleManager()
	{
		if (!this) return 0;
		return (hk_Vehicle*)(*(uint64_t*)(this + fivem::VehicleManager));
	}
	hk_ObjectNavigationPed* ObjectNavigation()
	{
		if (!this) return 0;
		return (hk_ObjectNavigationPed*)(*(uint64_t*)(this + 0x30));
	}
	bool IsInAVehicule()
	{
		if (!this) return false;
		if (*(BYTE*)(this + fivem::IsInAVehicule) == 0x40)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool SetFreeze(bool toggle)
	{
		if (!this) return 0;
		return *(BYTE*)(this + 0x218) = toggle;
	}

	uint32_t SetSuperJump(bool toggle)
	{
		if (toggle)
		{
			if (!this) return 0;
			return *(BYTE*)(this + 0x218) |= 1 << 14;;
		}
	}
	Vector3 heading()
	{
		if (!this) return { 0,0 ,0 };
		return *(Vector3*)(this + 0x70);
	}
	Vector3 GetCoordinate()
	{
		if (!this) return Vector3{ 0,0,0 };
		return *(Vector3*)(this + 0x90);
	}
	Vector3 SetCoordinate(Vector3 Cords)
	{
		if (!this) return Vector3{ 0,0,0 };
		return *(Vector3*)(this + 0x90) = Cords;
	}

	Vector3 SetVelocity()
	{
		if (!this) return Vector3{ 0,0,0 };
		return *(Vector3*)(this + 0x320) = Vector3(0, 0, 0);
	}
	float GetHealth()
	{
		if (!this) return 0;
		return *(float*)(this + 0x280);
	}
	float GetArmor()
	{
		if (!this) return 0;
		return *(float*)(this + fivem::Armor);
	}
	float GetMaxHealth()
	{
		if (!this) return 0;
		return *(float*)(this + 0x284);
	}
	float SetHealth(float Health)
	{
		if (!this) return 0;
		return *(float*)(this + 0x280) = Health;
	}

	float SetArmor(float Armor)
	{
		if (!this) return 0;
		return *(float*)(this + fivem::Armor) = Armor;
	}
	float SetMaxHealth()
	{
		if (!this) return 0;
		return *(float*)(this + 0x280) = GetMaxHealth();
	}
	uint32_t GetPedType()
	{
		if (!this) return 0;
		return *(uint32_t*)(this + fivem::EntityType);
	}
	bool IsPedOrFalse()
	{
		if (!this) return 0;
		auto ped_type = this->GetPedType();

		ped_type = ped_type << 11 >> 25;

		if (ped_type != 2)
		{
			return true;
		}
		else
			return false;
	}
	BYTE SetInvisible(BYTE caca)
	{
		if (!this) return 0;
		return *(BYTE*)(this + 0x2C) = caca; // 0X1 ou 0X37
	}

	unsigned char Set_Ragdoll(bool value)
	{
		if (!this) return 0;
		if (value)
		{
			return *(unsigned char*)(this + 0x10B8) = 1;
		}
		else
		{
			return *(unsigned char*)(this + 0x10B8) = 32;
		}
	}
};

class Pedd {
public:
	hk_Ped* Handle;
	int Id;
	int IsPlayer;
	bool IsVisible;
	bool IsInvisible;
	Vector3 Position;
	std::vector<Vector3> Bones;
	Pedd() : Handle(nullptr), Id(0), IsPlayer(0), IsVisible(false), IsInvisible(false) {}
};

class Playerr {
public:
	hk_Ped* Handle;
	int Id;
	int IsPlayer;
	bool IsVisible;
	bool IsInvisible;
	Vector3 Position;
	std::vector<Vector3> Bones;
	std::string Name;
	Playerr() :Handle(nullptr), Id(0), IsPlayer(0), IsVisible(false), IsInvisible(false)  , Name("") {}
};
class hk_ObjectInfo
{
public:
	char* ModelChar()
	{
		if (!this) return 0;
		return (char*)(this + 0x18);
	}
};
class hk_Object
{
public:
	hk_ObjectInfo* ObjectModelInfo()
	{
		if (!this) return 0;
		return (hk_ObjectInfo*)(*(uint64_t*)(this + 0x20));
	}
	Vector3 GetCoordinate()
	{
		if (!this) return Vector3{ 0,0,0 };
		return *(Vector3*)(this + 0x90);
	}
};
class hk_ObjectList
{
public:
	hk_Object* Object(int index)
	{
		if (!this) return 0;
		return (hk_Object*)(*(uint64_t*)(this + (index * 0x10)));
	}
};

class hk_PedList
{
public:
	hk_Ped* Ped(int index)
	{
		if (!this) return 0;
		return (hk_Ped*)(*(uint64_t*)(this + (index * 0x10)));
	}
};

class hk_VehicleList
{
public:
	hk_Vehicle* Vehicle(int index)
	{
		if (!this) return 0;
		return (hk_Vehicle*)(*(uint64_t*)(this + (index * 0x10)));
	}
};
class hk_VehicleInterface
{
public:
	uint64_t VehicleMaximum()
	{
		if (!this) return 0;
		return (uint64_t)(*(uint64_t*)(this + 0x188));
	}

	hk_VehicleList* VehicleList()
	{
		if (!this) return 0;
		return (hk_VehicleList*)(*(uint64_t*)(this + 0x180));
	}
};
class hk_PedInterface
{
public:
	uint64_t PedMaximum()
	{
		if (!this) return 0;
		return (uint64_t)(*(uint64_t*)(this + 0x108));
	}

	hk_PedList* PedList()
	{
		if (!this) return 0;
		return (hk_PedList*)(*(uint64_t*)(this + 0x100));
	}
};

class hk_ObjectInterface
{
public:
	uint64_t ObjectMaximum()
	{
		if (!this) return 0;
		return (uint64_t)(*(uint64_t*)(this + 0x160));
	}

	hk_ObjectList* ObjectList()
	{
		if (!this) return 0;
		return (hk_ObjectList*)(*(uint64_t*)(this + 0x0158));
	}
};
class hk_ReplayInterface
{
public:
	hk_PedInterface* PedInterface()
	{
		if (!this) return 0;
		return (hk_PedInterface*)(*(uint64_t*)(this + 0x18));
	}
	hk_VehicleInterface* VehicleInterface()
	{
		if (!this) return 0;
		return (hk_VehicleInterface*)(*(uint64_t*)(this + 0x10));
	}
	hk_ObjectInterface* ObjectInterface()
	{
		if (!this) return 0;
		return (hk_ObjectInterface*)(*(uint64_t*)(this + 0x28));
	}
};

class hk_World
{
public:
	hk_Ped* LocalPlayer()
	{
		if (!this) return 0;
		return (hk_Ped*)(*(uint64_t*)(this + 0x8));
	}
};
inline std::vector<Playerr> List;
