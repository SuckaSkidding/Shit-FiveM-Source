#pragma once

#pragma warning(disable : 4996)

#include "../classes/classes.hpp"
#include "../settings.hpp"
#include "../native/invoker.hpp"



int spacing_up = 0;
int spacing_down = 0;
int spacing_car = 0;
int spacing_boat = 0;
int spacing_heli = 0;

using namespace std;

inline bool VisibleCheck(DWORD64 pPed, DWORD64 Peddd) {


	auto handle = fivem::pointer_to_handle(pPed);
	auto handle1 = fivem::pointer_to_handle(Peddd);
	if (ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(handle1, handle, 17)) {

		return true;
	}
	return false;
}

inline bool Visible(DWORD64 pPed) {

	auto handle = fivem::pointer_to_handle(pPed);
	if (ENTITY::IS_ENTITY_VISIBLE(handle)) {

		return true;
	}

	return false;
}

bool invisible_special_colors = false;

namespace visuals {

	void player_esp(void) {

		if (settings::visuals::enabled) {


	
			hk_World* World = (hk_World*)*(uint64_t*)(fivem::World);
			if (!World)
				return;

			hk_Ped* LocalPlayer = World->LocalPlayer();
			if (!LocalPlayer)
				return;

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

				if (LocalPlayer->GetHealth() <= 100)
					continue;

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

				if (settings::visuals::hitsound) {

					bool damaged = false;
					damaged = ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(fivem::pointer_to_handle((DWORD64)Peds), PLAYER::PLAYER_PED_ID(), 1);
					if (damaged) {

						wchar_t wtext[50];
						mbstowcs(wtext, settings::visuals::hitsound_path, strlen(settings::visuals::hitsound_path) + 1);
						LPWSTR ptr = wtext;

						PlaySoundW((wtext), NULL, SND_FILENAME | SND_ASYNC);
						damaged = false;
					}

				}

				if (settings::visuals::friend_visuals) {

					if (settings::visuals::friend_visuals_check_type == 0) {

						void* addr = (void*)(Peds->PlayerInfo() + 0x20);
						const char* caca = "ccaca";

						auto it = std::find(fivem::Friend.begin(), fivem::Friend.end(), caca);

						if (it != fivem::Friend.end())
							continue;

					}

				}

				bool is_friends = false;

				if (settings::visuals::friend_visuals_check_type == 1) {

					void* addr = (void*)(Peds->PlayerInfo() + 0x20);
					const char* caca = "ccaca";

					auto it = std::find(fivem::Friend.begin(), fivem::Friend.end(), caca);

					if (it != fivem::Friend.end())
						is_friends = true;

				}

				if (!settings::visuals::draw_peds) {

					if (IsPed) {

						continue;

					}

				}


				if (!settings::visuals::draw_self) {

					if (Peds == LocalPlayer) {

						continue;

					}

				}

				if (settings::visuals::only_alive) {

					if (Peds->GetHealth() < 100) {

						continue;

					}

				}

				if (settings::visuals::visible_check) {

					if (settings::visuals::visible_check_type == 0) {

						if (!VisibleCheck((DWORD64)LocalPlayer, (DWORD64)Peds)) {

							continue;

						}

					}

				}

				if (settings::visuals::invisible_check) {

					if (settings::visuals::invisible_check_type == 0) {

						if (!Visible((DWORD64)Peds)) {

							continue;

						}

					}

				}

				ImVec2 Ped_Location = fivem::WorldToScreen(Peds->GetCoordinate());
				if (!IsOnScreen(Ped_Location)) continue;

				Vector3 DistanceCalculation = (LocalPlayer->GetCoordinate() - Peds->GetCoordinate());

				int Distance = sqrtf(DistanceCalculation.x * DistanceCalculation.x + DistanceCalculation.y * DistanceCalculation.y + DistanceCalculation.z * DistanceCalculation.z);;

				if (Distance < settings::visuals::esp_distance) {

					float Height = 0;
					float Width = 0;
					float HealthDistance = 0;

					if (settings::visuals::esp_type == 0) {

						int bone_positions[][2] = {

							{ 0, 7 },
							{ 7, 6 },
							{ 7, 5 },
							{ 7, 8 },
							{ 8, 3 },
							{ 8, 4 }

						};

						uint64_t PedInt = reinterpret_cast<uint64_t>(Peds);
						ImVec2 Head = fivem::GetBoneArrayW2SPos(PedInt, bone_positions[0][0]);
						ImVec2 Left_Foot = fivem::GetBoneArrayW2SPos(PedInt, bone_positions[4][1]);
						ImVec2 Right_Foot = fivem::GetBoneArrayW2SPos(PedInt, bone_positions[5][1]);

						float Foot_Middle = (Left_Foot.y + Right_Foot.y) / 2.f;
						Height = abs(Head.y - Foot_Middle) * 1.35f;
						Width = (Height / settings::visuals::box_size);
						HealthDistance = Width / 16;

					}

					if (settings::visuals::esp_type == 1) {

						Vector3 mins = Peds->PedModelInfo()->GetMin();
						Vector3 maxs = Peds->PedModelInfo()->GetMax();

						Vector3 min = (Peds->GetCoordinate() + mins);
						Vector3 max = (Peds->GetCoordinate() + maxs);
						Vector3 points[] = {
								Vector3(min.x, min.y, min.z),
								Vector3(min.x, max.y, min.z),
								Vector3(max.x, max.y, min.z),
								Vector3(max.x, min.y, min.z),
								Vector3(max.x, max.y, max.z),
								Vector3(min.x, max.y, max.z),
								Vector3(min.x, min.y, max.z),
								Vector3(max.x, min.y, max.z)
						};

						ImVec2 w2s_points[8];
						auto index = 0;
						for (Vector3 point : points) {
							w2s_points[index] = fivem::WorldToScreen(point);
							if (w2s_points[index].x == 0.f && w2s_points[index].y == 0.f)
								continue;
							index++;
						}

						float x = w2s_points[0].x;
						float y = w2s_points[0].y;
						float width = w2s_points[0].x;
						float height = w2s_points[0].y;
						for (auto point : w2s_points) {
							if (x > point.x)
								x = point.x;
							if (width < point.x)
								width = point.x;
							if (y > point.y)
								y = point.y;
							if (height < point.y)
								height = point.y;
						}

						int out_x = x;
						int out_y = y;
						int out_w = width - x;
						int out_h = height - y;
						Height = out_h / 1.02;
						Width = out_w;

						if (((Ped_Location.x + Width / 2) - (Ped_Location.x - Width / 2)) > 600)
							continue;



					}



					if (settings::visuals::box_esp) {

						ImColor caca = settings::visuals::box_color_visible;

						if (settings::visuals::visible_check) {

							if (settings::visuals::visible_check_type == 1) {

								if (VisibleCheck((DWORD64)LocalPlayer, (DWORD64)Peds))
								{
									caca = settings::visuals::box_color_visible;
								}
								else
								{
									caca = settings::visuals::box_color;
								}

							}

						}
						if (settings::visuals::invisible_check_type == 1) {

							if (Visible((DWORD64)Peds)) {




							}
							else {

								caca = settings::visuals::invisible_color;

							}

						}
						if (settings::visuals::friend_visuals) {

							if (is_friends) {


								caca = settings::visuals::friends_colors;

							}

						}
						if (settings::visuals::outlined) {

							
							ImGui::GetBackgroundDrawList()->AddRect(ImVec2(Ped_Location.x + 1 - Width / 2, Ped_Location.y + 1 - Height / 2), ImVec2(Ped_Location.x - 2 + Width / 2, Ped_Location.y - 2 + Height / 2), ImColor(0, 0, 0, 255), settings::visuals::box_rounding, ImDrawCornerFlags_All, settings::visuals::tickness);
							ImGui::GetBackgroundDrawList()->AddRect(ImVec2(Ped_Location.x - 1 - Width / 2, Ped_Location.y - 1 - Height / 2), ImVec2(Ped_Location.x + 1 + Width / 2, Ped_Location.y + 1 + Height / 2), ImColor(0, 0, 0, 255), settings::visuals::box_rounding, ImDrawCornerFlags_All, settings::visuals::tickness);

						}
						Vector3 locatl = Vector3(Peds->GetCoordinate().x, Peds->GetCoordinate().y, Peds->GetCoordinate().z + settings::visuals::Dynamicdebug);
						ImVec2 lavictime = fivem::WorldToScreen(locatl);

						ImGui::GetBackgroundDrawList()->AddRect(ImVec2(Ped_Location.x - Width / 2, Ped_Location.y - Height / 2), ImVec2(Ped_Location.x + Width / 2, Ped_Location.y + Height / 2), caca, settings::visuals::box_rounding, ImDrawCornerFlags_All, settings::visuals::tickness);

					}

					if (settings::visuals::filled_esp) {


						ImColor caca = settings::visuals::filled_color_visible;

						if (settings::visuals::visible_check) {

							if (settings::visuals::visible_check_type == 1) {

								if (VisibleCheck((DWORD64)LocalPlayer, (DWORD64)Peds))
								{
									caca = settings::visuals::filled_color_visible;
								}
								else
								{
									caca = settings::visuals::filled_color;
								}
							}
						}
						ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(Ped_Location.x - Width / 2, Ped_Location.y - Height / 2), ImVec2(Ped_Location.x + Width / 2, Ped_Location.y + Height / 2), caca, settings::visuals::box_rounding, 0);
					}

					spacing_up = 15;
					std::string name = "";
	

					if (settings::visuals::player_name) {

						ImColor caca = settings::visuals::player_name_color_visible;

						if (settings::visuals::visible_check_type == 1) {

							if (VisibleCheck((DWORD64)LocalPlayer, (DWORD64)Peds))
							{
								caca = settings::visuals::player_name_color_visible;
							}
							else
							{
								caca = settings::visuals::player_name_color;
							}

						}

						if (settings::visuals::invisible_check_type == 1) {

							if (Visible((DWORD64)Peds)) {




							}
							else {

								caca = settings::visuals::invisible_color;

							}

						}

						if (settings::visuals::friend_visuals) {

							if (is_friends) {


								caca = settings::visuals::friends_colors;

							}

						}
						auto pedIterator = std::find_if(List.begin(), List.end(),
							[&Peds](Playerr ped) {
								return ped.Handle == Peds;
							});

			
						if (pedIterator != List.end()) {
							name.append(pedIterator->Name);

						}
						else {

							name.append("Ped");

						}
						//name.append(Name);

						DrawOutlinedText(ImGui::GetFont(), name, ImVec2(Ped_Location.x, Ped_Location.y - Height / 2 - spacing_up), 13.0f, caca, true);

						spacing_up += 15;
					}

					if (settings::visuals::health_text) {

						ImColor caca = settings::visuals::health_color_visible;

						if (settings::visuals::visible_check_type == 1) {

							if (VisibleCheck((DWORD64)LocalPlayer, (DWORD64)Peds))
							{
								caca = settings::visuals::health_color_visible;
							}
							else
							{
								caca = settings::visuals::health_color;
							}

						}

						if (settings::visuals::invisible_check_type == 1) {

							if (Visible((DWORD64)Peds)) {




							}
							else {

								caca = settings::visuals::invisible_color;

							}

						}


						if (settings::visuals::friend_visuals) {

							if (is_friends) {


								caca = settings::visuals::friends_colors;

							}

						}

						int health = Peds->GetHealth();

						std::string xxx = "(" + std::to_string(health) + " hp)";

						DrawOutlinedText(ImGui::GetFont(), xxx, ImVec2(Ped_Location.x, Ped_Location.y - Height / 2 - spacing_up), 13.0f, caca, true);

					}


					if (settings::visuals::health_bar)
					{
						if (Peds->GetHealth() <= 100)
							continue;
					
						if (settings::visuals::healthbar_type <= 1) {

							float MaxHealth = Peds->GetMaxHealth(); // Utilise la valeur de santé maximale fixée à 200 si le joueur est sous l'effet "Glife"
							float CurrentHealth = Peds->GetHealth() - 100; // Soustrait 100 de la valeur actuelle de santé

							float HealthPercentage = Height / 100 * CurrentHealth;
							float HealthPercentagee = Height / 100 * 100;

							if (HealthPercentage > Height)
								HealthPercentage = Height;

							float fixedhealth = Peds->GetHealth() / 2;

							float fixedhealthh = 100;

							ImColor col = ImColor(52, 176, 48, 255);
							ImColor coll = ImColor(0, 0, 0, 255);

							if (settings::visuals::healthbar_type == 0) {

								if (fixedhealth != 0)
									DrawHealthBar(ImVec2((Ped_Location.x + Width / 2) + 5, Ped_Location.y + Height / 2), ImVec2(2, HealthPercentagee), coll);
								DrawHealthBar(ImVec2((Ped_Location.x + Width / 2) + 5, Ped_Location.y + Height / 2), ImVec2(1.8, HealthPercentage), col);

							}

							if (settings::visuals::healthbar_type == 1) {

								if (fixedhealth != 0)
									DrawHealthBar(ImVec2((Ped_Location.x - Width / 2) - 5, Ped_Location.y + Height / 2), ImVec2(2, HealthPercentagee), coll);
								DrawHealthBar(ImVec2((Ped_Location.x - Width / 2) - 5, Ped_Location.y + Height / 2), ImVec2(1.8, HealthPercentage), col);

							}
						}
						else {

							float MaxHealth = Peds->GetMaxHealth(); // Utilise la valeur de santé maximale fixée à 200 si le joueur est sous l'effet "Glife"
							float CurrentHealth = Peds->GetHealth() - 100; // Soustrait 100 de la valeur actuelle de santé

							float fixedhealth = Peds->GetArmor();

							float fixedhealthh = 100;

							ImColor col = ImColor(52, 176, 48, 255);
							ImColor coll = ImColor(0, 0, 0, 255);

							float HealthPercentageeee = Width / 100 * (Peds->GetHealth() - 100);
							float HealthPercentageex = Width / 100 * 100;

							if (HealthPercentageeee > Width)
								HealthPercentageeee = Width;

							if (settings::visuals::healthbar_type == 2) {

								if (fixedhealth != 0)
									DrawHealthBarhorizontal(ImVec2((Ped_Location.x - Width / 2), (Ped_Location.y + Height / 2) + 5), ImVec2(Ped_Location.x - Width / 2, (Ped_Location.y + Height / 2) +  5), ImVec2(2, HealthPercentageex), coll);
								DrawHealthBarhorizontal(ImVec2((Ped_Location.x - Width / 2), (Ped_Location.y + Height / 2) + 5), ImVec2(Ped_Location.x - Width / 2, (Ped_Location.y + Height / 2) + 5), ImVec2(1.8, HealthPercentageeee), col);

							}
						}
					}

					spacing_down = 5;

					if (settings::visuals::distance_text) {

						ImColor caca = settings::visuals::distance_color_visible;


						if (settings::visuals::visible_check_type == 1) {

							if (VisibleCheck((DWORD64)LocalPlayer, (DWORD64)Peds))
							{
								caca = settings::visuals::distance_color_visible;
							}
							else
							{
								caca = settings::visuals::distance_color;
							}

						}

						if (settings::visuals::invisible_check_type == 1) {

							if (Visible((DWORD64)Peds)) {




							}
							else {

								caca = settings::visuals::invisible_color;

							}

						}

						if (settings::visuals::friend_visuals) {

							if (is_friends) {


								caca = settings::visuals::friends_colors;

							}

						}

						std::string xxx = std::to_string(Distance) + " m";

						DrawOutlinedText(ImGui::GetFont(), xxx, ImVec2(Ped_Location.x, Ped_Location.y + Height / 2 + spacing_down), 13.0f, caca, true);

						spacing_down = 15;
					}

					if (settings::visuals::weapon_name) {

						ImColor caca = settings::visuals::weapon_name_color_visible;

						if (settings::visuals::visible_check_type == 1) {

							if (VisibleCheck((DWORD64)LocalPlayer, (DWORD64)Peds))
							{
								caca = settings::visuals::weapon_name_color_visible;
							}
							else
							{
								caca = settings::visuals::weapon_name_color;
							}

						}

						if (settings::visuals::invisible_check_type == 1) {

							if (Visible((DWORD64)Peds)) {




							}
							else {

								caca = settings::visuals::invisible_color;

							}

						}


						if (settings::visuals::friend_visuals) {

							if (is_friends) {


								caca = settings::visuals::friends_colors;

							}

						}

						hk_WeaponManager* PedsWeaponManager = Peds->WeaponManager();
						if (!PedsWeaponManager)
							continue;
						hk_WeaponInfo* PedsWeaponInfo = PedsWeaponManager->WeaponInfo();
						if (!PedsWeaponInfo)
							continue;

						uint64_t Hash = PedsWeaponInfo->GetHash();

						DrawOutlinedText(ImGui::GetFont(), get_weapon_name(Hash), ImVec2(Ped_Location.x, Ped_Location.y + Height / 2 + spacing_down), 13.0f, caca, true);

					}

					if (settings::visuals::skeleton_esp) {

						int bone_positions[][2] = {
								{ 0, 7 },
								{ 7, 6 },
								{ 7, 5 },
								{ 7, 8 },
								{ 8, 3 },
								{ 8, 4 }
						};


						uint64_t PedInt = reinterpret_cast<uint64_t>(Peds);

						ImColor caca = settings::visuals::skeleton_color_visible;

						if (settings::visuals::visible_check) {

							if (settings::visuals::visible_check_type == 1) {

								if (VisibleCheck((DWORD64)LocalPlayer, (DWORD64)Peds))
								{
									caca = settings::visuals::skeleton_color_visible;
								}
								else
								{
									caca = settings::visuals::skeleton_color;
								}

							}

						}

						if (settings::visuals::invisible_check_type == 1) {

							if (Visible((DWORD64)Peds)) {




							}
							else {

								caca = settings::visuals::invisible_color;

							}

						}


						if (settings::visuals::friends_colors) {

							if (is_friends) {


								caca = settings::visuals::friend_visuals;

							}

						}

						for (int i = 0; i < 6; ++i) {

							ImVec2 Bone_1 = fivem::GetBoneArrayW2SPos(PedInt, bone_positions[i][0]);
							ImVec2 Bone_2 = fivem::GetBoneArrayW2SPos(PedInt, bone_positions[i][1]);

							ImColor aa = ImColor(0, 0, 0, 255);

							ImGui::GetBackgroundDrawList()->AddLine(Bone_1, Bone_2, aa, 3.0f);
							ImGui::GetBackgroundDrawList()->AddLine(Bone_1, Bone_2, caca, 1.0f);

							ImGui::GetBackgroundDrawList()->AddLine(Bone_1, Bone_2, caca, 1.0f);



						}

					}

					if (settings::visuals::snapline) {

						if (Peds == LocalPlayer) {

							continue;

						}

						ImColor caca = settings::visuals::snapline_color_visible;

						if (settings::visuals::visible_check_type == 1) {

							if (VisibleCheck((DWORD64)LocalPlayer, (DWORD64)Peds))
							{
								caca = settings::visuals::snapline_color_visible;
							}
							else
							{
								caca = settings::visuals::snapline_color;
							}

						}

						if (settings::visuals::invisible_check_type == 1) {

							if (Visible((DWORD64)Peds)) {




							}
							else {

								caca = settings::visuals::invisible_color;

							}

						}


						if (settings::visuals::friend_visuals) {

							if (is_friends) {


								caca = settings::visuals::friends_colors;

							}

						}
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(fivem::WindowSize.x / 2, fivem::WindowSize.y), ImVec2(Ped_Location.x, Ped_Location.y + Height / 2), caca);
					}
				}
			}
		}
	}

	void vehicle_esp(void) {

		if (settings::visuals::vehicle::main_enabled) {

			hk_World* World = (hk_World*)*(uint64_t*)(fivem::World);
			if (!World)
				return;

			hk_Ped* LocalPlayer = World->LocalPlayer();
			if (!LocalPlayer)
				return;

			hk_ReplayInterface* ReplayInterface = (hk_ReplayInterface*)*(uint64_t*)(fivem::ReplayInterface);
			if (!ReplayInterface)
				return;

			hk_VehicleInterface* VehicleInterface = ReplayInterface->VehicleInterface();
			if (!VehicleInterface)
				return;

			ImVec2 LocalPlayer_Location = fivem::WorldToScreen(LocalPlayer->GetCoordinate());


			for (int i = 0; i < VehicleInterface->VehicleMaximum(); i++) {

				if (LocalPlayer->GetHealth() < 100)
					continue;

				hk_Vehicle* Vehiclex = VehicleInterface->VehicleList()->Vehicle(i);
				if (!Vehiclex)
					continue;

				ImVec2 Vehicle_location = fivem::WorldToScreen(Vehiclex->GetCoordinate());
				if (!IsOnScreen(Vehicle_location))
					continue;


				Vector3 DistanceCalculation = (LocalPlayer->GetCoordinate() - Vehiclex->GetCoordinate());

				int Distance = sqrtf(DistanceCalculation.x * DistanceCalculation.x + DistanceCalculation.y * DistanceCalculation.y + DistanceCalculation.z * DistanceCalculation.z);

				if (Distance < settings::visuals::esp_distance) {

					if (settings::vehicle::enabled) {

						if (settings::vehicle::warp_on_key) {

							bool fcku = false;
							Entity aimedEntity;
							Vehicle vehicle_target = fivem::pointer_to_handle((DWORD64)Vehiclex);

							fcku = PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &aimedEntity) && aimedEntity == vehicle_target;
							if (PLAYER::IS_PLAYER_FREE_AIMING_AT_ENTITY(PLAYER::PLAYER_ID(), vehicle_target)) {

								if (SAFE_CALL(GetAsyncKeyState)(settings::vehicle::key_warp) & 0x8000) {

									PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), vehicle_target, -1);

								}
							}
						}

					}

					Hash zizi = ENTITY::GET_ENTITY_MODEL(fivem::pointer_to_handle((DWORD64)Vehiclex));

					const char* caca = Vehiclex->VehicleModelInfo()->GetCharName();

					if (settings::visuals::vehicle::car_enabled) {

						if (VEHICLE::IS_THIS_MODEL_A_CAR(zizi)) {

							DrawOutlinedText(ImGui::GetFont(), caca, ImVec2(Vehicle_location.x, Vehicle_location.y), 13.0f, ImColor(255, 255, 255, 255), true);

							if (settings::visuals::vehicle::car_marker) {

								spacing_car = 18;

								ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(Vehicle_location.x, Vehicle_location.y + spacing_car), 4, ImColor(255, 255, 255), 100);

								spacing_car += 5;
							}
							else {

								spacing_car += 16;
							}

							if (settings::visuals::vehicle::car_distance) {

								std::string ccc = std::to_string(Distance) + "m";

								DrawOutlinedText(ImGui::GetFont(), ccc, ImVec2(Vehicle_location.x, Vehicle_location.y + spacing_car), 13.0f, ImColor(255, 255, 255, 255), true);

								spacing_car += 18;
							}

							if (settings::visuals::vehicle::car_show_plate) {

								char* text_plate = VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT(fivem::pointer_to_handle((DWORD64)Vehiclex));

								DrawOutlinedText(ImGui::GetFont(), text_plate, ImVec2(Vehicle_location.x, Vehicle_location.y + spacing_car), 13.0f, ImColor(255, 255, 255, 255), true);

								spacing_car += 16;

							}

							if (settings::visuals::vehicle::car_lock) {

								int status = VEHICLE::GET_VEHICLE_DOOR_LOCK_STATUS(fivem::pointer_to_handle((DWORD64)Vehiclex));

								if (status == 1) {

									DrawOutlinedText(ImGui::GetFont(), "Unlocked", ImVec2(Vehicle_location.x, Vehicle_location.y + spacing_car), 13.0f, ImColor(255, 255, 255, 255), true);

								}
								else {

									DrawOutlinedText(ImGui::GetFont(), "Locked", ImVec2(Vehicle_location.x, Vehicle_location.y + spacing_car), 13.0f, ImColor(255, 255, 255, 255), true);

								}


							}

						}


						if (settings::visuals::vehicle::boat_enabled) {

							if (VEHICLE::IS_THIS_MODEL_A_BOAT(zizi)) {

								DrawOutlinedText(ImGui::GetFont(), caca, ImVec2(Vehicle_location.x, Vehicle_location.y), 13.0f, ImColor(255, 255, 255, 255), true);

								if (settings::visuals::vehicle::boat_marker) {

									spacing_boat = 18;

									ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(Vehicle_location.x, Vehicle_location.y + spacing_boat), 4, ImColor(255, 255, 255), 100);

									spacing_boat += 5;
								}
								else {

									spacing_boat += 16;
								}

								if (settings::visuals::vehicle::boat_distance) {

									std::string ccc = std::to_string(Distance) + "m";

									DrawOutlinedText(ImGui::GetFont(), ccc, ImVec2(Vehicle_location.x, Vehicle_location.y + spacing_boat), 13.0f, ImColor(255, 255, 255, 255), true);

									spacing_boat += 16;
								}

								if (settings::visuals::vehicle::boat_show_plate) {

									char* text_plate = VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT(fivem::pointer_to_handle((DWORD64)Vehiclex));

									DrawOutlinedText(ImGui::GetFont(), text_plate, ImVec2(Vehicle_location.x, Vehicle_location.y + spacing_boat), 13.0f, ImColor(255, 255, 255, 255), true);

									spacing_boat += 16;

								}

								if (settings::visuals::vehicle::boat_lock) {

									int status = VEHICLE::GET_VEHICLE_DOOR_LOCK_STATUS(fivem::pointer_to_handle((DWORD64)Vehiclex));

									if (status == 1) {

										DrawOutlinedText(ImGui::GetFont(), "Unlocked", ImVec2(Vehicle_location.x, Vehicle_location.y + spacing_boat), 13.0f, ImColor(255, 255, 255, 255), true);

									}
									else {

										DrawOutlinedText(ImGui::GetFont(), "Locked", ImVec2(Vehicle_location.x, Vehicle_location.y + spacing_boat), 13.0f, ImColor(255, 255, 255, 255), true);

									}


								}

							}

						}


						if (settings::visuals::vehicle::heli_enabled) {

							if (VEHICLE::IS_THIS_MODEL_A_HELI(zizi)) {

								DrawOutlinedText(ImGui::GetFont(), caca, ImVec2(Vehicle_location.x, Vehicle_location.y), 13.0f, ImColor(255, 255, 255, 255), true);

								if (settings::visuals::vehicle::heli_marker) {

									spacing_heli = 18;

									ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(Vehicle_location.x, Vehicle_location.y + spacing_heli), 4, ImColor(255, 255, 255), 100);

									spacing_heli += 5;
								}
								else {

									spacing_heli += 16;
								}

								if (settings::visuals::vehicle::heli_distance) {

									std::string ccc = std::to_string(Distance) + "m";

									DrawOutlinedText(ImGui::GetFont(), ccc, ImVec2(Vehicle_location.x, Vehicle_location.y + spacing_heli), 13.0f, ImColor(255, 255, 255, 255), true);

									spacing_heli += 16;
								}

								if (settings::visuals::vehicle::heli_show_plate) {

									char* text_plate = VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT(fivem::pointer_to_handle((DWORD64)Vehiclex));

									DrawOutlinedText(ImGui::GetFont(), text_plate, ImVec2(Vehicle_location.x, Vehicle_location.y + spacing_heli), 13.0f, ImColor(255, 255, 255, 255), true);

									spacing_heli += 16;

								}

								if (settings::visuals::vehicle::heli_lock) {

									int status = VEHICLE::GET_VEHICLE_DOOR_LOCK_STATUS(fivem::pointer_to_handle((DWORD64)Vehiclex));

									if (status == 1) {

										DrawOutlinedText(ImGui::GetFont(), "Unlocked", ImVec2(Vehicle_location.x, Vehicle_location.y + spacing_heli), 13.0f, ImColor(255, 255, 255, 255), true);

									}
									else {

										DrawOutlinedText(ImGui::GetFont(), "Locked", ImVec2(Vehicle_location.x, Vehicle_location.y + spacing_heli), 13.0f, ImColor(255, 255, 255, 255), true);

									}
								}
							}
						}
					}
				}
			}

		}

	}
}


