#pragma once

#include "../classes/classes.hpp"
#include "../includes/includes.hpp"
#include "../settings.hpp"

#include "../native/invoker.hpp"

#include <cmath>
#include "../../../console_log.hpp"
float ApplyCurve(float x, float curve)
{
	return std::pow(x, curve);
}

bool NeedToDisable = false;
bool IsDisabled = false;
bool IsOnFOV = false;

bool shooting = false;

inline bool IsVisible(DWORD64 pPed, DWORD64 Peddd) {
	auto handle = fivem::pointer_to_handle(pPed);
	auto handle1 = fivem::pointer_to_handle(Peddd);
	if (ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(handle1, handle, 17)) {
		return true;
	}
	return false;
}

inline bool Invisible(DWORD64 pPed) {
	auto handle = fivem::pointer_to_handle(pPed);
	if (ENTITY::IS_ENTITY_VISIBLE(handle)) {
		return true;
	}
	return false;
}

namespace aimbot {
	uintptr_t GetDistancePlayer() {
		uintptr_t ClosestPlayer = 0;
		float closestdist = FLT_MAX;
		float dist;
		hk_World* World = (hk_World*)*(uint64_t*)(fivem::World);
		if (!World)
			return NULL;

		hk_Ped* LocalPlayer = World->LocalPlayer();
		if (!LocalPlayer)
			return NULL;

		hk_ReplayInterface* ReplayInterface = (hk_ReplayInterface*)*(uint64_t*)(fivem::ReplayInterface);
		if (!ReplayInterface)
			return NULL;

		hk_PedInterface* PedInterface = ReplayInterface->PedInterface();
		if (!PedInterface)
			return NULL;

		for (int index = 0; index < PedInterface->PedMaximum(); index++) {
			hk_Ped* Peds = PedInterface->PedList()->Ped(index);
			if (!Peds)
				continue;

			if (Peds == LocalPlayer)
				continue;

			if (Peds->GetHealth() <= 0)
				continue;

			if (settings::aimbot::only_visible) {
				if (IsVisible((DWORD64)LocalPlayer, (DWORD64)Peds))
				{
				}
				else
				{
					continue;
				}
			}

			if (settings::aimbot::avoid_invisible) {
				if (Invisible((DWORD64)Peds))
				{
				}
				else
				{
					continue;
				}
			}

			if (settings::aimbot::avoid_target_friend) {
				void* addr = (void*)(Peds->PlayerInfo() + 0x20);
				const char* caca = fivem::GetPlayerNamess(addr);

				auto it = std::find(fivem::Friend.begin(), fivem::Friend.end(), caca);

				if (it != fivem::Friend.end())
					continue;
			}
			else {
			}

			if (settings::aimbot::aimbot_target == 1) {
				auto ped_type = Peds->GetPedType();
				if (!ped_type)
					continue;
				ped_type = ped_type << 11 >> 25;

				if (ped_type != 2) {
					continue;
				}
			}

			if (settings::aimbot::aimbot_target == 2) {
				auto ped_type = Peds->GetPedType();
				if (!ped_type)
					continue;

				ped_type = ped_type << 11 >> 25;

				if (ped_type == 2) {
					continue;
				}
			}

			Vector3 DistanceCalculation = (LocalPlayer->GetCoordinate() - Peds->GetCoordinate());
			double Distance = sqrtf(DistanceCalculation.x * DistanceCalculation.x + DistanceCalculation.y * DistanceCalculation.y + DistanceCalculation.z * DistanceCalculation.z);

			if (Distance <= settings::aimbot::aimbot_distance) {
				ImVec2 PedPos = fivem::WorldToScreen(Peds->GetCoordinate());

				ImVec2 Head = fivem::GetBonePosMatrixW2S(reinterpret_cast<uint64_t>(Peds), 0);
				if (!IsOnScreen(Head))
					continue;

				ImVec2 middle = ImVec2(fivem::WindowSize.x / 2, fivem::WindowSize.y / 2);
				dist = fivem::pythag(middle, Head);

				if (dist < closestdist) {
					{
						closestdist = dist;
						ClosestPlayer = reinterpret_cast<uint64_t>(Peds);
					}
				}
			}
		}
		return ClosestPlayer;
	}
	float get_distance(Vector3 pointA, Vector3 pointB) {
		float x_ba = (float)(pointB.x - pointA.x);
		float y_ba = (float)(pointB.y - pointA.y);
		float z_ba = (float)(pointB.z - pointA.z);
		float y_2 = y_ba * y_ba;
		float x_2 = x_ba * x_ba;
		float sum_2 = y_2 + x_2;
		return (float)sqrtf(sum_2 + z_ba);
	}
	PVector3 ToPVector3(Vector3 pVec)
	{
		return PVector3(pVec.x, pVec.y, pVec.z);
	}

