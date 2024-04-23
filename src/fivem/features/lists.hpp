#pragma once


#include "../classes/classes.hpp"
#include "../settings.hpp"
#include "../native/invoker.hpp"
namespace vehiculelist {
	bool shootbullet = false;
}
namespace playerlist {
	bool shootplayer = false;
	bool tazeplayer = false;
}
namespace lists {

	void players_list(void) {

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


		static char filterText[256] = "";

		ImGui::Text("Filter Player Name");
		if (ImGui::InputText("##Filter Player Name", filterText, sizeof(filterText)))
		{
			// Le texte de filtrage a été modifié, vous pouvez effectuer une action ici
		}

		if (ImGui::ListBoxHeader(" ", ImVec2(ImGui::GetContentRegionAvail().x - 2, ImGui::GetContentRegionAvail().y - 2)))
		{
			for (int i = 0; i < PedInterface->PedMaximum(); i++)
			{
				hk_Ped* Peds = PedInterface->PedList()->Ped(i);
				if (!Peds)
					continue;

				void* addr = (void*)(Peds->PlayerInfo() + 0x20);
			//	const char* caca = fivem::GetPlayerNamess(addr);
				std::string pouf = "player";
				pouf.append("##");
				std::string playerName = pouf + std::to_string(i);
				//if (caca == "** Invalid **")
				//{
					playerName = "Peds ##" + std::to_string(i);
			//	}
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
					else {
						auto pedIterator = std::find_if(List.begin(), List.end(),
							[&Peds](Playerr ped) {
								return ped.Handle == Peds;
							});


						if (pedIterator != List.end()) {
							playerName = pedIterator->Name + std::to_string(i);

						}
					

					}

			
				// Vérifier si le nom du joueur correspond au texte de filtrage saisi
				if (std::strstr(playerName.c_str(), filterText) != nullptr)
				{
					bool is_selected = (settings::peds::selected_index == i);
					if (ImGui::Selectable(playerName.c_str(), is_selected))
					{
						settings::peds::selected_index = i;
					}
				}
			}

			ImGui::ListBoxFooter();

		}
	}

