#include "fiber.hpp"
#include "tick.hpp"
#include <memory.h>

#include "src/fivem/classes/classes.hpp"
#include "src/fivem/features/aimbot.hpp"
#include "src/fivem/features/player.hpp"
#include "src/fivem/features/weapons.hpp"
#include "src/fivem/features/vehicles.hpp"
#include <src/fivem/features/lists.hpp>
#include "src/fivem/native/invoker.hpp"
#include <enums.hpp>
#include <hashes.hpp>
#include "src/detours/detours.h"
bool bWaitingForModelAircraft = true;

bool NeedToSpawn = true;
bool IsModelRequested = false;
bool IsphysModelRequested = false;

bool IsMModelRequested = false;
bool HookMethod = false;
bool ishooked = false;
bool RcCamCreated = false;
bool noclipcreate = false;
bool CamCreated = false;
bool CamDelete = false;
bool HasAnRcCar = false;
bool hooknative = false;
static std::vector<Entity> ents = {};
static PVector3 location;
static PVector3 other;
float dist = 10;
bool trig = false;
int currentTime = 0;
static constexpr double multiplier = 10.0;
float degToRad(float degs)
{
	return degs * 3.141592653589793f / 180.f;
}
static const int scroll = 0;
Entity ent;
Entity RcCar;

Cam camera = -1;
Cam rccamera = -1;

float speedd = 0.5f;
float mult = 0.f;
PVector3 position;
PVector3 rotation;
PVector3 Rcposition;
PVector3 Rcrotation;
static const ControllerInputs controls[] = { ControllerInputs::INPUT_LOOK_LR, ControllerInputs::INPUT_LOOK_UD, ControllerInputs::INPUT_LOOK_UP_ONLY, ControllerInputs::INPUT_LOOK_DOWN_ONLY, ControllerInputs::INPUT_LOOK_LEFT_ONLY, ControllerInputs::INPUT_LOOK_RIGHT_ONLY, ControllerInputs::INPUT_LOOK_LEFT, ControllerInputs::INPUT_LOOK_RIGHT, ControllerInputs::INPUT_LOOK_UP, ControllerInputs::INPUT_LOOK_DOWN };

PVector3 rot_to_direction(PVector3 rot) {
	float x = degToRad(rot.x);
	float z = degToRad(rot.z);

	float num = abs(cos(x));

	return PVector3{ -sin(z) * num, cos(z) * num, sin(x) };
}

void max_vehicle(Vehicle veh)
{
	Hash model = ENTITY::GET_ENTITY_MODEL(veh);

	VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

	VEHICLE::TOGGLE_VEHICLE_MOD(veh, MOD_TURBO, TRUE);
	VEHICLE::TOGGLE_VEHICLE_MOD(veh, MOD_TYRE_SMOKE, TRUE);
	VEHICLE::TOGGLE_VEHICLE_MOD(veh, MOD_XENON_LIGHTS, TRUE);
	VEHICLE::SET_VEHICLE_WINDOW_TINT(veh, 1);
	VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, false);

	for (int slot = MOD_SPOILERS; slot <= MOD_LIGHTBAR; slot++)
	{
		if (slot == MOD_LIVERY)
		{
			continue;
		}

		int count = VEHICLE::GET_NUM_VEHICLE_MODS(veh, slot);
		if (count > 0)
		{
			int selected_mod = -1;

			for (int mod = count - 1; mod >= -1; mod--)
			{

				selected_mod = mod;
				break;
			}

			if (selected_mod != -1)
			{
				VEHICLE::SET_VEHICLE_MOD(veh, slot, selected_mod, true);
			}
		}
	}
}

void max_vehicle_performance(Vehicle veh)
{

	VehicleModType perfomance_mods[] = { MOD_ENGINE, MOD_BRAKES, MOD_TRANSMISSION, MOD_SUSPENSION, MOD_ARMOR, MOD_NITROUS, MOD_TURBO };
	VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

	for (auto mod_slot : perfomance_mods)
	{
		if (mod_slot != MOD_NITROUS && mod_slot != MOD_TURBO)
			VEHICLE::SET_VEHICLE_MOD(veh, mod_slot, VEHICLE::GET_NUM_VEHICLE_MODS(veh, mod_slot) - 1, true);
		else
			VEHICLE::TOGGLE_VEHICLE_MOD(veh, mod_slot, true);
	}

}