	Vector3 ToVector3(PVector3 pVec)
	{
		return Vector3(pVec.x, pVec.y, pVec.z);
	}
	void SilentVec(Vector3 point)
	{
		hk_World* World = (hk_World*)*(uint64_t*)(fivem::World);
		hk_Ped* LocalPlayer = World->LocalPlayer();

		//hk_WeaponManager* LocalPlayerWeaponManager = LocalPlayer->WeaponManager();
	    //hk_WeaponInfo* LocalPlayerWeaponInfo = LocalPlayerWeaponManager->WeaponInfo();
		//uint64_t WeaponHash = LocalPlayerWeaponInfo->GetHash();
		auto player = PLAYER::PLAYER_PED_ID();
		auto WeaponHash = WEAPON::GET_SELECTED_PED_WEAPON(player);
		auto WeaponDamage = WEAPON::GET_WEAPON_DAMAGE(WeaponHash, NULL);
		const Entity ent = PLAYER::PLAYER_PED_ID();
		uintptr_t entity = reinterpret_cast<uint64_t>(LocalPlayer);
		auto bone_pos = fivem::GetBonePosMatrix(entity, 0);

		if (settings::aimbot::aimbot_type == 2 && GetDistancePlayer() != NULL && SAFE_CALL(GetAsyncKeyState)(VK_LBUTTON) & 0x8000) {

			/*if (GetDistancePlayer() != NULL)
			{
				PED::SET_PED_SHOOTS_AT_COORD(PLAYER::PLAYER_PED_ID(), point.x, point.y, point.z, true);

			}*/
			//WEAPON::REQUEST_WEAPON_ASSET(WeaponHash, 31, 0);
			auto targetHandle = fivem::pointer_to_handle((DWORD64)LocalPlayer);

			if (settings::aimbot::only_visible) {
				//PED::SET_PED_SHOOT_RATE(targetHandle, 1000);
				if (IsVisible((DWORD64)LocalPlayer, entity) && WEAPON::IS_PED_WEAPON_READY_TO_SHOOT(player))
					PED::SET_PED_SHOOTS_AT_COORD(targetHandle, point.x, point.y, point.z, true);
				//PED::SET_PED_SHOOT_RATE(targetHandle, 1000);
			}
			else {
				if(WEAPON::IS_PED_WEAPON_READY_TO_SHOOT(player))
				PED::SET_PED_SHOOTS_AT_COORD(targetHandle, point.x, point.y, point.z, true);

			}

			/*Print("tabarnac");

			const auto weapon_entity = WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(ent);
			if (!weapon_entity)
				return;
			Print("entity weapon get");

			PVector3 dim_min;
			PVector3 dim_max;
			GAMEPLAY::GET_MODEL_DIMENSIONS(ENTITY::GET_ENTITY_MODEL(weapon_entity), &dim_min, &dim_max);
			const auto dimensions = (dim_max - dim_min) * 0.5f;
			const auto weapon_position =
				ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(weapon_entity, dimensions.x, 0, dimensions.z * 0.3f);
			PVector3 PosPed = ENTITY::GET_ENTITY_COORDS(ent, false);
			GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS((dimensions.x), (dimensions.y), (dimensions.z), (point.x), (point.y ), (point.z ), (int)WeaponDamage, false, WeaponHash, player, true, false, 3.f);*/
			Print("[ AIMBOT ] Silent - shot bullet");
			/*		if (SAFE_CALL(GetAsyncKeyState)(0x01) & 0x8000) {

					PED::SET_PED_SHOOTS_AT_COORD(PLAYER::PLAYER_PED_ID(), Out.x, (Out.y + 0.1f), (Out.z + 0.1f), true);
					}*/

		}

		if (GetDistancePlayer() != NULL && PED::IS_PED_SHOOTING(player))
		{
			hk_Ped* PedC = (hk_Ped*)GetDistancePlayer();
		
			Vector3 playerPosition = PedC->GetCoordinate();
			Vector3 LocalPos = LocalPlayer->GetCoordinate();

			Vector3 heading = PedC->heading();
			//auto startpos = point + heading;
			//auto endpos = point - heading;


			Vector3 startpos = Vector3(playerPosition.x , playerPosition.y , playerPosition.z );
			Vector3 endpos = Vector3(playerPosition.x , playerPosition.y , playerPosition.z );

			auto Out = PedC->GetCoordinate();
		    if (settings::aimbot::aimbot_type == 3 ) 
			{
				Print("[ AIMBOT ] Magic - shot bullet");

				GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS( (point.x + heading.x), (point.y + heading.y), (point.z + heading.z) , (point.x - heading.x), (point.y - heading.y ), (point.z + heading.z), (int)WeaponDamage, false, WeaponHash, player, true, false, 3.f);

			}
	



		}
	}
	void AimVec(Vector3 point) {
		DWORD64 addr = fivem::GetCamera();
		if (addr)
		{

			Vector3 CrosshairPos = *(Vector3*)(addr + 0x60);
			Vector3 caca(CrosshairPos.x - point.x, CrosshairPos.y - point.y, CrosshairPos.z - point.z);
			float distance = caca.Length();
			hk_World* World = (hk_World*)*(uint64_t*)(fivem::World);
			hk_Ped* LocalPlayer = World->LocalPlayer();

	

			auto deltaTime = ImGui::GetIO().Framerate / 2;
			uint64_t CamData = *(DWORD64*)(addr + 0x10);
			if (CamData != NULL)
			{
				if (LocalPlayer->IsInAVehicule()) {

					if (*(float*)(CamData + 0x2AC) == -2)
					{
						*(float*)(CamData + 0x2AC) = 0.0f;
						*(float*)(CamData + 0x2C0) = 111.0f;
						*(float*)(CamData + 0x2C4) = 111.0f;
					}
				}
				else {

					if (*(float*)(CamData + 0x130) == 8.0f)
					{
						*(float*)(CamData + 0x130) = 111.0f;
						*(float*)(CamData + 0x134) = 111.0f;
						*(float*)(CamData + 0x4CC) = 0.0f;

						if (*(float*)(CamData + 0x49C) == 1.0f)
							*(float*)(CamData + 0x49C) = 0.0f;

						*(float*)(CamData + 0x2AC) = 0.0f;
						*(float*)(CamData + 0x2B0) = 0.0f;
					}

				}
			}
			float threshold = 0.5f / (settings::aimbot::aimbot_smooth * 20);
			Vector3 Out = Vector3((point.x - CrosshairPos.x) / distance, (point.y - CrosshairPos.y) / distance, (point.z - CrosshairPos.z) / distance);

			if (settings::aimbot::aimbot_smooth <= 1)
			{
				*(Vector3*)(addr + 0x40) = Out;  //FPS
				*(Vector3*)(addr + 0x3D0) = Out; //TPS
			}
			else
			{
				float curve = settings::aimbot::curve; // Récupérer la valeur de la courbe depuis les paramètres.

				{
					Vector3 angles = *(Vector3*)(addr + 0x40);
					float delta_x = Out.x - angles.x;
					if (std::abs(delta_x) > threshold)
					{
						if (angles.x > Out.x)
							*(float*)(addr + 0x40 + 0x0) -= ApplyCurve(std::abs(delta_x), curve) * threshold;
						else if (angles.x < Out.x)
							*(float*)(addr + 0x40 + 0x0) += ApplyCurve(std::abs(delta_x), curve) * threshold;
					}

					float delta_y = Out.y - angles.y;
					if (std::abs(delta_y) > threshold)
					{
						if (angles.y > Out.y)
							*(float*)(addr + 0x40 + 0x4) -= ApplyCurve(std::abs(delta_y), curve) * threshold;
						else if (angles.y < Out.y)
							*(float*)(addr + 0x40 + 0x4) += ApplyCurve(std::abs(delta_y), curve) * threshold;
					}

					float delta_z = Out.z - angles.z;
					if (std::abs(delta_z) > threshold)
					{
						if (angles.z > Out.z)
							*(float*)(addr + 0x40 + 0x8) -= ApplyCurve(std::abs(delta_z), curve) * threshold;
						else if (angles.z < Out.z)
							*(float*)(addr + 0x40 + 0x8) += ApplyCurve(std::abs(delta_z), curve) * threshold;
					}
				}

				{
					Vector3 angles = *(Vector3*)(addr + 0x3D0);
					float delta_x = Out.x - angles.x;
					if (std::abs(delta_x) > threshold)
					{
						if (angles.x > Out.x)
							*(float*)(addr + 0x3D0 + 0x0) -= ApplyCurve(std::abs(delta_x), curve) * threshold;
						else if (angles.x < Out.x)
							*(float*)(addr + 0x3D0 + 0x0) += ApplyCurve(std::abs(delta_x), curve) * threshold;
					}

					float delta_y = Out.y - angles.y;
					if (std::abs(delta_y) > threshold)
					{
						if (angles.y > Out.y)
							*(float*)(addr + 0x3D0 + 0x4) -= ApplyCurve(std::abs(delta_y), curve) * threshold;
						else if (angles.y < Out.y)
							*(float*)(addr + 0x3D0 + 0x4) += ApplyCurve(std::abs(delta_y), curve) * threshold;
					}

					float delta_z = Out.z - angles.z;
					if (std::abs(delta_z) > threshold)
					{
						if (angles.z > Out.z)
							*(float*)(addr + 0x3D0 + 0x8) -= ApplyCurve(std::abs(delta_z), curve) * threshold;
						else if (angles.z < Out.z)
							*(float*)(addr + 0x3D0 + 0x8) += ApplyCurve(std::abs(delta_z), curve) * threshold;
					}
				}
			}
		}
	}

