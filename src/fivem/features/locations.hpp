#pragma once

#include "../native/invoker.hpp"
#include "../classes/classes.hpp"
#include <ImGuiNotify.hpp>

using namespace std;

struct MyElement {
	int x, y, z;
	std::string name;

	bool isSelected; // Nouvelle variable pour indiquer si l'élément est sélectionné


};

std::vector<MyElement> myElements;

int selected_pos = -1;

char new_hash_buffer_x[64];
char new_hash_buffer_y[64];
char new_hash_buffer_z[64];

namespace locations {

	auto location_list() -> void {

		static int selectedIndex = -1;

		if (ImGui::BeginListBox(("##liste of pos"), ImVec2(ImGui::GetWindowWidth() - 20, ImGui::GetWindowHeight() - 150))) {

			for (int i = 0; i < myElements.size(); i++) {
				std::string label = myElements[i].name;
				if (ImGui::Selectable(label.c_str(), selectedIndex == i)) {
					selectedIndex = i;
				}
			}

			ImGui::EndListBox();
		}

		if (selectedIndex != -1) {

			const MyElement& selectedElement = myElements[selectedIndex];

			if (ImGui::Button("Teleport", ImVec2(ImGui::GetWindowWidth() - 20, 29))) {

				auto selected_pos = Vector3(selectedElement.x, selectedElement.y, selectedElement.z);

				ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), selectedElement.x, selectedElement.y, selectedElement.z, false, false, false, true);

			}

			if (ImGui::Button("Delete", ImVec2(ImGui::GetWindowWidth() - 20, 29))) {

				myElements.erase(myElements.begin() + selectedIndex);
				selectedIndex = -1;

			}
		}

	}

	auto location_settings() -> void {

		static char name[32] = "";
		static int position[3] = { 0.0f, 0.0f, 0.0f };


		ImGui::InputText(("Name"), name, sizeof(name));
		ImGui::InputText(("Position X"), new_hash_buffer_x, sizeof(new_hash_buffer_x), ImGuiInputTextFlags_CharsDecimal);
		ImGui::InputText(("Position Y"), new_hash_buffer_y, sizeof(new_hash_buffer_y), ImGuiInputTextFlags_CharsDecimal);
		ImGui::InputText(("Position Z"), new_hash_buffer_z, sizeof(new_hash_buffer_z), ImGuiInputTextFlags_CharsDecimal);
		std::string mossad = name;
		if (ImGui::Button(("Add"), ImVec2(ImGui::GetWindowWidth() - 20, 29))) {
			if (mossad.empty()) {
				ImGui::InsertNotification({ ImGuiToastType_Success, 3000, E("You need to add an name to the location") });

			}
			else {
				MyElement newElement;

				position[0] = atoi(new_hash_buffer_x);
				position[1] = atoi(new_hash_buffer_y);
				position[2] = atoi(new_hash_buffer_z);

				newElement.x = position[0];
				newElement.y = position[1];
				newElement.z = position[2];
				newElement.name = name;

				myElements.push_back(newElement);


			}


		}

		if (ImGui::Button(("Add Current Postion"), ImVec2(ImGui::GetWindowWidth() - 20, 29))) {


			hk_World* World = (hk_World*)*(uint64_t*)(fivem::World);
			if (!World)
				return;

			hk_Ped* LocalPlayer = World->LocalPlayer();
			if (!LocalPlayer)
				return;

			hk_ReplayInterface* ReplayInterface = (hk_ReplayInterface*)*(uint64_t*)(fivem::ReplayInterface);
			if (!ReplayInterface)
				return;

			Vector3 pos = LocalPlayer->GetCoordinate();
			if (mossad.empty()) {
				ImGui::InsertNotification({ ImGuiToastType_Success, 3000, E("You need to add an name to the location") });

			}
			else {
				MyElement newElement;
				newElement.x = pos.x;
				newElement.y = pos.y;
				newElement.z = pos.z;
				newElement.name = name;

				myElements.push_back(newElement);
			}

		}

	}

	auto visuals() -> void {


			hk_World* World = (hk_World*)*(uint64_t*)(fivem::World);
			if (!World)
				return;

			hk_Ped* LocalPlayer = World->LocalPlayer();
			if (!LocalPlayer)
				return;

			hk_ReplayInterface* ReplayInterface = (hk_ReplayInterface*)*(uint64_t*)(fivem::ReplayInterface);
			if (!ReplayInterface)
				return;

			for (const auto& element : myElements) {

				Vector3 DistanceCalculation = (LocalPlayer->GetCoordinate() - Vector3(element.x, element.y, element.z));

				int Distance = sqrtf(DistanceCalculation.x * DistanceCalculation.x + DistanceCalculation.y * DistanceCalculation.y + DistanceCalculation.z * DistanceCalculation.z);
			

					ImVec2 point_positon = fivem::WorldToScreen(Vector3(element.x, element.y, element.z));
					if (!IsOnScreen(point_positon))
						continue;

					DrawOutlinedText(ImGui::GetFont(), element.name, ImVec2(point_positon.x, point_positon.y), 13.0f, ImColor(255, 255, 255, 255), true);

					ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(point_positon.x, point_positon.y + 25), 4, ImColor(255, 255, 255), 100);

					std::string ccc = std::to_string(Distance) + ("m");

					DrawOutlinedText(ImGui::GetFont(), ccc, ImVec2(point_positon.x, point_positon.y + 35), 13.0f, ImColor(255, 255, 255, 255), true);



			}
		}



}