bool raycast(Entity* ent)
{
	BOOL hit;
	PVector3 endCoords = PVector3(0, 0, 0);
	PVector3 surfaceNormal = PVector3(0, 0, 0);

	PVector3 camCoords = CAM::GET_GAMEPLAY_CAM_COORD();
	PVector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
	PVector3 dir = rot_to_direction(rot);
	PVector3 farCoords = PVector3(0, 0, 0);

	farCoords.x = camCoords.x + dir.x * 100000;
	farCoords.y = camCoords.y + dir.y * 100000;
	farCoords.z = camCoords.z + dir.z * 100000;

	int ray = WORLDPROBE::_CAST_RAY_POINT_TO_POINT(camCoords.x,
		camCoords.y,
		camCoords.z,
		farCoords.x,
		farCoords.y,
		farCoords.z,
		-1,
		0,
		7);
	WORLDPROBE::GET_SHAPE_TEST_RESULT(ray, &hit, &endCoords, &surfaceNormal, ent);

	return (bool)hit;
}



bool raycastphys(Entity* ent)
{
	BOOL hit;
	PVector3 endCoords = PVector3(0, 0, 0);
	PVector3 surfaceNormal = PVector3(0, 0, 0);

	PVector3 camCoords = position;
	PVector3 rot = rotation;
	PVector3 dir = rot_to_direction(rot);
	PVector3 farCoords = PVector3(0, 0, 0);

	farCoords.x = camCoords.x + dir.x * 100000;
	farCoords.y = camCoords.y + dir.y * 100000;
	farCoords.z = camCoords.z + dir.z * 100000;

	int ray = WORLDPROBE::_CAST_RAY_POINT_TO_POINT(camCoords.x,
		camCoords.y,
		camCoords.z,
		farCoords.x,
		farCoords.y,
		farCoords.z,
		-1,
		0,
		7);
	WORLDPROBE::GET_SHAPE_TEST_RESULT(ray, &hit, &endCoords, &surfaceNormal, ent);

	return (bool)hit;
}
void apply_velocity(Entity e)
{

	if (ENTITY::DOES_ENTITY_EXIST(e))
	{
		NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(e);
		if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_WEAPON_WHEEL_NEXT))
			dist -= 5;
		if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_WEAPON_WHEEL_PREV))
			dist += 5;

		//if (!entity::take_control_of(e))
		//	return; // TODO: remove from vector

		ENTITY::SET_ENTITY_COLLISION(e, false, false);

		other = ENTITY::GET_ENTITY_COORDS(e, true);

		PVector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
		float pitch = degToRad(rot.x); // vertical
		// float roll = rot.y;
		float yaw = degToRad(rot.z + 90); // horizontal

		PVector3 velocity = PVector3(0, 0, 0);

		velocity.x = location.x + (dist * cos(pitch) * cos(yaw)) - other.x;
		velocity.y = location.y + (dist * sin(yaw) * cos(pitch)) - other.y;
		velocity.z = location.z + (dist * sin(pitch)) - other.z;

		ENTITY::SET_ENTITY_VELOCITY(e, velocity.x * (float)multiplier, velocity.y * (float)multiplier, velocity.z * (float)multiplier);
		ENTITY::SET_ENTITY_ALPHA(e, 105, 0);
	}
}



void toClipboard(HWND hwnd, const std::string & s) {
	OpenClipboard(hwnd);
	EmptyClipboard();
	HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, s.size() + 1);
	if (!hg) {
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hg), s.c_str(), s.size() + 1);
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT, hg);
	CloseClipboard();
	GlobalFree(hg);
}

Entity crosshair_catch;
Entity veh_catch;
Entity m_entity;
float m_speed_multiplier;
static constexpr float speed = 1.0f;

typedef __int64(__fastcall* random)(__int64 a1, __int64 a2, Vector3 a3, Vector3 a4, __int64 a5, __int64 a6, __int64 a7, __int64 a8, char a9, int a10, int a11);
typedef __int64(__fastcall* HandleBullet_t)(__int64 BulletPtr, class CWeaponInfo* CWeaponInfo, Vector3 StartPos, Vector3 EndPos, float Range, int weaponHash, char a7, char a8);
HandleBullet_t HandleBullet = nullptr;
random fonteman = nullptr;

bool HasPrintedValue = false;