struct Element
{
	std::string name;
	int hash;
};

std::vector<Element> item_list;

char new_element[256];
int new_hash = 0;

int selected_item = -1;

int spacing = 0;


namespace object {

	void settings(void) {

		ImGui::Checkbox(E("Enabled"), &settings::visuals::object::object_esp);

		std::vector<const char*> item_names;
		for (const auto& element : item_list)
		{
			item_names.push_back(element.name.c_str());
		}

		ImGui::Text(E("Object(s) List"));
		ImGui::ListBox(E("##Liste des éléments"), &selected_item, item_names.data(), static_cast<int>(item_names.size()));

		
		if (selected_item != -1 && ImGui::Button(E("Delete")))
		{
			item_list.erase(item_list.begin() + selected_item);
			selected_item = -1;
		}

		ImGui::Separator();

		ImGui::Text(E("Object Name"));
		ImGui::InputText(E("##Object Name"), new_element, sizeof(new_element));
		ImGui::Text(E("Object Hash"));
		ImGui::InputInt(E("##Hash"), &new_hash, sizeof(new_hash));

		if (ImGui::Button(E("Add")))
		{

			item_list.push_back({ new_element, new_hash });
		}

	}

	void visuals(void) {

		if (settings::visuals::object::object_esp) {

			hk_World* World = (hk_World*)*(uint64_t*)(fivem::World);
			if (!World)
				return;

			hk_Ped* LocalPlayer = World->LocalPlayer();
			if (!LocalPlayer)
				return;

			hk_ReplayInterface* ReplayInterface = (hk_ReplayInterface*)*(uint64_t*)(fivem::ReplayInterface);
			if (!ReplayInterface)
				return;

			hk_ObjectInterface* PedInterface = ReplayInterface->ObjectInterface();
			if (!PedInterface)
				return;

			for (int i = 0; i < PedInterface->ObjectMaximum(); i++) {

				hk_Object* Peds = PedInterface->ObjectList()->Object(i);
				if (!Peds) continue;

				if (LocalPlayer->GetHealth() <= 100)
					continue;

				ImVec2 object_pos = fivem::WorldToScreen(Peds->GetCoordinate());
				if (!IsOnScreen(object_pos))
					continue;

				const char* caca = Peds->ObjectModelInfo()->ModelChar();
				int32_t WeaponHash = *(int32_t*)(Peds->ObjectModelInfo() + 0x18);

				Vector3 DistanceCalculation = (LocalPlayer->GetCoordinate() - Peds->GetCoordinate());

				int Distance = sqrtf(DistanceCalculation.x * DistanceCalculation.x + DistanceCalculation.y * DistanceCalculation.y + DistanceCalculation.z * DistanceCalculation.z);

				for (const auto& element : item_list)
				{
					if (element.hash == WeaponHash)
					{
						spacing = 30;

						DrawOutlinedText(ImGui::GetFont(), element.name, ImVec2(object_pos.x, object_pos.y - spacing), 13.0f, ImColor(255, 255, 255, 255), true);

						if (settings::visuals::object::marker) {

							spacing = 8;

						}
						else {

							spacing = 15;

						}

						if (settings::visuals::object::marker) {


							ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(object_pos.x, object_pos.y - spacing), 4, ImColor(255, 255, 255), 100);

						}

						spacing = 3;

						if (settings::visuals::object::distance) {


							std::string ccc = std::to_string(Distance) + "m";

							DrawOutlinedText(ImGui::GetFont(), ccc, ImVec2(object_pos.x, object_pos.y - spacing), 13.0f, ImColor(255, 255, 255, 255), true);

						}

						if (settings::visuals::object::snapline) {

							ImGui::GetBackgroundDrawList()->AddLine(ImVec2(fivem::WindowSize.x / 2, fivem::WindowSize.y), ImVec2(object_pos.x, object_pos.y), ImColor(255, 255, 255));

						}

					}

				}
			}

		}
		
	}

}