	void player_list_option(void) {


		hk_World* World = (hk_World*)*(uint64_t*)(fivem::World);
		if (!World)
			return;

		hk_Ped* LocalPlayer = World->LocalPlayer();
		if (!LocalPlayer)
			return;

		hk_ObjectNavigationPed* Nav = LocalPlayer->ObjectNavigation();
		if (!Nav)
			return;

		hk_ReplayInterface* ReplayInterface = (hk_ReplayInterface*)*(uint64_t*)(fivem::ReplayInterface);
		if (!ReplayInterface)
			return;

		hk_PedInterface* PedInterface = ReplayInterface->PedInterface();
		if (!PedInterface)
			return;

		ImGui::Text("Players List Features");
		ImGui::Separator();

		hk_Ped* SelectedPed = PedInterface->PedList()->Ped(settings::peds::selected_index);

		bool can_use_lists = true;

		if (SelectedPed->GetCoordinate().x == 0) {

			if (SelectedPed->GetCoordinate().z == 0) {

				can_use_lists = false;

			}

		}
		else if (SelectedPed->GetCoordinate().y == 0)
		{

			if (SelectedPed->GetCoordinate().z == 0) {

				can_use_lists = false;

			}

		}

		if (!can_use_lists) {

			ImGui::Text("Invalid player selected !");
			ImGui::Text("Please choice another one");

		}
		else {

			ImGui::Checkbox("Overide Ped", &settings::peds::overide_ped);

			if (settings::peds::overide_ped) {

				ImVec2 Ped_Location = fivem::WorldToScreen(SelectedPed->GetCoordinate());
				if (IsOnScreen(Ped_Location)) {

					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(fivem::WindowSize.x / 2, fivem::WindowSize.y), ImVec2(Ped_Location.x, Ped_Location.y), ImColor(255, 255, 255));

				}

			}

			ImGui::Separator();

			ImGui::Text("Features :");
			ImGui::Separator();

			void* addr = (void*)(SelectedPed->PlayerInfo() + 0x20);
			//const char* caca = fivem::GetPlayerNamess(addr);

			std::string pouf = "ped";

			auto it = std::find(fivem::Friend.begin(), fivem::Friend.end(), pouf);

			if (it != fivem::Friend.end())
			{
				if (ImGui::Button("Remove Friend"))
				{

					int index = it - fivem::Friend.begin();
					fivem::Friend.erase(fivem::Friend.begin() + index);

				}
			}
			else
			{
				if (ImGui::Button("Add Friend"))
				{
					//fivem::Friend.push_back(caca);
				}
			}

			if (ImGui::TreeNode("Utils")) {

				if (ImGui::Button("Steal Outfit")) {

					auto player = PLAYER::PLAYER_PED_ID();

					PED::_ASSIGN_PLAYER_TO_PED(fivem::pointer_to_handle((DWORD64)SelectedPed), player);

				}

				if (ImGui::Button("Set in Godmode")) {

					ENTITY::SET_ENTITY_INVINCIBLE(fivem::pointer_to_handle((DWORD64)SelectedPed), true);
					PLAYER::SET_PLAYER_INVINCIBLE(fivem::pointer_to_handle((DWORD64)SelectedPed), true);

				}

				ImGui::SameLine();

				if (ImGui::Button("Remove Godmode")) {

					ENTITY::SET_ENTITY_INVINCIBLE(fivem::pointer_to_handle((DWORD64)SelectedPed), false);
					PLAYER::SET_PLAYER_INVINCIBLE(fivem::pointer_to_handle((DWORD64)SelectedPed), false);


				}

				if (ImGui::Button("Set Invisible")) {

					ENTITY::SET_ENTITY_VISIBLE(fivem::pointer_to_handle((DWORD64)SelectedPed), false);


				}

				ImGui::SameLine();

				if (ImGui::Button("Remove Invisible")) {

					ENTITY::SET_ENTITY_VISIBLE(fivem::pointer_to_handle((DWORD64)SelectedPed), true);


				}

				if (ImGui::Button("Give Health")) {

					ENTITY::SET_ENTITY_HEALTH(fivem::pointer_to_handle((DWORD64)SelectedPed), 200);

				}

				ImGui::SameLine();


				if (ImGui::Button("Give Armor")) {

					PED::SET_PED_ARMOUR(fivem::pointer_to_handle((DWORD64)SelectedPed), 100);

				}

				if (ImGui::Button("Revive")) {

					PED::RESURRECT_PED(fivem::pointer_to_handle((DWORD64)SelectedPed));

				}

				if (ImGui::Button("Teleport to player")) {

					if (SelectedPed != LocalPlayer)
					{
						auto caca = SelectedPed->GetCoordinate();

						PED::SET_PED_COORDS_KEEP_VEHICLE(PLAYER::PLAYER_PED_ID(), caca.x, caca.y, caca.z);
					}
				}



				ImGui::TreePop();
			}


			if (ImGui::TreeNode("Trolls")) {

				if (ImGui::Button("Taze Player")) {

					if (SelectedPed != LocalPlayer) {


						auto player = PLAYER::PLAYER_PED_ID();
						auto WeaponHash = WEAPON::GET_SELECTED_PED_WEAPON(player);
						auto WeaponDamage = WEAPON::GET_WEAPON_DAMAGE(0x8BB05FD7, NULL);
						GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(SelectedPed->GetCoordinate().x, SelectedPed->GetCoordinate().y, SelectedPed->GetCoordinate().z + 2, SelectedPed->GetCoordinate().x, SelectedPed->GetCoordinate().y, SelectedPed->GetCoordinate().z - 1, (int)WeaponDamage, false, 0x8BB05FD7, player, true, false, 3.f);


					}

				}

				if (ImGui::Button("Kill Player")) {

					if (SelectedPed != LocalPlayer) {

						auto player = PLAYER::PLAYER_PED_ID();
						auto WeaponHash = WEAPON::GET_SELECTED_PED_WEAPON(player);
						GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(SelectedPed->GetCoordinate().x, SelectedPed->GetCoordinate().y, SelectedPed->GetCoordinate().z + 2, SelectedPed->GetCoordinate().x, SelectedPed->GetCoordinate().y, SelectedPed->GetCoordinate().z - 1, 300, false, 0x1B06D571, player, true, false, 3.f);

					}
				}

				if (ImGui::Button("Strip All Weapon")) {

					if (SelectedPed == LocalPlayer) {



					}
					else {

						WEAPON::REMOVE_ALL_PED_WEAPONS(fivem::pointer_to_handle((DWORD64)SelectedPed), false);

					}

				}

				if (ImGui::Button("Strip Current Weapon")) {

					if (SelectedPed != LocalPlayer) {

						auto weapon = WEAPON::GET_SELECTED_PED_WEAPON(fivem::pointer_to_handle((DWORD64)SelectedPed));
						WEAPON::REMOVE_WEAPON_FROM_PED(fivem::pointer_to_handle((DWORD64)SelectedPed), weapon);

					}
				}


				if (ImGui::Button("Freeze Player")) {

					ENTITY::FREEZE_ENTITY_POSITION(fivem::pointer_to_handle((DWORD64)SelectedPed), true);

				}

				ImGui::SameLine();

				if (ImGui::Button("Unfreeze Player")) {

					ENTITY::FREEZE_ENTITY_POSITION(fivem::pointer_to_handle((DWORD64)SelectedPed), false);

				}

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Other")) {

				if (ImGui::Button("Spectate"))
				{
					auto player = PLAYER::PLAYER_PED_ID();
					NETWORK::NETWORK_SET_IN_SPECTATOR_MODE((bool)true, fivem::pointer_to_handle((DWORD64)SelectedPed));

				}

				ImGui::SameLine();

				if (ImGui::Button("Off Spectate"))
				{
					auto player = PLAYER::PLAYER_PED_ID();
					NETWORK::NETWORK_SET_IN_SPECTATOR_MODE((bool)false, fivem::pointer_to_handle((DWORD64)SelectedPed));
				}


				ImGui::TreePop();
			}

			ImGui::Separator();

			ImGui::Text("Information :");
			ImGui::Separator();

			Vector3 DistanceCalculation = (LocalPlayer->GetCoordinate() - SelectedPed->GetCoordinate());
			int Distance = sqrtf(DistanceCalculation.x * DistanceCalculation.x + DistanceCalculation.y * DistanceCalculation.y + DistanceCalculation.z * DistanceCalculation.z);;

			int health = SelectedPed->GetHealth();
			int armor = SelectedPed->GetArmor();

			std::string ixx = std::to_string(settings::peds::selected_index);
			ImGui::Text(ixx.c_str());


			std::string distance = "Distance : " + std::to_string(Distance);
			ImGui::Text(distance.c_str());
			std::string healthtoshow = "Health : " + std::to_string(health) + " \nArmor : " + std::to_string(armor);
			ImGui::Text(healthtoshow.c_str());
			std::string coordstoshow = "X : " + std::to_string(SelectedPed->GetCoordinate().x) + " \nY : " + std::to_string(SelectedPed->GetCoordinate().y) + " \nZ : " + std::to_string(SelectedPed->GetCoordinate().z);
			ImGui::Text(coordstoshow.c_str());

		}


	}

	void vehicle_list(void) {

		hk_World* World = (hk_World*)*(uint64_t*)(fivem::World);
		if (!World)
			return;

		hk_Ped* LocalPlayer = World->LocalPlayer();
		if (!LocalPlayer)
			return;

		hk_ReplayInterface* ReplayInterface = (hk_ReplayInterface*)*(uint64_t*)(fivem::ReplayInterface);
		if (!ReplayInterface)
			return;

		hk_VehicleInterface* PedInterface = ReplayInterface->VehicleInterface();
		if (!PedInterface)
			return;


		static char filterText[256] = "";


		ImGui::Text("Filter Vehicle Name");
		if (ImGui::InputText("##filter Vehicle Name", filterText, sizeof(filterText)))
		{

		}

		if (ImGui::ListBoxHeader("    ", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y))) {
		
			for (int i = 0; i < PedInterface->VehicleMaximum(); i++) {
				hk_Vehicle* Peds = PedInterface->VehicleList()->Vehicle(i);
				if (!Peds)
					continue;

				const char* caca = Peds->VehicleModelInfo()->GetCharName();
				std::string pouf = caca;
				pouf.append("##");
				std::string playerName = pouf + std::to_string(i);


				if (std::strstr(playerName.c_str(), filterText) != nullptr)
				{
					bool is_selected = (settings::peds::selected_index_vehicle == i);
					if (ImGui::Selectable(playerName.c_str(), is_selected))
					{
						settings::peds::selected_index_vehicle = i;
					}
				}
			}

			ImGui::ListBoxFooter();
		}
	}

	void vehicle_list_option(void) {

		hk_World* World = (hk_World*)*(uint64_t*)(fivem::World);
		if (!World)
			return;

		hk_Ped* LocalPlayer = World->LocalPlayer();
		if (!LocalPlayer)
			return;

		hk_ReplayInterface* ReplayInterface = (hk_ReplayInterface*)*(uint64_t*)(fivem::ReplayInterface);
		if (!ReplayInterface)
			return;

		hk_VehicleInterface* PedInterface = ReplayInterface->VehicleInterface();
		if (!PedInterface)
			return;

		hk_Vehicle* SelectedVehicle = PedInterface->VehicleList()->Vehicle(settings::peds::selected_index_vehicle);


		bool can_use_lists = true;

		if (SelectedVehicle->GetCoordinate().x == 0) {

			if (SelectedVehicle->GetCoordinate().z == 0) {

				can_use_lists = false;

			}

		}
		else if (SelectedVehicle->GetCoordinate().y == 0)
		{

			if (SelectedVehicle->GetCoordinate().z == 0) {

				can_use_lists = false;

			}

		}


		ImGui::Text("Vehicle List Features");
		ImGui::Separator();

		if (!can_use_lists) {


			ImGui::Text("Invalid car selected !");
			ImGui::Text("Please choice another one");

		}
		else {

			ImGui::Checkbox("Overide Vehicle", &settings::peds::overide_veh);

			if (settings::peds::overide_veh) {

				ImVec2 Ped_Location = fivem::WorldToScreen(SelectedVehicle->GetCoordinate());
				if (IsOnScreen(Ped_Location)) {

					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(fivem::WindowSize.x / 2, fivem::WindowSize.y), ImVec2(Ped_Location.x, Ped_Location.y), ImColor(255, 255, 255));

				}


			}

			if (ImGui::TreeNode("Utils")) {


				if (ImGui::Button("Teleport To Vehicle")) {

					auto caca = SelectedVehicle->GetCoordinate();

					ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), caca.x, caca.y, caca.z, false, false, false, true);


				}

				if (ImGui::Button("Teleport Into Vehicle")) {

					Vehicle vehicle_target = fivem::pointer_to_handle((DWORD64)SelectedVehicle);

					PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), vehicle_target, -1);


				}


				if (ImGui::Button("Warp Vehicle")) {

					Vehicle playerVehicle = fivem::pointer_to_handle((DWORD64)SelectedVehicle);

					Ped pedestrian = VEHICLE::GET_PED_IN_VEHICLE_SEAT(playerVehicle, -1);

					AI::CLEAR_PED_TASKS_IMMEDIATELY(pedestrian);

					Vector3 location = LocalPlayer->GetCoordinate();

					if (VEHICLE::IS_VEHICLE_SEAT_FREE(playerVehicle, -1)) {

						ENTITY::SET_ENTITY_COORDS(playerVehicle, location.x, location.y, location.z, false, false, false, true);
					}

				}

				if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false)) {

					if (ImGui::Button("Steal Plate")) {

						char* text_plate = VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT(fivem::pointer_to_handle((DWORD64)SelectedVehicle));
						auto current_vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), true);

						VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(current_vehicle, text_plate);

					}


				}

				


				if (ImGui::Button("Lock vehicle"))
				{
					VEHICLE::SET_VEHICLE_DOORS_LOCKED(fivem::pointer_to_handle((DWORD64)SelectedVehicle), 3);

				}

				ImGui::SameLine();

				if (ImGui::Button("Unlock vehicle"))
				{
					VEHICLE::SET_VEHICLE_DOORS_LOCKED(fivem::pointer_to_handle((DWORD64)SelectedVehicle), 1);

				}

				ImGui::TreePop();

			}



			if (ImGui::TreeNode("Trolls")) {


				if (ImGui::Button("Teleport To Void")) {

					ENTITY::SET_ENTITY_COORDS(fivem::pointer_to_handle((DWORD64)SelectedVehicle), 15000, 15000, 0, false, false, false, true);


				}

				if (ImGui::Button("Kick Driver")) {

					Ped pedestrian = VEHICLE::GET_PED_IN_VEHICLE_SEAT(fivem::pointer_to_handle((DWORD64)SelectedVehicle), -1);

					AI::CLEAR_PED_TASKS_IMMEDIATELY(pedestrian);

				}


				if (ImGui::Button("Explode Vehicle")) {
					vehiculelist::shootbullet = true;
					
				}

				ImGui::TreePop();
			}

			ImGui::Separator();

			ImGui::Text("Information :");
			ImGui::Separator();

			int health = SelectedVehicle->GetHealth();

			Vector3 DistanceCalculation = (LocalPlayer->GetCoordinate() - SelectedVehicle->GetCoordinate());
			int Distance = sqrtf(DistanceCalculation.x * DistanceCalculation.x + DistanceCalculation.y * DistanceCalculation.y + DistanceCalculation.z * DistanceCalculation.z);;

			std::string zizi = std::to_string(settings::peds::selected_index_vehicle);
			ImGui::Text(zizi.c_str());

			std::string distance = "Distance : " + std::to_string(Distance);
			ImGui::Text(distance.c_str());
			std::string healthtoshow = "Health : " + std::to_string(health);
			ImGui::Text(healthtoshow.c_str());
			std::string coordstoshow = "X : " + std::to_string(SelectedVehicle->GetCoordinate().x) + " \nY : " + std::to_string(SelectedVehicle->GetCoordinate().y) + " \nZ : " + std::to_string(SelectedVehicle->GetCoordinate().z);
			ImGui::Text(coordstoshow.c_str());

		}
	
	}

	void vehicle_native_option(void) {
		hk_World* World = (hk_World*)*(uint64_t*)(fivem::World);
		if (!World)
			return;

		hk_Ped* LocalPlayer = World->LocalPlayer();
		if (!LocalPlayer)
			return;

		hk_ReplayInterface* ReplayInterface = (hk_ReplayInterface*)*(uint64_t*)(fivem::ReplayInterface);
		if (!ReplayInterface)
			return;

		hk_VehicleInterface* PedInterface = ReplayInterface->VehicleInterface();
		if (!PedInterface)
			return;

		hk_Vehicle* SelectedVehicle = PedInterface->VehicleList()->Vehicle(settings::peds::selected_index_vehicle);
		if (vehiculelist::shootbullet) {
			auto player = PLAYER::PLAYER_PED_ID();
			GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(SelectedVehicle->GetCoordinate().x, SelectedVehicle->GetCoordinate().y, SelectedVehicle->GetCoordinate().z + 2, SelectedVehicle->GetCoordinate().x, SelectedVehicle->GetCoordinate().y, SelectedVehicle->GetCoordinate().z - 1, 300, false, 0xB1CA77B1, player, true, false, 3.f);
			vehiculelist::shootbullet = false;

		}
	}
}