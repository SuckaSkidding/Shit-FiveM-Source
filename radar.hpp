#pragma once 

#include "src/fivem/settings.hpp"
#include "src/fivem/classes/classes.hpp"
#define pi 3.141592653589793f


void WindowFillCircle(float x, float y, float w, float h, ImColor color, int rounding)
{
	ImGui::GetWindowDrawList()->AddCircleFilled(ImVec2(x, y), 3, color, rounding);
}
void WindowCircle(float x, float y, float w, float h, ImColor color, int rounding)
{
	ImGui::GetWindowDrawList()->AddCircle(ImVec2(x, y), 3, color, rounding);
}

void WindowRadarText(std::string text, float x, float y, int size, ImColor color)
{
	DrawOutlinedText(ImGui::GetFont(), text, ImVec2(x, y), size, color, true);

	//DrawOutlinedText(ImGui::GetFont(), caca, ImVec2(Ped_Location.x, Ped_Location.y - Height / 2 - 15), 13.0f, ImColor(255, 255, 255, 255), true);
}

float degreesToRadians(float degrees)
{

	return degrees * (pi / 180.0f);

}
ImVec2 WorldToRadar(Vector3 Location, FLOAT RadarX, FLOAT RadarY, float RadarSize, float RadarZoom)
{

	hk_World* World = reinterpret_cast<hk_World*>(*reinterpret_cast<uint64_t*>(fivem::World));
	hk_Ped* LocalPlayer = World->LocalPlayer();
	Vector3 localpos = LocalPlayer->GetCoordinate();
	ImVec2 Coord(0, 0);
	ImVec2 Return(0, 0);
	DWORD64 addr = fivem::GetCamera();

	if (addr) {

		float rot = 0.0f;
		Vector3 TPS = *reinterpret_cast<Vector3*>(addr + 0x03D0);

		// Utilisation de la fonction atan2 pour calculer l'angle de rotation
		rot = atan2f(TPS.y, TPS.x) * 180.0f / DirectX::XM_PI;

		// Utilisation de la fonction atan2 pour calculer l'angle de direction vers l'avant
		float ForwardDirection = atan2f(TPS.y, TPS.x);
		float cosYaw = cos(ForwardDirection);
		float sinYaw = sin(ForwardDirection);

		float deltaX = Location.x - localpos.x;
		float deltaY = Location.y - localpos.y;

		// Précalcule les valeurs diviseur pour éviter des calculs répétitifs
		float cosDivZoom = cosYaw / RadarZoom;
		float sinDivZoom = sinYaw / RadarZoom;

		float locationX = (deltaY * cosDivZoom - deltaX * sinDivZoom);
		float locationY = (deltaX * cosDivZoom + deltaY * sinDivZoom);

		const float halfRadarSize = RadarSize / 2.0f - 2.5f;

		// Utilisation de std::clamp pour garantir que les valeurs restent dans la plage autorisée
		locationX = std::clamp(locationX, -halfRadarSize, halfRadarSize);
		locationY = std::clamp(locationY, -halfRadarSize, halfRadarSize);

		Return.x = -locationX + RadarX;
		Return.y = -locationY + RadarY;

	}

	return Return;

}
namespace radar {

	auto radar() -> void {

		if (settings::visuals::radar::enabled) {

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
			ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(ImColor(0,0,0,20)));

			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
			{
				ImGui::SetNextWindowSize(ImVec2(settings::visuals::radar::size_x, settings::visuals::radar::size_y));

				ImGui::Begin("Radar", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
				{
					ImDrawList* draw_list = ImGui::GetWindowDrawList();

					ImVec2 winpos = ImGui::GetWindowPos();
					ImVec2 winsize = ImGui::GetWindowSize();

					const float RadarZoomFactor = (settings::visuals::radar::zoom * 0.2f);
					const ImVec2 RadarWindowPos = ImGui::GetWindowPos();
					const ImVec2 RadarWindowSize = ImGui::GetWindowSize();

					for (int index = 0; index < PedInterface->PedMaximum(); index++) {

						hk_Ped* Peds = PedInterface->PedList()->Ped(index);

						if (!Peds || LocalPlayer->GetHealth() <= 100) {
							continue;
						}

						float health = Peds->GetHealth();
						auto ped_type = Peds->GetPedType();

						if (!ped_type) {
							continue;
						}

						bool IsPed = false;

						ped_type = ped_type << 11 >> 25;

						if (ped_type != 2) {

							IsPed = true;

						}

						if (!settings::visuals::radar::render_ped && IsPed) {
							continue;
						}

						if (!settings::visuals::radar::render_dead && health < 100) {
							continue;
						}

						// Pr calcul de la position du radar pour ce ped
						ImVec2 RadarPedPos = WorldToRadar(Peds->GetCoordinate(), RadarWindowPos.x, RadarWindowPos.y, RadarWindowSize.x, RadarZoomFactor);

						// Calcul de la position du cercle   dessiner
						float CircleCenterX = RadarPedPos.x + RadarWindowSize.x * 0.5f;
						float CircleCenterY = RadarPedPos.y + RadarWindowSize.y * 0.5f;
				

						// Dessin du cercle
						if (Peds == LocalPlayer) {
							WindowFillCircle(CircleCenterX, CircleCenterY, 4, 4, settings::visuals::radar::local_player_dot_circle, 0);
							//WindowCircle(CircleCenterX, CircleCenterY, 4, 4, settings::visuals::radar::local_player_dot_circle, 0);
						
						}
						else {
							WindowFillCircle(CircleCenterX, CircleCenterY, 4, 4, settings::visuals::radar::player_dot_circle, 0);
					

						}
					}

				}
				ImGui::End();
			}
			ImGui::PopStyleVar();
			ImGui::PopStyleColor();

		}


	}


}