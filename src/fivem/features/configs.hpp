#pragma once

#include "../../dependencies/imgui/imgui.h"
#include <filesystem>
#include "../settings.hpp"

namespace fs = std::filesystem;

namespace config {

	void configuration(void) {

        static std::vector<std::string> configFiles;
        static std::vector<const char*> configFilesCStr; // Tableau de pointeurs de chaînes

        static char configName[64]; // Variable pour stocker le nom de la configuration

        configFiles.clear();
        configFilesCStr.clear();




        std::string main = getenv("APPDATA");
        std::string configs = "";
        main.append("\\NVIDIA");
        configs.append(main + "\\settings");


        ImGui::Text(E("Config Name"));
        ImGui::InputText(E("##configname"), configName, sizeof(configName));

        if (ImGui::Button(E("Create"))) {

            auto configPath = configs + "\\";

            configPath.append((std::string(configName) + ".cfg"));

            FILE* p_stream;
            fopen_s(&p_stream, configPath.c_str(), "w");

            fwrite(&settings::aimbot::enabled, sizeof(bool), 1, p_stream);
            fwrite(&settings::aimbot::hotkey, sizeof(bool), 1, p_stream);
            fwrite(&settings::aimbot::aimbot_fov, sizeof(bool), 1, p_stream);
            fwrite(&settings::aimbot::aimbot_smooth, sizeof(bool), 1, p_stream);
            fwrite(&settings::aimbot::aimbot_distance, sizeof(bool), 1, p_stream);
            fwrite(&settings::aimbot::prediction, sizeof(bool), 1, p_stream);
            fwrite(&settings::visuals::preview_target, sizeof(bool), 1, p_stream);
            fwrite(&settings::visuals::preview_style, sizeof(bool), 1, p_stream);
            fwrite(&settings::aimbot::aimbot_type, sizeof(bool), 1, p_stream);
            fwrite(&settings::aimbot::aimbot_target, sizeof(bool), 1, p_stream);
            fwrite(&settings::aimbot::aimbot_bone, sizeof(bool), 1, p_stream);
            fwrite(&settings::aimbot::only_visible, sizeof(bool), 1, p_stream);
            fwrite(&settings::aimbot::avoid_invisible, sizeof(bool), 1, p_stream);
            fwrite(&settings::aimbot::avoid_target_friend, sizeof(bool), 1, p_stream);

            fwrite(&settings::visuals::enabled, sizeof(bool), 1, p_stream);
            fwrite(&settings::visuals::visible_check, sizeof(bool), 1, p_stream);
            fwrite(&settings::visuals::visible_check_type, sizeof(bool), 1, p_stream);
            fwrite(&settings::visuals::invisible_check, sizeof(bool), 1, p_stream);
            fwrite(&settings::visuals::invisible_check_type, sizeof(bool), 1, p_stream);
            fwrite(&settings::visuals::friend_visuals, sizeof(bool), 1, p_stream);
            fwrite(&settings::visuals::friend_visuals_check_type, sizeof(bool), 1, p_stream);
            fwrite(&settings::visuals::box_esp, sizeof(bool), 1, p_stream);
            fwrite(&settings::visuals::box_rounding, sizeof(bool), 1, p_stream);
            fwrite(&settings::visuals::box_size, sizeof(bool), 1, p_stream);
            fwrite(&settings::visuals::filled_esp, sizeof(bool), 1, p_stream);
            fwrite(&settings::visuals::skeleton_esp, sizeof(bool), 1, p_stream);
            fwrite(&settings::visuals::health_bar, sizeof(bool), 1, p_stream);
            fwrite(&settings::visuals::healthbar_type, sizeof(bool), 1, p_stream);
            fwrite(&settings::visuals::player_name, sizeof(bool), 1, p_stream);
            fwrite(&settings::visuals::health_text, sizeof(bool), 1, p_stream);
            fwrite(&settings::visuals::distance_text, sizeof(bool), 1, p_stream);
            fwrite(&settings::visuals::weapon_name, sizeof(bool), 1, p_stream);
            fwrite(&settings::visuals::snapline, sizeof(bool), 1, p_stream);
            fwrite(&settings::visuals::esp_distance, sizeof(bool), 1, p_stream);
            fwrite(&settings::visuals::esp_type, sizeof(bool), 1, p_stream);
            fwrite(&settings::visuals::only_alive, sizeof(bool), 1, p_stream);
            fwrite(&settings::visuals::draw_peds, sizeof(bool), 1, p_stream);
            fwrite(&settings::visuals::draw_self, sizeof(bool), 1, p_stream);

            fwrite(&settings::visuals::vehicle::car_enabled, sizeof(bool), 1, p_stream);
            fwrite(&settings::visuals::vehicle::boat_enabled, sizeof(bool), 1, p_stream);
            fwrite(&settings::visuals::vehicle::heli_enabled, sizeof(bool), 1, p_stream);

            fwrite(&settings::self::enabled, sizeof(bool), 1, p_stream);
            fwrite(&settings::self::godmode, sizeof(bool), 1, p_stream);
            fwrite(&settings::self::invisible, sizeof(bool), 1, p_stream);
            fwrite(&settings::self::no_hs, sizeof(bool), 1, p_stream);
            fwrite(&settings::self::no_ragdoll, sizeof(bool), 1, p_stream);
            fwrite(&settings::self::infinite_stamina, sizeof(bool), 1, p_stream);
            fwrite(&settings::self::desync, sizeof(bool), 1, p_stream);
            fwrite(&settings::self::noclip, sizeof(bool), 1, p_stream);
            fwrite(&settings::self::hotkey_noclip, sizeof(bool), 1, p_stream);
            fwrite(&settings::self::hotkey_forward, sizeof(bool), 1, p_stream);
            fwrite(&settings::self::hotkey_backward, sizeof(bool), 1, p_stream);
            fwrite(&settings::self::hotkey_left, sizeof(bool), 1, p_stream);
            fwrite(&settings::self::hotkey_right, sizeof(bool), 1, p_stream);

            fwrite(&settings::weapon::enabled, sizeof(bool), 1, p_stream);
            fwrite(&settings::weapon::no_recoil, sizeof(bool), 1, p_stream);
            fwrite(&settings::weapon::no_reload, sizeof(bool), 1, p_stream);
            fwrite(&settings::weapon::no_spread, sizeof(bool), 1, p_stream);
            fwrite(&settings::weapon::recoil_value, sizeof(bool), 1, p_stream);
            fwrite(&settings::weapon::reload_value, sizeof(bool), 1, p_stream);
            fwrite(&settings::weapon::spread_value, sizeof(bool), 1, p_stream);
            fwrite(&settings::weapon::weapon_range, sizeof(bool), 1, p_stream);
            fwrite(&settings::weapon::damage_boost, sizeof(bool), 1, p_stream);
            fwrite(&settings::weapon::infite_ammo, sizeof(bool), 1, p_stream);

            fwrite(&settings::vehicle::enabled, sizeof(bool), 1, p_stream);
            fwrite(&settings::vehicle::auto_start_engine, sizeof(bool), 1, p_stream);
            fwrite(&settings::vehicle::auto_open_car, sizeof(bool), 1, p_stream);
            fwrite(&settings::vehicle::skip_animation, sizeof(bool), 1, p_stream);
            fwrite(&settings::vehicle::warp_on_key, sizeof(bool), 1, p_stream);
            fwrite(&settings::vehicle::key_warp, sizeof(bool), 1, p_stream);

            fwrite(&settings::visuals::crosshair, sizeof(bool), 1, p_stream);
            fwrite(&settings::visuals::crossahir_style, sizeof(bool), 1, p_stream);
            fwrite(&settings::misc::hotkey, sizeof(bool), 1, p_stream);
            fwrite(&settings::visuals::fov_circle, sizeof(bool), 1, p_stream);
            fwrite(&settings::visuals::fov_circle_filled, sizeof(bool), 1, p_stream);
            fwrite(&settings::visuals::hitsound, sizeof(bool), 1, p_stream);
            fwrite(&settings::visuals::hitsound_path, sizeof(bool), 1, p_stream);
            fwrite(&settings::misc::lock_menu_layout, sizeof(bool), 1, p_stream);
            fwrite(&settings::misc::menu_size_x, sizeof(bool), 1, p_stream);
            fwrite(&settings::misc::menu_size_y, sizeof(bool), 1, p_stream);
            if (p_stream)
            {

                fclose(p_stream);
            }
        }
        ImGui::Separator();

        for (const auto& entry : fs::directory_iterator(configs))
        {
            // Vérifie si l'extension du fichier est .txt
            if (entry.path().extension() == ".cfg")
            {

                // Ajoute le nom du fichier au tableau
                configFiles.push_back(entry.path().filename().string());

                // Ajoute le pointeur de chaîne correspondant au tableau de pointeurs de chaînes
                configFilesCStr.push_back(configFiles.back().c_str());

            }
        }


        static int selectedConfigIndex = -1;
        if (ImGui::BeginListBox("##Config List", ImVec2(ImGui::GetWindowWidth() - 20, ImGui::GetWindowHeight() / 2 - 20))) {
            for (int i = 0; i < configFilesCStr.size(); i++) {
                bool isSelected = (selectedConfigIndex == i);
                if (ImGui::Selectable(configFilesCStr[i], isSelected))
                    selectedConfigIndex = i;
                if (isSelected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndListBox();
        }

        if (selectedConfigIndex >= 0 && selectedConfigIndex < configFiles.size())
        {
            std::string selectedConfigName = configFiles[selectedConfigIndex];


            if (ImGui::Button(E("Load")))
            {
                FILE* p_stream;

                auto configPath = configs + "\\" + selectedConfigName;

                fopen_s(&p_stream, configPath.c_str(), "r+");

                // set file pointer to 0
                fseek(p_stream, 0, SEEK_SET);


                
                fread_s(&settings::aimbot::enabled, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::aimbot::hotkey, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::aimbot::aimbot_fov, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::aimbot::aimbot_smooth, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::aimbot::aimbot_distance, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::aimbot::prediction, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::aimbot::aimbot_type, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::aimbot::aimbot_target, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::aimbot::aimbot_bone, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::aimbot::only_visible, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::aimbot::avoid_invisible, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::aimbot::avoid_target_friend, sizeof(bool), sizeof(bool), 1, p_stream);

                fread_s(&settings::visuals::preview_target, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::visuals::preview_style, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::visuals::enabled, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::visuals::visible_check, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::visuals::visible_check_type, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::visuals::invisible_check, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::visuals::invisible_check_type, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::visuals::friend_visuals, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::visuals::friend_visuals_check_type, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::visuals::box_esp, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::visuals::box_rounding, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::visuals::box_size, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::visuals::filled_esp, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::visuals::skeleton_esp, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::visuals::health_bar, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::visuals::healthbar_type, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::visuals::player_name, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::visuals::health_text, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::visuals::distance_text, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::visuals::weapon_name, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::visuals::snapline, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::visuals::esp_distance, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::visuals::esp_type, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::visuals::only_alive, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::visuals::draw_peds, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::visuals::draw_self, sizeof(bool), sizeof(bool), 1, p_stream);

                fread_s(&settings::visuals::vehicle::car_enabled, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::visuals::vehicle::boat_enabled, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::visuals::vehicle::heli_enabled, sizeof(bool), sizeof(bool), 1, p_stream);

                fread_s(&settings::self::enabled, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::self::godmode, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::self::invisible, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::self::no_hs, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::self::no_ragdoll, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::self::infinite_stamina, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::self::desync, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::self::noclip, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::self::hotkey_noclip, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::self::hotkey_forward, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::self::hotkey_backward, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::self::hotkey_left, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::self::hotkey_right, sizeof(bool), sizeof(bool), 1, p_stream);

                fread_s(&settings::weapon::enabled, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::weapon::no_recoil, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::weapon::no_reload, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::weapon::no_spread, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::weapon::recoil_value, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::weapon::reload_value, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::weapon::spread_value, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::weapon::weapon_range, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::weapon::damage_boost, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::weapon::infite_ammo, sizeof(bool), sizeof(bool), 1, p_stream);

                fread_s(&settings::vehicle::enabled, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::vehicle::auto_start_engine, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::vehicle::auto_open_car, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::vehicle::skip_animation, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::vehicle::warp_on_key, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::vehicle::key_warp, sizeof(bool), sizeof(bool), 1, p_stream);

                fread_s(&settings::visuals::crosshair, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::visuals::crossahir_style, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::visuals::fov_circle, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::visuals::fov_circle_filled, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::visuals::hitsound, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::visuals::hitsound_path, sizeof(bool), sizeof(bool), 1, p_stream);

                fread_s(&settings::misc::hotkey, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::misc::lock_menu_layout, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::misc::menu_size_x, sizeof(bool), sizeof(bool), 1, p_stream);
                fread_s(&settings::misc::menu_size_y, sizeof(bool), sizeof(bool), 1, p_stream);


                fclose(p_stream);

            }

            ImGui::SameLine();
            if (ImGui::Button(E("Save")))
            {
                FILE* p_stream;

                auto configPath = configs +E("\\") + selectedConfigName;

                fopen_s(&p_stream, configPath.c_str(), "w+");

                // set file pointer to 0
                fseek(p_stream, 0, SEEK_SET);



                fwrite(&settings::aimbot::enabled, sizeof(bool), 1, p_stream);
                fwrite(&settings::aimbot::hotkey, sizeof(bool), 1, p_stream);
                fwrite(&settings::aimbot::aimbot_fov, sizeof(bool), 1, p_stream);
                fwrite(&settings::aimbot::aimbot_smooth, sizeof(bool), 1, p_stream);
                fwrite(&settings::aimbot::aimbot_distance, sizeof(bool), 1, p_stream);
                fwrite(&settings::aimbot::prediction, sizeof(bool), 1, p_stream);
                fwrite(&settings::visuals::preview_target, sizeof(bool), 1, p_stream);
                fwrite(&settings::visuals::preview_style, sizeof(bool), 1, p_stream);
                fwrite(&settings::aimbot::aimbot_type, sizeof(bool), 1, p_stream);
                fwrite(&settings::aimbot::aimbot_target, sizeof(bool), 1, p_stream);
                fwrite(&settings::aimbot::aimbot_bone, sizeof(bool), 1, p_stream);
                fwrite(&settings::aimbot::only_visible, sizeof(bool), 1, p_stream);
                fwrite(&settings::aimbot::avoid_invisible, sizeof(bool), 1, p_stream);
                fwrite(&settings::aimbot::avoid_target_friend, sizeof(bool), 1, p_stream);

                fwrite(&settings::visuals::enabled, sizeof(bool), 1, p_stream);
                fwrite(&settings::visuals::visible_check, sizeof(bool), 1, p_stream);
                fwrite(&settings::visuals::visible_check_type, sizeof(bool), 1, p_stream);
                fwrite(&settings::visuals::invisible_check, sizeof(bool), 1, p_stream);
                fwrite(&settings::visuals::invisible_check_type, sizeof(bool), 1, p_stream);
                fwrite(&settings::visuals::friend_visuals, sizeof(bool), 1, p_stream);
                fwrite(&settings::visuals::friend_visuals_check_type, sizeof(bool), 1, p_stream);
                fwrite(&settings::visuals::box_esp, sizeof(bool), 1, p_stream);
                fwrite(&settings::visuals::box_rounding, sizeof(bool), 1, p_stream);
                fwrite(&settings::visuals::box_size, sizeof(bool), 1, p_stream);
                fwrite(&settings::visuals::filled_esp, sizeof(bool), 1, p_stream);
                fwrite(&settings::visuals::skeleton_esp, sizeof(bool), 1, p_stream);
                fwrite(&settings::visuals::health_bar, sizeof(bool), 1, p_stream);
                fwrite(&settings::visuals::healthbar_type, sizeof(bool), 1, p_stream);
                fwrite(&settings::visuals::player_name, sizeof(bool), 1, p_stream);
                fwrite(&settings::visuals::health_text, sizeof(bool), 1, p_stream);
                fwrite(&settings::visuals::distance_text, sizeof(bool), 1, p_stream);
                fwrite(&settings::visuals::weapon_name, sizeof(bool), 1, p_stream);
                fwrite(&settings::visuals::snapline, sizeof(bool), 1, p_stream);
                fwrite(&settings::visuals::esp_distance, sizeof(bool), 1, p_stream);
                fwrite(&settings::visuals::esp_type, sizeof(bool), 1, p_stream);
                fwrite(&settings::visuals::only_alive, sizeof(bool), 1, p_stream);
                fwrite(&settings::visuals::draw_peds, sizeof(bool), 1, p_stream);
                fwrite(&settings::visuals::draw_self, sizeof(bool), 1, p_stream);

                fwrite(&settings::visuals::vehicle::car_enabled, sizeof(bool), 1, p_stream);
                fwrite(&settings::visuals::vehicle::boat_enabled, sizeof(bool), 1, p_stream);
                fwrite(&settings::visuals::vehicle::heli_enabled, sizeof(bool), 1, p_stream);

                fwrite(&settings::self::enabled, sizeof(bool), 1, p_stream);
                fwrite(&settings::self::godmode, sizeof(bool), 1, p_stream);
                fwrite(&settings::self::invisible, sizeof(bool), 1, p_stream);
                fwrite(&settings::self::no_hs, sizeof(bool), 1, p_stream);
                fwrite(&settings::self::no_ragdoll, sizeof(bool), 1, p_stream);
                fwrite(&settings::self::infinite_stamina, sizeof(bool), 1, p_stream);
                fwrite(&settings::self::desync, sizeof(bool), 1, p_stream);
                fwrite(&settings::self::noclip, sizeof(bool), 1, p_stream);
                fwrite(&settings::self::hotkey_noclip, sizeof(bool), 1, p_stream);
                fwrite(&settings::self::hotkey_forward, sizeof(bool), 1, p_stream);
                fwrite(&settings::self::hotkey_backward, sizeof(bool), 1, p_stream);
                fwrite(&settings::self::hotkey_left, sizeof(bool), 1, p_stream);
                fwrite(&settings::self::hotkey_right, sizeof(bool), 1, p_stream);

                fwrite(&settings::weapon::enabled, sizeof(bool), 1, p_stream);
                fwrite(&settings::weapon::no_recoil, sizeof(bool), 1, p_stream);
                fwrite(&settings::weapon::no_reload, sizeof(bool), 1, p_stream);
                fwrite(&settings::weapon::no_spread, sizeof(bool), 1, p_stream);
                fwrite(&settings::weapon::recoil_value, sizeof(bool), 1, p_stream);
                fwrite(&settings::weapon::reload_value, sizeof(bool), 1, p_stream);
                fwrite(&settings::weapon::spread_value, sizeof(bool), 1, p_stream);
                fwrite(&settings::weapon::weapon_range, sizeof(bool), 1, p_stream);
                fwrite(&settings::weapon::damage_boost, sizeof(bool), 1, p_stream);
                fwrite(&settings::weapon::infite_ammo, sizeof(bool), 1, p_stream);

                fwrite(&settings::vehicle::enabled, sizeof(bool), 1, p_stream);
                fwrite(&settings::vehicle::auto_start_engine, sizeof(bool), 1, p_stream);
                fwrite(&settings::vehicle::auto_open_car, sizeof(bool), 1, p_stream);
                fwrite(&settings::vehicle::skip_animation, sizeof(bool), 1, p_stream);
                fwrite(&settings::vehicle::warp_on_key, sizeof(bool), 1, p_stream);
                fwrite(&settings::vehicle::key_warp, sizeof(bool), 1, p_stream);

                fwrite(&settings::visuals::crosshair, sizeof(bool), 1, p_stream);
                fwrite(&settings::visuals::crossahir_style, sizeof(bool), 1, p_stream);
                fwrite(&settings::misc::hotkey, sizeof(bool), 1, p_stream);
                fwrite(&settings::visuals::fov_circle, sizeof(bool), 1, p_stream);
                fwrite(&settings::visuals::fov_circle_filled, sizeof(bool), 1, p_stream);
                fwrite(&settings::visuals::hitsound, sizeof(bool), 1, p_stream);
                fwrite(&settings::visuals::hitsound_path, sizeof(bool), 1, p_stream);
                fwrite(&settings::misc::lock_menu_layout, sizeof(bool), 1, p_stream);
                fwrite(&settings::misc::menu_size_x, sizeof(bool), 1, p_stream);
                fwrite(&settings::misc::menu_size_y, sizeof(bool), 1, p_stream);

                fclose(p_stream);

            }
            ImGui::SameLine();
            if (ImGui::Button("Delete"))
            {
                auto configPath = configs + "\\" + selectedConfigName;

                remove(configPath.c_str());

            }

        }

 
	}
}