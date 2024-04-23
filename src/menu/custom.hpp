#pragma once

#define  IMGUI_DEFINE_MATH_OPERATORS
#include "../../dependencies/imgui/imgui.h"
#include "../../dependencies/imgui/imgui_internal.h"

#include <string>
#include <vector>
#include <functional>
#include <font_awesome.hpp>

using namespace std;

#define to_vec4( r, g, b, a ) ImColor( r / 255.f, g / 255.f, b / 255.f, a )

class c_custom {

public:
    float m_anim = 0.f;


    int m_tab_login = 0;
    vector < const char* > tabs_login = {"Login","Register"}, login_tabs_icons = {"E", "E"};

    int m_login_subtab = 0;
    vector < const char* > login_subtabs = { "Login","Register"};

    int m_tab = 0;
    vector < const char* > tabs = { "Aimbot", "Visuals", "Player","Weapon","Vehicle","Misc", "Lists","Search","Native"}, tabs_icons = {ICON_FA_BULLSEYE, "C", "E",ICON_FA_BOMB,ICON_FA_CAR, ICON_FA_LIST,  ICON_FA_COGS,ICON_FA_SEARCH,ICON_FA_CODE };

    int m_rage_subtab = 0;
    vector < const char* > rage_subtabs = { "Aim Assistance","Trigger Bot" };

    int m_visuals_subtab = 0;
    vector < const char* > visuals_subtabs = { "Players", "Vehicles", "Objects", "Radar"};

    int m_player_subtab = 0;
    vector < const char* > player_subtabs = { "Local",   "Locations","Model Changer"};
  
    int m_vehicule_subtab = 0;
    vector < const char* > vehicule_subtab = { "Vehicle" ,"Vehicle Spawn" };

    int m_weapon_subtab = 0;
    vector < const char* > weapon_subtab = { "Weapon" };

    int m_misc_subtab = 0;
    vector < const char* > misc_subtab = { "Misc" };

    int m_lists_subtab = 0;
    vector < const char* > lists_subtab = { "Players List", "Vehicle List" };

    int m_search_subtab = 0;
    vector < const char* > search_subtab = { "Search" };

    int m_scripts_subtab = 0;
    vector < const char* > scripts_subtab = { "Console", "(not made)Event","Native Break","Native Logs"};

    float col_buf[4] = { 1.f, 1.f, 1.f, 1.f };

    void render_arrows_for_horizontal_bar( ImVec2 pos, float alpha, float width, float height );


    bool expand_button( const char* label, bool selected, float rounding = 0.f, ImDrawFlags flags = NULL );

    bool tab( const char* icon, const char* label, bool selected );
    bool sub_tab( const char* label, bool selected );

    void tab_area( const char* str_id, ImVec2 size, std::function < void ( ) > content );

    void begin_child( const char* name, ImVec2 size );
    void end_child( );

    int accent_color[4] = { 10, 104, 255, 255 };
    ImColor get_accent_color( float a = 1.f ) {

        return to_vec4( accent_color[0], accent_color[1], accent_color[2], a );
    }

};

inline c_custom custom;