__int64 ekip(__int64 a1, __int64 a2, Vector3 a3, Vector3  a4, __int64 a5, __int64 a6, __int64 a7, __int64 a8, char a9, int a10, int a11) {

	// edit the position here
	//uintptr_t addr = reinterpret_cast<uintptr_t>(&EndPos.x) - (uintptr_t)GetModuleHandleA(nullptr);
	float first = (a3.x);
	float second = (a3.y);
	float third = (a3.z);
	float fourth = (a3.x);
    std::string azer = "X coords" + std::to_string(first) + "\n Y coords" + std::to_string(second) + "\n Z coords" + std::to_string(third) + "\n Z coords" + std::to_string(fourth);
	//MessageBoxA(NULL, azer.c_str(), "", NULL);
	a4 = Vector3(0,0,0);
	//ImGui::SetClipboardText(std::to_string(addr).c_str());
	//	MessageBoxA(NULL, "Y coords", std::to_string(EndPos.y).c_str(), NULL);
	//	MessageBoxA(NULL, "Z coords", std::to_string(EndPos.z).c_str(), NULL);
	

	return fonteman(a1,a2 ,a3,a4,a5,a6,a7,a8,a9,a10,a11);
}
__int64 mHandleBullet(__int64 BulletPtr, class CWeaponInfo* CWeaponInfo, Vector3 StartPos, Vector3 EndPos, float Range, int weaponHash, bool a7, bool a8) {

	// edit the position here
	//uintptr_t addr = reinterpret_cast<uintptr_t>(&EndPos.x) - (uintptr_t)GetModuleHandleA(nullptr);
	while (!HasPrintedValue) {
    	//MessageBoxA(NULL, "X coords", std::to_string(addr).c_str(), NULL);
	//	ImGui::SetClipboardText(std::to_string(addr).c_str());
	//	MessageBoxA(NULL, "Y coords", std::to_string(EndPos.y).c_str(), NULL);
	//	MessageBoxA(NULL, "Z coords", std::to_string(EndPos.z).c_str(), NULL);
		HasPrintedValue = true;
	}

	EndPos = Vector3(14459,155,12);

	return HandleBullet(BulletPtr, CWeaponInfo, StartPos, EndPos, Range, weaponHash, a7, a8);
}
void on_Tls_Thread() {

	//you are on Tls thread Safe to run native without crash
	if (!fivem::IsOffsetWorking) {
		//	FindOffset();
		fivem::IsOffsetWorking = true;
	}
	if (!hooknative) {
	
		HookNative1();
		hooknative = true;
	}
	aimbot::hook();
	hk_ReplayInterface* ReplayInterface = (hk_ReplayInterface*)*(uint64_t*)(fivem::ReplayInterface);
	if (!ReplayInterface)
		return;

	hk_PedInterface* PedInterface = ReplayInterface->PedInterface();
	if (!PedInterface)
		return;

	for (int index = 0; index < PedInterface->PedMaximum(); index++)
	{
		hk_Ped* Peds = PedInterface->PedList()->Ped(index);
		if (!Peds) continue;
		auto handle = fivem::pointer_to_handle((DWORD64)Peds);
			bool found = false;

			int NetworkGetPlayerIndex = NETWORK::NETWORK_GET_PLAYER_INDEX_FROM_PED(handle);
			std::string Name = PLAYER::GET_PLAYER_NAME(NetworkGetPlayerIndex);



			auto ped_type = Peds->GetPedType();

			if (!ped_type)
			{
				continue;
			}

			bool IsPed = false;

			ped_type = ped_type << 11 >> 25;

			if (ped_type != 2) {

				IsPed = true;

			}
			if (IsPed)
				continue;
			auto it = std::find_if(List.begin(), List.end(), [&](const Playerr& player) {
				return player.Name == Name;
				});
			if (it != List.end()) {
				it->Handle = Peds;
				it->IsPlayer = 1;
			}
			else {
				Playerr pPlayer;
				pPlayer.Name = Name;
				pPlayer.IsPlayer = 1;
				pPlayer.Handle = Peds;
				List.push_back(pPlayer);
			}

				//for (Playerr player : List) {
				////	MessageBoxA(0, player.Name.c_str(),"",0);
				//	if (player.Name == Name) {

				//		player.Handle = Peds;
				//		player.IsPlayer = 1;
				//		found = true;
				//		break;
				//	}
				//	else {
				//	
				//		found = false;

				//	}
				//}
				//if (!found) {
				//	Playerr pPlayer;
				//	pPlayer.Name = Name;
				//	pPlayer.IsPlayer = 1;
				//	pPlayer.Handle = Peds;
				//	List.push_back(pPlayer);
				//}
		


//			List.push_back();

	
	}

	if (settings::self::noclip && settings::self::noclip_type == 1) {
		noclipcreate = true;
		//for (const auto& control : controls)
		//	CONTROLS::DISABLE_CONTROL_ACTION(0, static_cast<int>(control), true);
		const Entity ent = PLAYER::PLAYER_PED_ID();

		const auto location = ENTITY::GET_ENTITY_COORDS(ent,false);

		// cleanup when changing entities
		if (m_entity != ent)
		{
			ENTITY::FREEZE_ENTITY_POSITION(m_entity, false);
			ENTITY::SET_ENTITY_COLLISION(m_entity, true, false);

			m_entity = ent;
		}

		Vector3 vel{};

			// Left Shift
			if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_JUMP))
				vel.z += speed / 2;
			// Left Control
			if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_DUCK))
				vel.z -= speed / 2;
			// Forward
			if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_UP_ONLY))
				vel.y += speed;
			// Backward
			if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_DOWN_ONLY))
				vel.y -= speed;
			// Left
			if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_LEFT_ONLY))
				vel.x -= speed;
			// Right
			if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_RIGHT_ONLY))
				vel.x += speed;
	

		auto rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
		ENTITY::SET_ENTITY_ROTATION(ent, 0.f, rot.y, rot.z, 2, 0);
		ENTITY::SET_ENTITY_COLLISION(ent, false, false);
		if (vel.x == 0.f && vel.y == 0.f && vel.z == 0.f)
		{
			// freeze entity to prevent drifting when standing still
			ENTITY::FREEZE_ENTITY_POSITION(ent, true);
			m_speed_multiplier = 0.f;
		}
		else
		{
			if (m_speed_multiplier < 20.f)
				m_speed_multiplier += 0.15f;

			ENTITY::FREEZE_ENTITY_POSITION(ent, false);

			const auto is_aiming = CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_AIM);
			if (is_aiming)
			{
				vel = vel * 2;

				const auto offset = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ent, vel.x * m_speed_multiplier, vel.y * m_speed_multiplier, vel.z * m_speed_multiplier);

				ENTITY::SET_ENTITY_VELOCITY(ent, 0, 0, 0);
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ent, offset.x, offset.y, offset.z, true, true, true);
			}
			else
			{
				vel = vel * 2;

				const auto offset = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ent, vel.x, vel.y, 0.f);
				vel.x = offset.x - location.x;
				vel.y = offset.y - location.y;

				ENTITY::SET_ENTITY_MAX_SPEED(ent, 999999999999);
				ENTITY::SET_ENTITY_VELOCITY(ent, vel.x * m_speed_multiplier, vel.y * m_speed_multiplier, vel.z * m_speed_multiplier);
			}
		}
	}
	else {
		if (noclipcreate) {
			ENTITY::FREEZE_ENTITY_POSITION(m_entity, false);
			ENTITY::SET_ENTITY_COLLISION(m_entity, true, false);
			noclipcreate = false;
		}
	}
	if (settings::aimbot::triggerbot) {
		if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_AIM))
		{
			if (raycast(&crosshair_catch))
			{
				if (ENTITY::IS_ENTITY_A_PED(crosshair_catch) && !ENTITY::IS_ENTITY_DEAD(crosshair_catch))
				{

					if (settings::aimbot::delay) {

						if (!trig) {
							currentTime = GetTickCount64();
							trig = true;
						}
						else {
							int lastActionTime = GetTickCount64();
							if ((lastActionTime - currentTime) >= settings::aimbot::triggerbot_delay) {
								PVector3 coords = ENTITY::GET_ENTITY_COORDS(crosshair_catch, 1);
								PED::SET_PED_SHOOTS_AT_COORD(PLAYER::PLAYER_PED_ID(), coords.x, coords.y, coords.z, true);
								trig = false;
	
							}
						}
			
					}
					else {

						PVector3 coords = ENTITY::GET_ENTITY_COORDS(crosshair_catch, 1);
						PED::SET_PED_SHOOTS_AT_COORD(PLAYER::PLAYER_PED_ID(), coords.x, coords.y, coords.z, true);
					}
				}// Add check for vehicles, currently only shoots peds not in vehicles
			}
			currentTime = 0;

		}
	}
	if (settings::self::rc_car)
	{

		if (!RcCar) {
			if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_AIM))
			{
				raycast(&veh_catch);
				if (ENTITY::IS_ENTITY_A_VEHICLE(veh_catch))
				{
					RcCar = veh_catch;
					veh_catch = NULL;
				}
			}
		}
		else {

			if (!RcCamCreated) {
				rccamera = CAM::CREATE_CAM((char*)"DEFAULT_SCRIPTED_CAMERA", 1);


				Vehicle Veh = NULL;
				if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
				{
					Veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
				}
				ENTITY::FREEZE_ENTITY_POSITION(Veh, true);
				Rcposition = ENTITY::GET_ENTITY_COORDS(RcCar, false);
				Rcrotation = ENTITY::GET_ENTITY_ROTATION(RcCar, 2);
				CAM::SET_CAM_COORD(rccamera, Rcposition.x, Rcposition.y, Rcposition.z + 5);
				CAM::SET_CAM_ROT(rccamera, Rcrotation.x, Rcrotation.y, Rcrotation.z, 2);
				CAM::SET_CAM_ACTIVE(rccamera, true);
				CAM::RENDER_SCRIPT_CAMS(true, true, 500, true, true);
				RcCamCreated = true;
			}


			Rcposition = ENTITY::GET_ENTITY_COORDS(RcCar, false);
			Rcrotation = ENTITY::GET_ENTITY_ROTATION(RcCar, 2);

			PVector3 dirr = rot_to_direction(Rcrotation);
			PVector3 ffarCoords = PVector3(0, 0, 0);

			ffarCoords.x = Rcposition.x - dirr.x * 6;
			ffarCoords.y = Rcposition.y - dirr.y * 6;
			ffarCoords.z = Rcposition.z - dirr.z * 6;

			float distance = 2;
			float rotationOffset = 180;
			float offsetX = distance * sin(degToRad(Rcrotation.z + rotationOffset));
			float offsetY = distance * cos(degToRad(Rcrotation.z + rotationOffset));
			CAM::SET_CAM_COORD(rccamera, ffarCoords.x, ffarCoords.y, Rcposition.z + 2.5);
			STREAMING::_SET_FOCUS_AREA(ffarCoords.x, ffarCoords.y, Rcposition.z + 3, 0.f, 0.f, 0.f);
			CAM::SET_CAM_ROT(rccamera, Rcrotation.x, Rcrotation.y, Rcrotation.z, 2);

			if (!settings::self::noclip)
			{
				VEHICLE::SET_VEHICLE_ENGINE_ON(RcCar, true, true);
				CONTROLS::DISABLE_ALL_CONTROL_ACTIONS(0);

				for (const auto& control : controls)
					CONTROLS::ENABLE_CONTROL_ACTION(0, static_cast<int>(control), true);
				// Left Shift
		//		if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_SPRINT))
			//		vecChange.z += speedd / 2;
				// Left Control
				//if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_DUCK))
					//vecChange.z -= speedd / 2;
				// Forward
				AI::_CLEAR_VEHICLE_TASKS(RcCar);
				// horn
				if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_HORN))
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(RcCar, 200.0);

				// Forward
				if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_UP_ONLY))
					AI::TASK_VEHICLE_TEMP_ACTION(PLAYER::PLAYER_PED_ID(), RcCar, 32, 2000);
				// Backward
				if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_DOWN_ONLY))
					AI::TASK_VEHICLE_TEMP_ACTION(PLAYER::PLAYER_PED_ID(), RcCar, 22, 2000);
				// Left
				if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_LEFT_ONLY))
					AI::TASK_VEHICLE_TEMP_ACTION(PLAYER::PLAYER_PED_ID(), RcCar, 7, 2000);
				// Right
				if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_RIGHT_ONLY))
					AI::TASK_VEHICLE_TEMP_ACTION(PLAYER::PLAYER_PED_ID(), RcCar, 8, 2000);
			}
			if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_AIM))
			{
				RcCar = NULL;

			}
		}

	}
	else {
		if (RcCamCreated) {
			CAM::SET_CAM_ACTIVE(rccamera, false);
			CAM::RENDER_SCRIPT_CAMS(false, true, 500, true, true);
			CAM::DESTROY_CAM(rccamera, false);
			STREAMING::CLEAR_FOCUS();

			ENTITY::FREEZE_ENTITY_POSITION(rccamera, false);
			RcCamCreated = false;
		}
	}
	if (settings::self::freecam)
	{
		if (!CamCreated) {
			camera = CAM::CREATE_CAM((char*)"DEFAULT_SCRIPTED_CAMERA", 1);

			position = CAM::GET_GAMEPLAY_CAM_COORD();
			rotation = CAM::GET_GAMEPLAY_CAM_ROT(2);
			Vehicle Veh = NULL;
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
			{
				Veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			}
			ENTITY::FREEZE_ENTITY_POSITION(Veh, true);
				ENTITY::FREEZE_ENTITY_POSITION(PLAYER::PLAYER_PED_ID(), true);

			CAM::SET_CAM_COORD(camera, position.x, position.y, position.z);
			CAM::SET_CAM_ROT(camera, rotation.x, rotation.y, rotation.z, 2);
			CAM::SET_CAM_ACTIVE(camera, true);
			CAM::RENDER_SCRIPT_CAMS(true, true, 500, true, true);


			//	memcpy(&freecamoffsetX, (DWORD64*)fivem::PatchX, sizeof(fivem::PatchX));
			//	memcpy(&freecamoffsetY, (DWORD64*)fivem::PatchY, sizeof(fivem::PatchY));
			//	memcpy(&freecamoffsetZ, (DWORD64*)fivem::PatchZ, sizeof(fivem::PatchZ));
			//	*(uint64_t*)(fivem::PatchX) = 0x909090;
			//	*(uint64_t*)(fivem::PatchY) = 0x909090;
			//	*(uint64_t*)(fivem::PatchZ) = 0x909090;

			CamCreated = true;
		}
		CONTROLS::DISABLE_ALL_CONTROL_ACTIONS(0);

		for (const auto& control : controls)
			CONTROLS::ENABLE_CONTROL_ACTION(0, static_cast<int>(control), true);

		Vector3 vecChange = { 0.f, 0.f, 0.f };
		Ped playerPed = PLAYER::PLAYER_PED_ID();


		if (!settings::self::noclip)
		{
			// Left Shift
			if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_SPRINT))
				vecChange.z += speedd / 2;
			// Left Control
			if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_DUCK))
				vecChange.z -= speedd / 2;
			// Forward
			if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_UP_ONLY))
				vecChange.y += speedd;
			// Backward
			if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_DOWN_ONLY))
				vecChange.y -= speedd;
			// Left
			if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_LEFT_ONLY))
				vecChange.x -= speedd;
			// Right
			if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_RIGHT_ONLY))
				vecChange.x += speedd;
		}

		if (vecChange.x == 0.f && vecChange.y == 0.f && vecChange.z == 0.f)
			mult = 0.f;
		else if (mult < 10)
			mult += 0.15f;

		PVector3 rot = CAM::GET_CAM_ROT(camera, 2);

	

			PVector3 dirrr = rot_to_direction(rot);
			PVector3 fffarCoords = PVector3(0, 0, 0);

			fffarCoords.x = position.x + dirrr.x * 1000;
			fffarCoords.y = position.y + dirrr.y * 1000;
			fffarCoords.z = position.z + dirrr.z * 1000;
		//	GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS((position.x), (position.y), (position.z), (fffarCoords.x), (fffarCoords.y), (fffarCoords.z), (int)100, false, 0xB1CA77B1, PLAYER::PLAYER_PED_ID(), true, false, 20.f);
			if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_ATTACK))
			{
				WEAPON::REQUEST_WEAPON_ASSET(0xB1CA77B1, 31, 0);
			}
			switch (settings::self::FreeCamInt) {
			case 0:
				if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_ATTACK))
				{
					GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS((position.x), (position.y), (position.z), (fffarCoords.x), (fffarCoords.y), (fffarCoords.z), (int)100, false, 0xBFE256D4, PLAYER::PLAYER_PED_ID(), true, false, 3.f);
				}
				
				break;
			case 1:
				if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_ATTACK))
				{
				GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS((position.x), (position.y), (position.z), (fffarCoords.x), (fffarCoords.y), (fffarCoords.z), (int)100, false, 0xB1CA77B1, PLAYER::PLAYER_PED_ID(), true, false, 100.f);
				}
				break;
			case 2:
				if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_ATTACK))
				{
				WEAPON::REQUEST_WEAPON_ASSET(0x24B17070, 31, 0);
				
				GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS((position.x), (position.y), (position.z), (fffarCoords.x), (fffarCoords.y), (fffarCoords.z), (int)100, false, 0x24B17070, PLAYER::PLAYER_PED_ID(), true, false, 3.f);
				}
				break;
			case 3:
				if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_ATTACK))
				{
				WEAPON::REQUEST_WEAPON_ASSET(0x45CD9CF3, 31, 0);

				GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS((position.x), (position.y), (position.z), (fffarCoords.x), (fffarCoords.y), (fffarCoords.z), (int)0, false, 0x45CD9CF3, PLAYER::PLAYER_PED_ID(), true, false, 3.f);
				}
				break;
			case 4: // create ped
				if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_ATTACK))
				{
				GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS((position.x), (position.y), (position.z), (fffarCoords.x), (fffarCoords.y), (fffarCoords.z), (int)100, false, 0xBFE256D4, PLAYER::PLAYER_PED_ID(), true, false, 3.f);
				}
				break;
			case 5: // create vehicule

				if (GetAsyncKeyState(VK_LBUTTON) & 0x1)
				{


					auto hashhh = settings::vehicle::vehicle_spawning::VehicleToSpawn;

					if (!IsphysModelRequested) {
						STREAMING::REQUEST_MODEL(hashhh);
						Print("[ PhysGun ] Requested model");

						IsphysModelRequested = true;
					}

				}
				if (IsphysModelRequested)
				{
					Print("[ PhysGun ] left click check");
					Ped playerPed = PLAYER::PLAYER_PED_ID();
					Vehicle playerVeh = NULL;

					auto hashhhhh = settings::vehicle::vehicle_spawning::VehicleToSpawn;
					if (STREAMING::HAS_MODEL_LOADED(hashhhhh))
					{
						PVector3 veh = PVector3(0, 0, 0);

						veh.x = position.x + dirrr.x * 3;
						veh.y = position.y + dirrr.y * 3;
						veh.z = position.z + dirrr.z * 3;
						//	*(unsigned short*)(fivem::modelspawnbypass) = 0x9090;

						playerVeh = VEHICLE::CREATE_VEHICLE(hashhhhh, veh.x, veh.y, veh.z, ENTITY::GET_ENTITY_HEADING(playerPed), false, TRUE);
						Print("[ PhysGun ] Create vehicule");
						//playerVeh = VEHICLE::CREATE_VEHICLE(hashhhhh, camCoords.x, camCoords.y, camCoords.z, ENTITY::GET_ENTITY_HEADING(playerPed), false, TRUE);

						if (settings::vehicle::networked) {
							NETWORK::NetworkRegisterEntityAsNetworked(playerVeh);
						}
						//	*(unsigned short*)(fivem::modelspawnbypass) = 0x0574;
						STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hashhhhh);
						if (settings::vehicle::spawn_maxed)	 {
							max_vehicle(playerVeh);
							max_vehicle_performance(playerVeh);
						}
						IsphysModelRequested = false;

					}
				}
		
	
			
			
			break;
			case 6: // PHYS GUN 


				PVector3 playerPos = position;
				auto is_zoomed_in = CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_AIM);

				short rightMouseButtonState = GetAsyncKeyState(VK_RBUTTON);
				if (rightMouseButtonState & 0x8000 && is_zoomed_in)
				{
					if (ent == NULL)
					{
						if (raycastphys(&ent))
						{
							if (ent)
								AI::SET_HIGH_FALL_TASK(ent, 0, 0, 0);
							if (ENTITY::IS_ENTITY_A_PED(ent))
							{
								ent = NULL;
							}

						}
					}
				}
				else
				{
					if (ent) {
						dist = 10;
						ENTITY::SET_ENTITY_COLLISION(ent, true, true);
						ENTITY::RESET_ENTITY_ALPHA(ent);

						ent = NULL;
					}
				}
				location = playerPos;
				other = ENTITY::GET_ENTITY_COORDS(ent, true);

				apply_velocity(ent);


				break;
			
		//	GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS((position.x), (position.y), (position.z), (fffarCoords.x), (fffarCoords.y), (fffarCoords.z), (int)100, false, 0xBFE256D4, PLAYER::PLAYER_PED_ID(), true, false, 3.f);

		}

		//float pitch = math::deg_to_rad(rot.x); // vertical
		//float roll = rot.y;
		float yaw = degToRad(rot.z); // horizontal

		position.x += (vecChange.x * cos(yaw) - vecChange.y * sin(yaw)) * mult;
		position.y += (vecChange.x * sin(yaw) + vecChange.y * cos(yaw)) * mult;
		position.z += vecChange.z * mult;

		//	DWORD64 addr = fivem::GetCamera();

		//	*(Vector3*)(addr + 0x60) = Vector3(position.x, position.y, position.x);
		CAM::SET_CAM_COORD(camera, position.x, position.y, position.z);
		STREAMING::_SET_FOCUS_AREA(position.x, position.y, position.z, 0.f, 0.f, 0.f);

		rotation = CAM::GET_GAMEPLAY_CAM_ROT(2);
		CAM::SET_CAM_ROT(camera, rotation.x, rotation.y, rotation.z, 2);
	}
	else {
		if (CamCreated) {
			Ped playerPed = PLAYER::PLAYER_PED_ID();

			CAM::SET_CAM_ACTIVE(camera, false);
			CAM::RENDER_SCRIPT_CAMS(false, true, 500, true, true);
			CAM::DESTROY_CAM(camera, false);
			STREAMING::CLEAR_FOCUS();
			Vehicle Veh = NULL;
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
			{
				Veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			}
			ENTITY::FREEZE_ENTITY_POSITION(Veh, false);
			ENTITY::FREEZE_ENTITY_POSITION(PLAYER::PLAYER_PED_ID(), false);
			ENTITY::FREEZE_ENTITY_POSITION(camera, false);

			CamCreated = false;
		}
	}
	if (settings::self::physic_gun)
	{
		Ped playerPed = PLAYER::PLAYER_PED_ID();
		PVector3 playerPos = ENTITY::GET_ENTITY_COORDS(playerPed, FALSE);
		auto is_zoomed_in = CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_AIM);

		short rightMouseButtonState = GetAsyncKeyState(VK_RBUTTON);
		if (rightMouseButtonState & 0x8000 && is_zoomed_in)
		{
			if (ent == NULL)
			{
				if (raycast(&ent))
				{
					if (ent)
						AI::SET_HIGH_FALL_TASK(ent, 0, 0, 0);
					if (ENTITY::IS_ENTITY_A_PED(ent))
					{
						ent = NULL;
					}

				}
			}
		}
		else
		{
			if (ent) {
				dist = 10;
				ENTITY::SET_ENTITY_COLLISION(ent, true, true);
				ENTITY::RESET_ENTITY_ALPHA(ent);

				ent = NULL;
			}
		}
		location = playerPos;
		other = ENTITY::GET_ENTITY_COORDS(ent, true);

		apply_velocity(ent);
	}

	player::self();
	weapon::weapon_modification();
	weapon::weapon_spawning();
	lists::vehicle_native_option();
	vehicle::vehicle_modifications();


	if (settings::self::model_changer::ModelChange) {
		Ped playerPed = PLAYER::PLAYER_PED_ID();
		Vehicle Veh = NULL;
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
		{
			Veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
		}

		auto hhash = settings::self::model_changer::ModelJoat;
		if (!IsModelRequested) {
			STREAMING::REQUEST_MODEL(hhash);

			IsModelRequested = true;
		}
		else
		{
			if (STREAMING::HAS_MODEL_LOADED(hhash))
			{
				PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), hhash);
				if (Veh != NULL)
				{
					PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Veh, -1);
				}
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hhash);
				IsModelRequested = false;

				settings::self::model_changer::ModelChange = false;
			}
		}

	}
	if (settings::vehicle::spawnvehicule) {
		Ped playerPed = PLAYER::PLAYER_PED_ID();
		Vehicle playerVeh = NULL;

		auto hash = settings::vehicle::vehicle_spawning::VehicleToSpawn;
		if (!IsModelRequested) {
			STREAMING::REQUEST_MODEL(hash);

			IsModelRequested = true;
		}
		else
		{
			if (STREAMING::HAS_MODEL_LOADED(hash))
			{
				PVector3 playerPosition = ENTITY::GET_ENTITY_COORDS(playerPed, FALSE);
			//	*(unsigned short*)(fivem::modelspawnbypass) = 0x9090;

				playerVeh = VEHICLE::CREATE_VEHICLE(hash, playerPosition.x, playerPosition.y, playerPosition.z, ENTITY::GET_ENTITY_HEADING(playerPed), false, TRUE);
				if (settings::vehicle::networked) {
					NETWORK::NetworkRegisterEntityAsNetworked(playerVeh);
				}
			//	*(unsigned short*)(fivem::modelspawnbypass) = 0x0574;
				PED::SET_PED_INTO_VEHICLE(playerPed, playerVeh, SEAT_DRIVER);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
				if (settings::vehicle::spawn_maxed) {
					max_vehicle(playerVeh);
					max_vehicle_performance(playerVeh);
				}
				IsModelRequested = false;

				settings::vehicle::spawnvehicule = false;
			}
		}

	}


	tick::pNativeInvoker.on_tick();

	Fiber::Instance().GameFiber->wait(1);
}

void Fiber::Call()
{
	//Log::Msg("[+]Initializing GameFiber...");

	this->GameFiber = std::make_unique<fiber::GameFiber_Task>(nullptr, on_Tls_Thread);
}