	void do_aimbot(uintptr_t entity) {
		auto get_distance = [](double x1, double y1, double x2, double y2) {
			return sqrtf(pow(x2 - x1, 2.0) + pow(y2 - y1, 2.0));
		};
		auto bone_pos = fivem::GetBonePosMatrixW2S(entity, 0);
		auto bone_posss = fivem::GetBonePosMatrix(entity, 0);

		// Vec3 bone_postest = GetBonePos(entity, SKEL_Head);
		auto center_x = (ImGui::GetIO().DisplaySize.x / 2.f);
		auto center_y = (ImGui::GetIO().DisplaySize.y / 2.f);
		if (bone_pos.x < 0 || bone_pos.x > fivem::WindowSize.x || bone_pos.y < 0 || bone_pos.y > fivem::WindowSize.y)
			return;

		switch (settings::aimbot::aimbot_bone) {
		case 0:
			// bone_pos = FiveM::GetBonePosW2S(entity, SKEL_Head);
			break;
		case 1:
			bone_pos = fivem::GetBonePosMatrixW2S(entity, 7);
			break;
		case 2:
			bone_pos = fivem::GetBonePosMatrixW2S(entity, 8);
			break;
		case 3:
			bone_pos = fivem::GetBonePosMatrixW2S(entity, 1);
			break;
		case 4:
			bone_pos = fivem::GetBonePosMatrixW2S(entity, 2);
			break;
		case 5:
			bone_pos = fivem::GetBonePosMatrixW2S(entity, 5);
			break;
		case 6:
			bone_pos = fivem::GetBonePosMatrixW2S(entity, 6);
			break;
		case 7:
			bone_pos = fivem::GetBonePosMatrixW2S(entity, 0x9995);
			break;
		}

		ImVec2 screen = bone_pos;

		if (settings::aimbot::prediction) {
			Vector3 Velo = ENTITY::GET_ENTITY_VELOCITY(fivem::pointer_to_handle((DWORD64)entity));
			screen = fivem::WorldToScreen(Vector3(bone_posss.x + (Velo.x * 2), bone_posss.y + (Velo.y * 2), bone_posss.z + (Velo.z * 2)));
		}

		float ScreenLocX = bone_pos.x - center_x;
		float ScreenLocY = bone_pos.y - center_y;

		float AimLocX = ScreenLocX /= settings::aimbot::aimbot_smooth + 1.5f;
		float AimLocY = ScreenLocY /= settings::aimbot::aimbot_smooth + 1.5f;

		float TargetX = 0.f;
		float TargetY = 0.f;

		if (AimLocX > center_x) {
			TargetX = -(center_x - AimLocX);
			if (TargetX + center_x > center_x * 2)
				TargetX = 0;
		}
		else {
			TargetX = AimLocX - center_x;
			if (TargetX + center_x < 0)
				TargetX = 0;
		}

		if (AimLocY > center_y) {
			TargetY = -(center_y - AimLocY);
			if (TargetY + center_y > center_y * 2)
				TargetY = 0;
		}
		else {
			TargetY = AimLocY - center_y;
			if (TargetY + center_y < 0)
				TargetY = 0;
		}

		if (settings::visuals::preview_target) {
			if (settings::visuals::preview_style == 0) {
				ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(bone_pos.x, bone_pos.y), 2, settings::visuals::preview_target_colors, 100);
			}

			if (settings::visuals::preview_style == 1) {
				ImGui::GetBackgroundDrawList()->AddLine(ImVec2(fivem::WindowSize.x / 2, fivem::WindowSize.y / 2), ImVec2(bone_pos.x, bone_pos.y), settings::visuals::preview_target_colors);
			}

			if (settings::visuals::preview_style == 2) {
				ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(bone_pos.x, bone_pos.y), 2, settings::visuals::preview_target_colors, 100);

				ImGui::GetBackgroundDrawList()->AddLine(ImVec2(fivem::WindowSize.x / 2, fivem::WindowSize.y / 2), ImVec2(bone_pos.x, bone_pos.y), settings::visuals::preview_target_colors);
			}
		}

		ImVec2 Screen_middle = ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2);

		if (fivem::pythag(Screen_middle, bone_pos) <= settings::aimbot::aimbot_fov * 10) {
			mouse_event(MOUSEEVENTF_MOVE, static_cast<DWORD>(AimLocX), static_cast<DWORD>(AimLocY), 0, 0);
		}
	}

	void hook(void) {
		if (settings::aimbot::enabled) {
			if (SAFE_CALL(GetAsyncKeyState)(settings::aimbot::hotkey) & 0x8000) {


				if (settings::aimbot::aimbot_type == 0) {
					uintptr_t pCPed = GetDistancePlayer();
					if (!pCPed)
						return;

					do_aimbot(pCPed);
				}
				else if (settings::aimbot::aimbot_type == 1) {
					auto get_distance = [](double x1, double y1, double x2, double y2) {
						return sqrtf(pow(x2 - x1, 2.0) + pow(y2 - y1, 2.0));
					};

					auto center_x = fivem::WindowSize.x / 2;
					auto center_y = fivem::WindowSize.y / 2;

					uintptr_t entity = GetDistancePlayer();
					if (!entity)
						return;
					auto bone_pos = fivem::GetBonePosMatrix(entity, 0);

					switch (settings::aimbot::aimbot_bone) {
					case 1:
						bone_pos = fivem::GetBonePosMatrix(entity, 7);
						break;
					case 2:
						bone_pos = fivem::GetBonePosMatrix(entity, 8);
						break;
					case 3:
						bone_pos = fivem::GetBonePosMatrix(entity, 1);
						break;
					case 4:
						bone_pos = fivem::GetBonePosMatrix(entity, 2);
						break;
					case 5:
						bone_pos = fivem::GetBonePosMatrix(entity, 5);
						break;
					case 6:
						bone_pos = fivem::GetBonePosMatrix(entity, 6);
						break;
					}

					ImVec2 screen = fivem::WorldToScreen(bone_pos);

					auto fov = get_distance(center_x, center_y, screen.x, screen.y);
					if (settings::aimbot::prediction) {
						hk_Ped* best_target = (hk_Ped*)GetDistancePlayer();
						Vector3 velocity = { 0,0,0 };
						auto vehicle = best_target->VehicleManager();
						if (vehicle)
							velocity = vehicle->GetVelocity();
	
						auto deltaTime = ImGui::GetIO().Framerate / 2;
						bone_pos += (velocity / deltaTime);
					}

					if (fov < settings::aimbot::aimbot_fov * 10) {
						AimVec(bone_pos);
					}
				}
				else if (settings::aimbot::aimbot_type >= 2 ) {
					auto get_distance = [](double x1, double y1, double x2, double y2) {
						return sqrtf(pow(x2 - x1, 2.0) + pow(y2 - y1, 2.0));
					};

					auto center_x = fivem::WindowSize.x / 2;
					auto center_y = fivem::WindowSize.y / 2;

					uintptr_t entity = GetDistancePlayer();
					if (!entity)
						return;
					auto bone_pos = fivem::GetBonePosMatrix(entity, 0);

					switch (settings::aimbot::aimbot_bone) {
					case 1:
						bone_pos = fivem::GetBonePosMatrix(entity, 7);
						break;
					case 2:
						bone_pos = fivem::GetBonePosMatrix(entity, 8);
						break;
					case 3:
						bone_pos = fivem::GetBonePosMatrix(entity, 1);
						break;
					case 4:
						bone_pos = fivem::GetBonePosMatrix(entity, 2);
						break;
					case 5:
						bone_pos = fivem::GetBonePosMatrix(entity, 5);
						break;
					case 6:
						bone_pos = fivem::GetBonePosMatrix(entity, 6);
						break;
					}
					ImVec2 screen = fivem::WorldToScreen(bone_pos);

					auto fov = get_distance(center_x, center_y, screen.x, screen.y);

					if (fov < settings::aimbot::aimbot_fov * 10) {
						SilentVec(bone_pos);
					}
				}


			}
		}
	}
} // namespace Aimbot