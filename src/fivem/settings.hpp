#pragma once
#include <joaat.hpp>

namespace settings {
	inline std::string windows_name = "";
	inline std::string user_name = "";
	inline bool init = false;
	inline int auth = 0;
	inline bool can_use_menu = false;

	namespace aimbot {
		inline bool enabled = false;

		inline bool only_visible = false;
		inline bool avoid_invisible = false;
		inline bool target_godmode = false;
		inline bool avoid_target_friend = false;
		inline bool triggerbot = false;
		inline bool delay = false;
		inline int triggerbot_delay = 1;


		inline int hotkey = 2;

		inline int aimbot_fov = 5;
		inline int magic_fov = 5;

		inline int aimbot_smooth = 2;
		inline float curve = 0;
		inline int aimbot_target = 0;
		inline const char* aimbot_target_list[]{ "All", "Only Player", "Only Ped" };


		inline int aimbot_distance = 150;

		inline int aimbot_bone = 0;
		inline const char* aimbot_bones_list[]{ "Head", "Neck", "Body", "Leg left", "Leg right", "Arm right", "Arm left" };

		inline int aimbot_type = 0;
		inline const char* aimbot_type_list[]{ "Mouse", "Memory","Silent","Magic" };
		inline bool silent = false;
		inline int magic_aimbot_type = 0;
		inline const char* magic_aimbot_type_list[]{ "Silent","Magic" };

		inline int aimbot_selection = 0;

		inline bool prediction = false;
	}

	namespace visuals {
		namespace radar {

			inline bool enabled = false;

			inline bool render_ped = false;
			inline bool render_dead = false;

			inline int size_x = 250;
			inline int size_y = 250;

			inline int zoom = 5;

			inline int opacity = 100;

			inline bool draw_vehicle = false;

			inline ImColor player_dot_circle = ImColor(255, 255, 255, 255);
			inline ImColor local_player_dot_circle = ImColor(255, 0, 0, 255);
			inline ImColor target_player_dot_circle = ImColor(255, 0, 0, 255);


		}
		inline bool enabled = false;
		inline int esp_distance = 250;

		inline bool visible_check = false;
		inline int visible_check_type = 0;
		inline const char* visible_check_choice_text[]{ "Visible Only", "Visible / No Visible" };

		inline bool invisible_check = false;
		inline int invisible_check_type = 0;
		inline const char* invisible_check_type_text[]{ "Don't Draw Invisible", "Different Colors" };

		inline bool friend_visuals = false;
		inline int friend_visuals_check_type = 0;
		inline const char* friend_visuals_check_type_text[]{ "Don't Draw Friends", "Different Colors" };
		
		inline bool Preview = false;

		inline bool only_alive = false;
		inline bool draw_self = false;
		inline bool draw_peds = false;

		inline bool box_esp = false;
		inline bool filled_esp = false;
		inline bool skeleton_esp = false;
		inline bool circle_skeleton_head = false;
		inline bool health_bar = false;
		inline bool armor_bar = false;
		inline bool health_text = false;
		inline bool player_name = false;
		inline bool distance_text = false;
		inline bool weapon_name = false;
		inline bool snapline = false;

		inline int nane_type = 0;
		inline const char* name_type_text[]{ "Up", "Down" };

		inline int healthbar_type = 0;
		inline const char* healthbar_type_text[]{ "Right", "Left", "Down" };
		inline int box_rounding = 1;
		inline float Dynamicdebug = 1;

		inline bool preview_target = false;
		inline int preview_style = 0;
		inline const char* ssxs[]{ "Dot", "Line", "Both" };

		inline bool fov_circle = false;
		inline bool fov_circle_filled = false;

		inline bool magic_fov_circle = false;
		inline bool magic_fov_circle_filled = false;
		inline bool crosshair = false;
		inline int crossahir_style = 0;
		inline const char* sss[]{ "Dot", "Cross" };

		inline float tickness = 0.5f;

		inline const char* esp_type_text[]{ "Dynamic", "Static" };
		inline int esp_type = 0;

		inline float box_size = 2.00f;

		inline int debug_int_1 = 4;
		inline int debug_int_2 = 5;
		inline float debug_flot_1 = 2.00f;

		inline bool outlined = true;
		inline bool outlined_text = true;

		inline bool loc_visuals = true;

		inline bool hitsound = false;
		char hitsound_path[50] = "C:\\Alprazolam\\skeet.wav";

		namespace object {
			inline bool object_esp = false;

			inline bool distance = false;
			inline bool marker = false;
			inline bool snapline = false;
		}

		namespace vehicle {
			inline bool main_enabled = false;

			inline bool car_enabled = false;
			inline bool car_marker = false;
			inline bool car_distance = false;
			inline bool car_show_only_occuped = false;
			inline bool car_show_plate = false;
			inline bool car_lock = false;

			inline bool boat_enabled = false;
			inline bool boat_marker = false;
			inline bool boat_distance = false;
			inline bool boat_show_only_occuped = false;
			inline bool boat_show_plate = false;
			inline bool boat_lock = false;

			inline bool heli_enabled = false;
			inline bool heli_marker = false;
			inline bool heli_distance = false;
			inline bool heli_show_only_occuped = false;
			inline bool heli_show_plate = false;
			inline bool heli_lock = false;

			inline int selected = -1;
			inline const char* model[]{ "Generic", "Boat", "Helicopter" };
		}

		inline ImColor box_color = ImColor(255, 255, 255, 150);
		inline ImColor filled_color = ImColor(0, 0, 0, 30);
		inline ImColor distance_color = ImColor(255, 255, 255, 255);
		inline ImColor health_color = ImColor(255, 255, 255, 255);
		inline ImColor player_name_color = ImColor(255, 255, 255, 255);
		inline ImColor weapon_name_color = ImColor(255, 255, 255, 255);
		inline ImColor skeleton_color = ImColor(255, 255, 255, 255);
		inline ImColor snapline_color = ImColor(255, 255, 255, 255);

		inline ImColor crosshair_color = ImColor(255, 255, 255, 255);
		inline ImColor preview_target_colors = ImColor(255, 255, 255, 255);

		inline ImColor box_color_visible = ImColor(255, 255, 255, 255);
		inline ImColor filled_color_visible = ImColor(0, 0, 0, 30);
		inline ImColor distance_color_visible = ImColor(255, 255, 255, 255);
		inline ImColor health_color_visible = ImColor(255, 255, 255, 255);
		inline ImColor player_name_color_visible = ImColor(255, 255, 255, 255);
		inline ImColor weapon_name_color_visible = ImColor(255, 255, 255, 255);
		inline ImColor skeleton_color_visible = ImColor(255, 255, 255, 255);
		inline ImColor snapline_color_visible = ImColor(255, 255, 255, 255);

		inline ImColor invisible_color = ImColor(255, 255, 255, 255);

		inline ImColor fov_color = ImColor(255, 255, 255, 255);
		inline ImColor magic_color = ImColor(255, 255, 255, 255);

		inline ImColor visible = ImColor(255, 255, 255, 255);
		inline ImColor invisible = ImColor(255, 255, 255, 255);

		inline ImColor lines_colors = ImColor(255, 255, 255, 255);

		inline ImColor friends_colors = ImColor(255, 255, 255, 255);
	}

	namespace self {
		inline bool enabled = false;

		inline bool godmode = false;
		inline bool invisible = false;
		inline bool no_hs = false;
		inline bool no_ragdoll = false;
		inline bool never_wanted = false;
		inline bool desync = false;
		inline int yaw = 0;
		inline bool random = false;
		inline bool infinite_stamina = false;
		inline bool revive = false;
		inline bool teleport_to_waypoint = false;
		inline bool physic_gun = false;
		inline bool freecam = false;
		inline int FreeCamInt = 0;
		inline const char* FreeCamType[]{ "<- Selected : Pistol Ammo ->",  "<- Selected : Explosive Ammo ->",  "<- Selected : Molotov Ammo ->",  "<- Selected : Taze Player ->", "<- Selected : Create Ped ->" ,  "<- Selected : Create Vehicle  ->" , "<- Selected : PhysGun  ->" };
		inline bool give_health = false;
		inline bool give_armor = false;

		inline int give_health_amnt = 100;
		inline int give_armor_amnt = 100;
		inline bool rc_car = false;
		inline bool noclip = false;
		inline int noclip_type = 0;
		inline const char* noclip_type_text[]{ "Camera", "Directional" };
		inline int hotkey_noclip = 0;

		inline int hotkey_forward = 0;
		inline int hotkey_left = 0;
		inline int hotkey_right = 0;
		inline int hotkey_backward = 0;

		inline bool freeze = false;
		inline bool un_freeze = false;
		namespace model_changer
		{
			inline bool ModelChange = false;
			inline int ModelPos = 0;
			rage::joaat_t ModelJoat;

			inline const char* Model[]{ //Model Changer
	"A_C_Boar","A_C_Chickenhawk","A_C_Chimp","A_C_Chop","A_C_Cormorant","A_C_Cow","A_C_Coyote","A_C_Crow","A_C_Deer","A_C_Fish","A_C_Hen","A_C_Husky","A_C_MtLion","A_C_Pig","A_C_Pigeon","A_C_Rat","A_C_Retriever",
	"A_C_Rhesus","A_C_Rottweiler","A_C_Seagull","A_C_SharkTiger","A_C_shepherd","A_F_M_Beach_01","A_F_M_BevHills_01","A_F_M_BevHills_02","A_F_M_BodyBuild_01","A_F_M_Business_02","A_F_M_Downtown_01","A_F_M_EastSA_01",
	"A_F_M_EastSA_02","A_F_M_FatBla_01","A_F_M_FatCult_01","A_F_M_FatWhite_01","A_F_M_KTown_01","A_F_M_KTown_02","A_F_M_ProlHost_01","A_F_M_Salton_01","A_F_M_SkidRow_01","A_F_M_SouCentMC_01","A_F_M_SouCent_01","A_F_M_SouCent_02",
	"A_F_M_Tourist_01","A_F_M_TrampBeac_01","A_F_M_Tramp_01","A_F_O_GenStreet_01","A_F_O_Indian_01","A_F_O_KTown_01","A_F_O_Salton_01","A_F_O_SouCent_01","A_F_O_SouCent_02","A_F_Y_Beach_01","A_F_Y_BevHills_01","A_F_Y_BevHills_02",
	"A_F_Y_BevHills_03","A_F_Y_BevHills_04","A_F_Y_Business_01","A_F_Y_Business_02","A_F_Y_Business_03","A_F_Y_Business_04","A_F_Y_EastSA_01","A_F_Y_EastSA_02","A_F_Y_EastSA_03","A_F_Y_Epsilon_01","A_F_Y_Fitness_01",
	"A_F_Y_Fitness_02","A_F_Y_GenHot_01","A_F_Y_Golfer_01","A_F_Y_Hiker_01","A_F_Y_Hippie_01","A_F_Y_Hipster_01","A_F_Y_Hipster_02","A_F_Y_Hipster_03","A_F_Y_Hipster_04","A_F_Y_Indian_01","A_F_Y_Juggalo_01","A_F_Y_Runner_01",
	"A_F_Y_RurMeth_01","A_F_Y_SCDressy_01","A_F_Y_Skater_01","A_F_Y_SouCent_01","A_F_Y_SouCent_02","A_F_Y_SouCent_03","A_F_Y_Tennis_01","A_F_Y_Topless_01","A_F_Y_Tourist_01","A_F_Y_Tourist_02","A_F_Y_Vinewood_01",
	"A_F_Y_Vinewood_02","A_F_Y_Vinewood_03","A_F_Y_Vinewood_04","A_F_Y_Yoga_01","A_M_M_ACult_01","A_M_M_AfriAmer_01","A_M_M_Beach_01","A_M_M_Beach_02","A_M_M_BevHills_01","A_M_M_BevHills_02","A_M_M_Business_01",
	"A_M_M_EastSA_01","A_M_M_EastSA_02","A_M_M_Farmer_01","A_M_M_FatLatin_01","A_M_M_GenFat_01","A_M_M_GenFat_02","A_M_M_Golfer_01","A_M_M_HasJew_01","A_M_M_Hillbilly_01","A_M_M_Hillbilly_02","A_M_M_Indian_01",
	"A_M_M_KTown_01","A_M_M_Malibu_01","A_M_M_MexCntry_01","A_M_M_MexLabor_01","A_M_M_OG_Boss_01","A_M_M_Paparazzi_01","A_M_M_Polynesian_01","A_M_M_ProlHost_01","A_M_M_RurMeth_01","A_M_M_Salton_01","A_M_M_Salton_02",
	"A_M_M_Salton_03","A_M_M_Salton_04","A_M_M_Skater_01","A_M_M_Skidrow_01","A_M_M_SoCenLat_01","A_M_M_SouCent_01","A_M_M_SouCent_02","A_M_M_SouCent_03","A_M_M_SouCent_04","A_M_M_StLat_02","A_M_M_Tennis_01",
	"A_M_M_Tourist_01","A_M_M_TrampBeac_01","A_M_M_Tramp_01","A_M_M_TranVest_01","A_M_M_TranVest_02","A_M_O_ACult_01","A_M_O_ACult_02","A_M_O_Beach_01","A_M_O_GenStreet_01","A_M_O_KTown_01","A_M_O_Salton_01",
	"A_M_O_SouCent_01","A_M_O_SouCent_02","A_M_O_SouCent_03","A_M_O_Tramp_01","A_M_Y_ACult_01","A_M_Y_ACult_02","A_M_Y_BeachVesp_01","A_M_Y_BeachVesp_02","A_M_Y_Beach_01","A_M_Y_Beach_02","A_M_Y_Beach_03","A_M_Y_BevHills_01",
	"A_M_Y_BevHills_02","A_M_Y_BreakDance_01","A_M_Y_BusiCas_01","A_M_Y_Business_01","A_M_Y_Business_02","A_M_Y_Business_03","A_M_Y_Cyclist_01","A_M_Y_DHill_01","A_M_Y_Downtown_01","A_M_Y_EastSA_01","A_M_Y_EastSA_02",
	"A_M_Y_Epsilon_01","A_M_Y_Epsilon_02","A_M_Y_Gay_01","A_M_Y_Gay_02","A_M_Y_GenStreet_01","A_M_Y_GenStreet_02","A_M_Y_Golfer_01","A_M_Y_HasJew_01","A_M_Y_Hiker_01","A_M_Y_Hippy_01","A_M_Y_Hipster_01","A_M_Y_Hipster_02",
	"A_M_Y_Hipster_03","A_M_Y_Indian_01","A_M_Y_Jetski_01","A_M_Y_Juggalo_01","A_M_Y_KTown_01","A_M_Y_KTown_02","A_M_Y_Latino_01","A_M_Y_MethHead_01","A_M_Y_MexThug_01","A_M_Y_MotoX_01","A_M_Y_MotoX_02","A_M_Y_MusclBeac_01",
	"A_M_Y_MusclBeac_02","A_M_Y_Polynesian_01","A_M_Y_RoadCyc_01","A_M_Y_Runner_01","A_M_Y_Runner_02","A_M_Y_Salton_01","A_M_Y_Skater_01","A_M_Y_Skater_02","A_M_Y_SouCent_01","A_M_Y_SouCent_02","A_M_Y_SouCent_03","A_M_Y_SouCent_04",
	"A_M_Y_StBla_01","A_M_Y_StBla_02","A_M_Y_StLat_01","A_M_Y_StWhi_01","A_M_Y_StWhi_02","A_M_Y_Sunbathe_01","A_M_Y_Surfer_01","A_M_Y_VinDouche_01","A_M_Y_Vinewood_01","A_M_Y_Vinewood_02","A_M_Y_Vinewood_03","A_M_Y_Vinewood_04",
	"A_M_Y_Yoga_01","CSB_Abigail","CSB_Anita","CSB_Anton","CSB_BallasOG","CSB_Bride","CSB_BurgerDrug","CSB_Car3guy1","CSB_Car3guy2","CSB_Chef","CSB_Chin_goon","CSB_Cletus","CSB_Cop","CSB_Customer","CSB_Denise_friend",
	"CSB_FOS_rep","CSB_G","CSB_Groom","CSB_Grove_str_dlr","CSB_Hao","CSB_Hugh","CSB_Imran","CSB_Janitor","CSB_Maude","CSB_MWeather","CSB_Ortega","CSB_Oscar","CSB_PornDudes","CSB_PrologueDriver","CSB_ProlSec","CSB_Ramp_gang",
	"CSB_Ramp_hic","CSB_Ramp_hipster","CSB_Ramp_marine","CSB_Ramp_mex","CSB_Reporter","CSB_RoccoPelosi","CSB_Screen_Writer","CSB_Stripper_01","CSB_Stripper_02","CSB_Tonya","CSB_TrafficWarden","CS_AmandaTownley","CS_Andreas",
	"cs_ashley","CS_Bankman","CS_Barry","CS_Beverly","CS_Brad","CS_BradCadaver","CS_Carbuyer","CS_Casey","CS_ChengSr","CS_ChrisFormage","CS_Clay","CS_Dale","CS_DaveNorton","cs_debra","cs_denise","CS_Devin","CS_Dom","CS_Dreyfuss",
	"CS_DrFriedlander","CS_Fabien","CS_FBISuit_01","CS_Floyd","CS_Guadalope","cs_gurk","CS_Hunter","CS_Janet","CS_JewelAss","CS_JimmyBoston","CS_JimmyDiSanto","CS_JoeMinuteMan","CS_JohnnyKlebitz","CS_Josef","CS_Josh","CS_LamarDavis",
	"CS_Lazlow","CS_LesterCrest","CS_LifeInvad_01","CS_Magenta","CS_Manuel","CS_Marnie","CS_MartinMadrazo","CS_MaryAnn","CS_Michelle","CS_Milton","CS_Molly","CS_MovPremF_01","CS_MovPremMale","CS_MRK","CS_MrsPhillips","CS_MRS_Thornhill",
	"CS_Natalia","CS_NervousRon","CS_Nigel","CS_Old_Man1A","CS_Old_Man2","CS_Omega","CS_Orleans","CS_Paper","CS_Patricia","CS_Priest","CS_ProlSec_02","CS_RussianDrunk","CS_SiemonYetarian","CS_Solomon","CS_SteveHains","CS_Stretch",
	"CS_Tanisha","CS_TaoCheng","CS_TaosTranslator","CS_TennisCoach","CS_Terry","CS_Tom","CS_TomEpsilon","CS_TracyDiSanto","CS_Wade","CS_Zimbor","G_F_Y_ballas_01","G_F_Y_Families_01","G_F_Y_Lost_01","G_F_Y_Vagos_01","G_M_M_ArmBoss_01",
	"G_M_M_ArmGoon_01","G_M_M_ArmLieut_01","G_M_M_ChemWork_01","G_M_M_ChiBoss_01","G_M_M_ChiCold_01","G_M_M_ChiGoon_01","G_M_M_ChiGoon_02","G_M_M_KorBoss_01","G_M_M_MexBoss_01","G_M_M_MexBoss_02","G_M_Y_ArmGoon_02","G_M_Y_Azteca_01",
	"G_M_Y_BallaEast_01","G_M_Y_BallaOrig_01","G_M_Y_BallaSout_01","G_M_Y_FamCA_01","G_M_Y_FamDNF_01","G_M_Y_FamFor_01","G_M_Y_Korean_01","G_M_Y_Korean_02","G_M_Y_KorLieut_01","G_M_Y_Lost_01","G_M_Y_Lost_02","G_M_Y_Lost_03",
	"G_M_Y_MexGang_01","G_M_Y_MexGoon_01","G_M_Y_MexGoon_02","G_M_Y_MexGoon_03","G_M_Y_PoloGoon_01","G_M_Y_PoloGoon_02","G_M_Y_SalvaBoss_01","G_M_Y_SalvaGoon_01","G_M_Y_SalvaGoon_02","G_M_Y_SalvaGoon_03","G_M_Y_StrPunk_01","G_M_Y_StrPunk_02",
	"HC_Driver","HC_Gunman","HC_Hacker","IG_Abigail","IG_AmandaTownley","IG_Andreas","IG_Ashley","IG_BallasOG","IG_Bankman","IG_Barry","IG_BestMen","IG_Beverly","IG_Brad","IG_Bride","IG_Car3guy1","IG_Car3guy2","IG_Casey",
	"IG_Chef","IG_ChengSr","IG_ChrisFormage","IG_Clay","IG_ClayPain","IG_Cletus","IG_Dale","IG_DaveNorton","IG_Denise","IG_Devin","IG_Dom","IG_Dreyfuss","IG_DrFriedlander","IG_Fabien","IG_FBISuit_01","IG_Floyd","IG_Groom",
	"IG_Hao","IG_Hunter","IG_Janet","ig_JAY_Norris","IG_JewelAss","IG_JimmyBoston","IG_JimmyDiSanto","IG_JoeMinuteMan","ig_JohnnyKlebitz","IG_Josef","IG_Josh","IG_KerryMcIntosh","IG_LamarDavis","IG_Lazlow","IG_LesterCrest",
	"IG_LifeInvad_01","IG_LifeInvad_02","IG_Magenta","IG_Manuel","IG_Marnie","IG_MaryAnn","IG_Maude","IG_Michelle","IG_Milton","IG_Molly","IG_MRK","IG_MrsPhillips","IG_MRS_Thornhill","IG_Natalia","IG_NervousRon","IG_Nigel",
	"IG_Old_Man1A","IG_Old_Man2","IG_Omega","IG_ONeil","IG_Orleans","IG_Ortega","IG_Paper","IG_Patricia","IG_Priest","IG_ProlSec_02","IG_Ramp_Gang","IG_Ramp_Hic","IG_Ramp_Hipster","IG_Ramp_Mex","IG_RoccoPelosi","IG_RussianDrunk",
	"IG_Screen_Writer","IG_SiemonYetarian","IG_Solomon","IG_SteveHains","IG_Stretch","IG_Talina","IG_Tanisha","IG_TaoCheng","IG_TaosTranslator","ig_TennisCoach","IG_Terry","IG_TomEpsilon","IG_Tonya","IG_TracyDiSanto","IG_TrafficWarden",
	"IG_TylerDix","IG_Wade","IG_Zimbor","MP_F_DeadHooker","MP_F_Freemode_01","MP_F_Misty_01","MP_F_StripperLite","MP_G_M_Pros_01","MP_HeadTargets","MP_M_Claude_01","MP_M_ExArmy_01","MP_M_FamDD_01","MP_M_FIBSec_01","MP_M_Freemode_01",
	"MP_M_Marston_01","MP_M_Niko_01","MP_M_ShopKeep_01","MP_S_M_Armoured_01","Player_One","Player_Two","Player_Zero","slod_human","slod_large_quadped","slod_small_quadped","S_F_M_Fembarber","S_F_M_Maid_01","S_F_M_Shop_HIGH",
	"S_F_M_SweatShop_01","S_F_Y_AirHostess_01","S_F_Y_Bartender_01","S_F_Y_Baywatch_01","S_F_Y_Cop_01","S_F_Y_Factory_01","S_F_Y_Hooker_01","S_F_Y_Hooker_02","S_F_Y_Hooker_03","S_F_Y_Migrant_01","S_F_Y_MovPrem_01","S_F_Y_Ranger_01",
	"S_F_Y_Scrubs_01","S_F_Y_Sheriff_01","S_F_Y_Shop_LOW","S_F_Y_Shop_MID","S_F_Y_StripperLite","S_F_Y_Stripper_01","S_F_Y_Stripper_02","S_F_Y_SweatShop_01","S_M_M_AmmuCountry","S_M_M_Armoured_01","S_M_M_Armoured_02","S_M_M_AutoShop_01",
	"S_M_M_AutoShop_02","S_M_M_Bouncer_01","S_M_M_ChemSec_01","S_M_M_CIASec_01","S_M_M_CntryBar_01","S_M_M_DockWork_01","S_M_M_Doctor_01","S_M_M_FIBOffice_01","S_M_M_FIBOffice_02","S_M_M_Gaffer_01","S_M_M_Gardener_01","S_M_M_GenTransport",
	"S_M_M_HairDress_01","S_M_M_HighSec_01","S_M_M_HighSec_02","S_M_M_Janitor","S_M_M_LatHandy_01","S_M_M_LifeInvad_01","S_M_M_Linecook","S_M_M_LSMetro_01","S_M_M_Mariachi_01","S_M_M_Marine_01","S_M_M_Marine_02","S_M_M_Migrant_01",
	"S_M_M_MovAlien_01","S_M_M_MovPrem_01","S_M_M_MovSpace_01","S_M_M_Paramedic_01","S_M_M_Pilot_01","S_M_M_Pilot_02","S_M_M_Postal_01","S_M_M_Postal_02","S_M_M_PrisGuard_01","S_M_M_Scientist_01","S_M_M_Security_01","S_M_M_SnowCop_01",
	"S_M_M_StrPerf_01","S_M_M_StrPreach_01","S_M_M_StrVend_01","S_M_M_Trucker_01","S_M_M_UPS_01","S_M_M_UPS_02","S_M_O_Busker_01","S_M_Y_AirWorker","S_M_Y_AmmuCity_01","S_M_Y_ArmyMech_01","S_M_Y_Autopsy_01","S_M_Y_Barman_01","S_M_Y_BayWatch_01",
	"S_M_Y_BlackOps_01","S_M_Y_BlackOps_02","S_M_Y_BlackOps_03","S_M_Y_BusBoy_01","S_M_Y_Chef_01","S_M_Y_Clown_01","S_M_Y_Construct_01","S_M_Y_Construct_02","S_M_Y_Cop_01","S_M_Y_Dealer_01","S_M_Y_DevinSec_01","S_M_Y_DockWork_01","S_M_Y_Doorman_01",
	"S_M_Y_DWService_01","S_M_Y_DWService_02","S_M_Y_Factory_01","S_M_Y_Fireman_01","S_M_Y_Garbage","S_M_Y_Grip_01","S_M_Y_HwayCop_01","S_M_Y_Marine_01","S_M_Y_Marine_02","S_M_Y_Marine_03","S_M_Y_Mime","S_M_Y_PestCont_01",
	"S_M_Y_Pilot_01","S_M_Y_PrisMuscl_01","S_M_Y_Prisoner_01","S_M_Y_Ranger_01","S_M_Y_Robber_01","S_M_Y_Sheriff_01","S_M_Y_Shop_MASK","S_M_Y_StrVend_01","S_M_Y_Swat_01","S_M_Y_USCG_01","S_M_Y_Valet_01","S_M_Y_Waiter_01",
	"S_M_Y_WinClean_01","S_M_Y_XMech_01","S_M_Y_XMech_02","U_F_M_Corpse_01","U_F_M_Miranda","U_F_M_ProMourn_01","U_F_O_MovieStar","U_F_O_ProlHost_01","U_F_Y_BikerChic","U_F_Y_COMJane","U_F_Y_corpse_01","U_F_Y_corpse_02",
	"U_F_Y_HotPosh_01","U_F_Y_JewelAss_01","U_F_Y_Mistress","U_F_Y_PoppyMich","U_F_Y_Princess","U_F_Y_SpyActress","U_M_M_Aldinapoli","U_M_M_BankMan","U_M_M_BikeHire_01","U_M_M_FIBArchitect","U_M_M_FilmDirector","U_M_M_GlenStank_01",
	"U_M_M_Griff_01","U_M_M_Jesus_01","U_M_M_JewelSec_01","U_M_M_JewelThief","U_M_M_MarkFost","U_M_M_PartyTarget","U_M_M_ProlSec_01","U_M_M_ProMourn_01","U_M_M_RivalPap","U_M_M_SpyActor","U_M_M_WillyFist","U_M_O_FinGuru_01",
	"U_M_O_TapHillBilly","U_M_O_Tramp_01","U_M_Y_Abner","U_M_Y_AntonB",	"U_M_Y_BabyD","U_M_Y_Baygor","U_M_Y_BurgerDrug_01","U_M_Y_Chip","U_M_Y_Cyclist_01","U_M_Y_FIBMugger_01","U_M_Y_Guido_01","U_M_Y_GunVend_01","U_M_Y_Hippie_01",
	"U_M_Y_ImpoRage","U_M_Y_Justin","U_M_Y_Mani","U_M_Y_MilitaryBum","U_M_Y_Paparazzi","U_M_Y_Party_01","U_M_Y_Pogo_01","U_M_Y_Prisoner_01","U_M_Y_ProlDriver_01","U_M_Y_RSRanger_01","U_M_Y_SBike","U_M_Y_StagGrm_01","U_M_Y_Tattoo_01",
	"U_M_Y_Zombie_01"};
		};
	}

	namespace weapon {
		inline bool enabled = false;
		inline bool no_recoil = false;
		inline bool no_reload = false;
		inline bool no_spread = false;
		inline bool infinite_range = false;
		inline bool force_gun = false;
		inline bool infite_ammo = false;
		inline bool set_ammo = false;
		inline bool damage_boost = false;

		inline int recoil_value = 0;
		inline int reload_value = 100;
		inline int spread_value = 0;
		inline int weapon_range = 1000;
		inline int ammo_to_set = 0;
		inline int int_damage = 999;

		namespace weapon_spawning {
			inline bool weapon_spawning = false;

			inline int weapon_current = 0;
			inline const char* weapon_list[]{ "Dagger", "Bat", "Knife", "Machete", "Pistol", "Pistol MK2", "Combat Pistol", "AP Pistol", "Stungun", "Pistol 50", "SNS PISTOL", "SNS Pistol MK2", "Heavy Pistol", "Vintage Pisol", "Flare Gun", "Marksman Pistol", "Revolver", "Revolver MK2", "Double Action", "Micro Smg", "Smg", "Smg MK2", "Assault Smg", "Combat PDW", "Machine Pistol", "Mini Smg", "Pump Shotgun", "Pump Shotgun MK2", "Sawnoff Shotgun", "Assault Shotgun", "Bullpup Shotgun", "Musket", "Heavy Shotgun", "DB Shotgun", "Auto Shotgun", "Assault Rifle", "Assault Rifle MK2", "Carbine Rifle", "Carbine Rifle MK2", "Advanced Rifle", "Special Carbine", "Special Carbine MK2", "Bullpup Rifle", "Bullpup Rifle MK2", "Compact Rifle", "Machine Gun", "Combat MG", "Combat MG MK2", "GUSENBERG", "Sniper Rifle", "AWP", "AWP MK2", "Marksman Rifle", "Marksman Rifle MK2", "RPG", "Grenade Launcher", "MiniGun", "FireWork", "RailGun", "Homing Launcher", "Compact Launcher", "Grenade", "BZGAS", "Smoke Grenade", "Flare", "Molotov", "Sticky BOMB", "Prox Mine", "SnowBall", "Pipe Bomb", "Ball", "Petrol Can", "Fire Extinguisher", "Parachute" };
			inline bool give = false;
			inline bool in_hand = false;
		}
	}

	namespace vehicle {
		inline bool enabled = false;

		inline bool godmod = false;
		inline bool auto_open_car = false;
		inline bool auto_start_engine = false;
		inline bool skip_animation = false;
		inline bool explode_car = false;
		inline bool spawnvehicule = false;
		inline bool networked = false;

		inline bool spawn_maxed = false;

		inline bool custom_speed = false;
		inline int speed_int = 0;

		inline bool on_car = false;
		inline bool update = false;
		inline char plate_text[8] = "...";

		inline int mod_idx = 0;
		inline int primary_color = 0;
		inline int secondary_color = 0;
		inline int add_idx = 0;

		inline bool update_colors = false;
		inline bool update_plate = false;

		inline bool repair = false;
		inline bool invisible_car = false;

		inline bool unlock = false;
		inline bool lock = false;

		inline bool warp_on_key = false;
		inline int key_warp = 0;

		namespace vehicle_spawning {

			int TypesInt = 0;
			int Selected = 0;
			inline bool SortByType = false;
			rage::joaat_t VehicleToSpawn;
			inline const char* types[]{ "Super", "Boats", "Commercial", "Compacts", "Coupes", "Cycles", "Emergency", "Helicopters", "Industrial", "Military", "Motorcycles", "Muscle", "OffRoad", "Planes", "Sedans", "Service", "AfterHours", "dcasino", "arenawar", "Doomsday", "Sports", "SportsClassics", "Super", "SUVs", "Trailer", "Trains", "Utility", "Vans", "IMPORTEXPORT"};


			inline int SuperSportsPos = 0;
			inline const char* SuperSports1[]{
				"MICHELLI",
				"JESTER3",
				"FLASHGT",
				"TEZERACT",
				"CHEBUREK",
				"TYRANT",
				"ELLIE",
				"FAGALOA",
				"GB200",
				"ISSI3",
				"TAIPAN",
				"DOMINATOR3",
				"CARACARA",

			};

			inline int BoatsPos = 0;
			inline const char* Boats1 []{
								"SEASHARK2",
               "DINGHY", "DINGHY2", "DINGHY3", "DINGHY4", "JETMAX",
				"MARQUIS", "PREDATOR", "SEASHARK", "SEASHARK2", "SEASHARK3",
				"SPEEDER", "SPEEDER2", "SQUALO", "SUBMERSIBLE", "SUBMERSIBLE2",
				"SUNTRAP", "TORO", "TORO2", "TROPIC", "TROPIC2",
				"TUG"
			};

			inline int ComercialPos = 0;
			inline const char*  Commercial1  []{
				"BENSON", "BIFF", "HAULER", "MULE", "MULE2",
				"MULE3", "PACKER", "PHANTOM", "POUNDER", "STOCKADE",
				"STOCKADE3"
			};

			inline int CompactsPos = 0;
			inline const char* Compacts1  []{
				"BLISTA", "BRIOSO", "DILETTANTE", "DILETTANTE2", "ISSI2",
				"PANTO", "PRAIRIE", "RHAPSODY"
			};

			inline int CoupesPos = 2;
			inline const char* Coupes1  []{
				"COGCABRIO", "EXEMPLAR", "F620", "FELON", "FELON2",
				"JACKAL", "ORACLE", "ORACLE2", "SENTINEL", "SENTINEL2",
				"WINDSOR", "WINDSOR2", "ZION", "ZION2"
			};

			inline int CyclesPos = 0;
			inline const char* Cycles1  []{
				"BMX", "CRUISER", "FIXTER", "SCORCHER", "TRIBIKE",
				"TRIBIKE2", "TRIBIKE3"
			};

			inline int EmergencyPos = 2;
			inline const char* Emergency1  []{
				"AMBULANCE", "FBI", "FBI2", "FIRETRUK", "LGUARD",
				"PBUS", "PRANGER", "POLICE", "POLICE2", "POLICE3",
				"POLICE4", "POLICEB", "POLICEOLD1", "POLICEOLD2", "POLICET",
				"SHERIFF", "SHERIFF2", "RIOT"
			};

			inline int HelicoptersPos = 4;
			inline const char* Helicopters1  []{
				"ANNIHILATOR", "BLIMP", "BLIMP2", "BUZZARD", "BUZZARD2",
				"CARGOBOB", "CARGOBOB2", "CARGOBOB3", "CARGOBOB4", "FROGGER",
				"FROGGER2", "MAVERICK", "POLMAV", "SAVAGE", "SKYLIFT",
				"SUPERVOLITO", "SUPERVOLITO2", "SWIFT", "SWIFT2", "VALKYRIE",
				"VALKYRIE2", "VOLATUS" , 				"SEASPARROW",
			};

			inline int IndustrialPos = 0;
			inline const char* Industrial1  []{
				"BULLDOZER", "CUTTER", "DUMP", "FLATBED", "GUARDIAN",
				"HANDLER", "MIXER", "MIXER2", "RUBBLE", "TIPTRUCK",
				"TIPTRUCK2"
			};

			inline int MilitaryPos = 0;
			inline const char* Military1  []{
				"BARRACKS", "BARRACKS2", "BARRACKS3", "CRUSADER", "RHINO"
			};

			inline int MotorcyclesPos = 0;
			inline const char* Motorcycles1  []{
				"OPPRESSOR", "AKUMA", "AVARUS", "BAGGER", "BATI", "BATI2",
				"BF400", "CARBONRS", "CHIMERA", "CLIFFHANGER", "DAEMON",
				"DAEMON2", "DEFILER", "DOUBLE", "ENDURO", "ESSKEY",
				"FAGGIO", "FAGGIO2", "FAGGIO3", "GARGOYLE", "HAKUCHOU",
				"HAKUCHOU2", "HEXER", "INNOVATION", "LECTRO", "MANCHEZ",
				"NEMESIS", "NIGHTBLADE", "PCJ", "RATBIKE", "RUFFIAN",
				"SANCHEZ", "SANCHEZ2", "SANCTUS", "SHOTARO", "SOVEREIGN",
				"THRUST", "VADER", "VINDICATOR", "VORTEX", "WOLFSBANE",
				"ZOMBIEA", "ZOMBIEB", "DIABLOUS", "DIABLOUS2", "FCR",
				"FCR2"
			};

			inline int MusclePos = 0;
			inline const char* Muscle1  []{
				"BLADE", "BUCCANEER", "BUCCANEER2", "CHINO", "CHINO2",
				"COQUETTE3", "DOMINATOR", "DOMINATOR2", "DUKES", "DUKES2",
				"GAUNTLET", "GAUNTLET2", "FACTION", "FACTION2", "FACTION3",
				"HOTKNIFE", "LURCHER", "MOONBEAM", "MOONBEAM2", "NIGHTSHADE",
				"PHOENIX", "PICADOR", "RATLOADER", "RATLOADER2", "RUINER", "RUINER2", "RUINER3",
				"SABREGT", "SABREGT2", "SLAMVAN", "SLAMVAN2", "SLAMVAN3",
				"STALION", "STALION2", "TAMPA", "VIGERO", "VIRGO",
				"VIRGO2", "VIRGO3", "VOODOO", "VOODOO2"
			};

			inline int OffRoadPos = 3;
			inline const char* OffRoad1  []{
				"BFINJECTION", "BIFTA", "BLAZER", "BLAZER2", "BLAZER3",
				"BLAZER4", "BODHI2", "BRAWLER", "DLOADER", "DUBSTA3",
				"DUNE", "DUNE2", "INSURGENT", "INSURGENT2", "KALAHARI",
				"MARSHALL", "MESA3", "MONSTER", "RANCHERXL", "RANCHERXL2",
				"REBEL", "REBEL2", "SANDKING", "SANDKING2", "TECHNICAL",
				"TROPHYTRUCK", "TROPHYTRUCK2", "TECHNICAL2", "DUNE4", "DUNE5",
				"BLAZER5"
			};

			inline int PlanesPos = 0;
			inline const char* Planes1  []{
				"BESRA", "CARGOPLANE", "CUBAN800", "DODO", "DUSTER",
				"HYDRA", "JET", "LAZER", "LUXOR", "LUXOR2",
				"MAMMATUS", "MILJET", "NIMBUS", "SHAMAL", "STUNT",
				"TITAN", "VELUM", "VELUM2", "VESTRA"
			};

			inline int SedansPos = 0;
			inline const char* Sedans1  []{
				"ASEA", "ASEA2", "ASTEROPE", "COG55", "COG552",
				"COGNOSCENTI", "COGNOSCENTI2", "EMPEROR", "EMPEROR2", "EMPEROR3",
				"FUGITIVE", "GLENDALE", "INGOT", "INTRUDER", "LIMO2",
				"PREMIER", "PRIMO", "PRIMO2", "REGINA", "ROMERO",
				"SCHAFTER2", "SCHAFTER5", "SCHAFTER6", "STANIER", "STRATUM",
				"STRETCH", "SUPERD", "SURGE", "TAILGATER", "WARRENER",
				"WASHINGTON"
			};

			inline int ServicePos = 0;
			inline const char* Service1  []{
				"AIRBUS", "BRICKADE", "BUS", "COACH", "RALLYTRUCK",
				"RENTALBUS", "TAXI", "TOURBUS", "TRASH", "TRASH2",
				"WASTELANDER",
			};

			inline int AfterHours = 0;
			inline const char* AfterHours1  []{
				"BLIMP3","FREECRAWLER","MENACER","MULE4","OPPRESSOR2","PATRIOT2","PBUS2",
				"POUNDER2","SCRAMJET","SPEEDO4","STAFFORD","STRIKEFORCE","SWINGER","TERBYTE",
			};
			inline int dcasino = 0;
			inline const char* dcasino1  []{
			"CARACARA2","DRAFTER","DYNASTY","EMERUS","GAUNTLET3","GAUNTLET4","HELLION","ISSI7","JUGULAR",
			"KRIEGER","LOCUST","NEBULA","NEO","NOVAK","PARAGON","PARAGON2","PEYOTE2","RROCKET",
			"S80","THRAX","ZION3","ZORRUSSO",
			};
			inline int arenawar = 0;
			inline const char* arenawar1  []{
			"BRUISER", "BRUISER2", "BRUISER3", "BRUTUS", "BRUTUS2", "BRUTUS3", "CERBERUS",
			"CERBERUS2", "CERBERUS3", "CLIQUE", "DEATHBIKE", "DEATHBIKE2", "DEATHBIKE3","DEVESTE",
			"DEVIANT", "DOMINATOR4", "DOMINATOR5", "DOMINATOR6", "IMPALER", "IMPALER2", "IMPALER3", "IMPALER4",
			"IMPERATOR", "IMPERATOR2", "IMPERATOR3", "ISSI4", "ISSI5", "ISSI6", "ITALIGTO", "MONSTER3",
			"MONSTER4", "MONSTER5", "RCBANDITO", "SCARAB2", "SCARAB3", "SCHLAGEN", "SLAMVAN4", "SLAMVAN5", "SLAMVAN6", "TOROS", "TULIP", "VAMOS",
			"ZR380", "ZR3802", "ZR3803"
			};

			inline int DoomsdayPos = 0;
			inline const char* Doomsday1  []{
				"AUTARCH", "AVENGER", "BARRAGE", "CHERNOBOG", "COMET4", "COMET5",
				"DELUXO", "GT500", "HERMES", "HUSTLER", "KAMACHO","KHANJALI",
				"NEON", "PARIAH", "RAIDEN", "REVOLTER", "RIATA", "RIOT2", "SAVESTRA",
				"SC1", "SENTINEL3", "STREITER", "STROMBERG", "THRUSTER", "VISERIS",
				"VOLATOL", "YOSEMITE", "Z190"
			};

			inline int SportsPos = 0;
			inline const char* Sports1  []{
				"ALPHA", "BANSHEE", "BESTIAGTS", "BLISTA2", "BLISTA3",
				"BUFFALO", "BUFFALO2", "BUFFALO3", "CARBONIZZARE", "COMET2",
				"COQUETTE", "ELEGY", "ELEGY2", "FELTZER2", "FUROREGT", "FUSILADE",
				"FUTO", "JESTER", "JESTER2", "KHAMELION", "KURUMA",
				"KURUMA2", "LYNX", "MASSACRO", "MASSACRO2", "NINEF",
				"NINEF2", "OMNIS", "PENUMBRA", "RAPIDGT", "RAPIDGT2",
				"RAPTOR", "SCHAFTER3", "SCHAFTER4", "SCHWARTZER", "SEVEN70",
				"SULTAN", "SURANO", "SPECTER", "SPECTER2", "TAMPA2", "TROPOS", "VERLIERER2",
				"RUINER2", "PHANTOM2", "RUSTON"
				"HOTRING",

			};

			inline int SportsClassicPos = 0;
			inline const char* SportsClassics1  []{
				"BTYPE", "BTYPE2", "BTYPE3", "CASCO", "COQUETTE2",
				"FELTZER3", "JB700", "MAMBA", "MANANA", "MONROE",
				"PEYOTE", "PIGALLE", "STINGER", "STINGERGT", "TORNADO",
				"TORNADO2", "TORNADO3", "TORNADO4", "TORNADO5", "TORNADO6",
				"ZTYPE", "INFERNUS2", "TURISMO2",
			};
			
			inline int SuperPos = 0;
			inline const char* Super1  []{
				"ADDER", "BANSHEE2", "BULLET", "CHEETAH", "ENTITYXF",
				"FMJ", "SHEAVA", "INFERNUS", "NERO", "NERO2","OSIRIS", "LE7B",
				"ITALIGTB", "ITALIGTB2", "PFISTER811", "PROTOTIPO", "REAPER", "SULTANRS", "T20",
				"TEMPESTA", "TURISMOR", "TYRUS", "VACCA", "VOLTIC", "ZENTORNO", "VOLTIC2", "PENETRATOR", "GP1"
			};

			inline 	int SUVPos = 0;
			inline const char* SUVs1  []{
				"BALLER", "BALLER2", "BALLER3", "BALLER4", "BALLER5",
				"BALLER6", "BJXL", "CAVALCADE", "CAVALCADE2", "CONTENDER",
				"DUBSTA", "DUBSTA2", "FQ2", "GRANGER", "GRESLEY",
				"HABANERO", "HUNTLEY", "LANDSTALKER", "MESA", "MESA2",
				"PATRIOT", "RADI", "ROCOTO", "SEMINOLE", "SERRANO",
				"XLS", "XLS2"
			};

			inline int TrailerPos = 0;
			inline const char* Trailer1  []{
				"ARMYTANKER", "ARMYTRAILER", "ARMYTRAILER2", "BALETRAILER", "BOATTRAILER",
				"DOCKTRAILER", "FREIGHTTRAILER", "GRAINTRAILER", "PROPTRAILER", "RAKETRAILER",
				"TANKER", "TANKER2", "TR2", "TR3", "TR4",
				"TRAILERLOGS", "TRAILERS", "TRAILERS2", "TRAILERS3", "TRAILERSMALL",
				"TRFLAT", "TVTRAILER"
			};

			inline int TrainsPos = 0;
			inline const char* Trains1  []{
				"CABLECAR", "FREIGHT", "FREIGHTCAR", "FREIGHTCONT1", "FREIGHTCONT2",
				"FREIGHTGRAIN", "METROTRAIN", "TANKERCAR"
			};

			inline int UtilityPos = 0;
			inline const char* Utility1  []{
				"AIRTUG", "CADDY", "CADDY2", "DOCKTUG", "FORKLIFT",
				"MOWER", "RIPLEY", "SADLER", "SADLER2", "SCRAP",
				"TOWTRUCK", "TOWTRUCK2", "TRACTOR", "TRACTOR2", "TRACTOR3",
				"UTILLITRUCK", "UTILLITRUCK2", "UTILLITRUCK3"
			};

			inline int VansPos = 0;
			inline const char* Vans1  []{
				"BISON", "BISON2", "BISON3", "BOBCATXL", "BOXVILLE",
				"BOXVILLE2", "BOXVILLE3", "BOXVILLE4", "BURRITO", "BURRITO2",
				"BURRITO3", "BURRITO4", "BURRITO5", "CAMPER", "GBURRITO",
				"GBURRITO2", "JOURNEY", "MINIVAN", "MINIVAN2", "PARADISE",
				"PONY", "PONY2", "RUMPO", "RUMPO2", "RUMPO3",
				"SPEEDO", "SPEEDO2", "SURFER", "SURFER2", "TACO",
				"YOUGA", "YOUGA2"
			};

			inline int IMPORTEXPORT = 0;
			inline const char* IMPORTEXPORT1  []{
				"BLAZER5", "BOXVILLE5", "COMET3", "DIABLOUS", "DIABLOUS2", "DUNE4", "DUNE5",
				"ELEGY", "FCR", "FCR2", "ITALIGTB", "ITALIGTB2", "NERO", "NERO2", "PENETRATOR",
				"PHANTOM2", "RUINER2", "SPECTER", "SPECTER2", "TECHNICAL2", "TEMPESTA", "VOLTIC2",
				"WASTELANDER"
			};
			const char* allVehicleNames[] = {
			"MICHELLI",
				"JESTER3",
				"FLASHGT",
				"TEZERACT",
				"SEASHARK2",
				"CHEBUREK",
				"TYRANT",
				"HOTRING",
				"ELLIE",
				"FAGALOA",
				"GB200",
				"ISSI3",
				"TAIPAN",
				"DOMINATOR3",
				"CARACARA",
				"SEASPARROW",		"DINGHY", "DINGHY2", "DINGHY3", "DINGHY4", "JETMAX",
				"MARQUIS", "PREDATOR", "SEASHARK", "SEASHARK2", "SEASHARK3",
				"SPEEDER", "SPEEDER2", "SQUALO", "SUBMERSIBLE", "SUBMERSIBLE2",
				"SUNTRAP", "TORO", "TORO2", "TROPIC", "TROPIC2",
				"TUG"	,			"BENSON", "BIFF", "HAULER", "MULE", "MULE2",
				"MULE3", "PACKER", "PHANTOM", "POUNDER", "STOCKADE",
				"STOCKADE3",	"BLISTA", "BRIOSO", "DILETTANTE", "DILETTANTE2", "ISSI2",
				"PANTO", "PRAIRIE", "RHAPSODY",		"COGCABRIO", "EXEMPLAR", "F620", "FELON", "FELON2",
				"JACKAL", "ORACLE", "ORACLE2", "SENTINEL", "SENTINEL2",
				"WINDSOR", "WINDSOR2", "ZION", "ZION2",		"BMX", "CRUISER", "FIXTER", "SCORCHER", "TRIBIKE",
				"TRIBIKE2", "TRIBIKE3",			"AMBULANCE", "FBI", "FBI2", "FIRETRUK", "LGUARD",
				"PBUS", "PRANGER", "POLICE", "POLICE2", "POLICE3",
				"POLICE4", "POLICEB", "POLICEOLD1", "POLICEOLD2", "POLICET",
				"SHERIFF", "SHERIFF2", "RIOT",			"ANNIHILATOR", "BLIMP", "BLIMP2", "BUZZARD", "BUZZARD2",
				"CARGOBOB", "CARGOBOB2", "CARGOBOB3", "CARGOBOB4", "FROGGER",
				"FROGGER2", "MAVERICK", "POLMAV", "SAVAGE", "SKYLIFT",
				"SUPERVOLITO", "SUPERVOLITO2", "SWIFT", "SWIFT2", "VALKYRIE",
				"VALKYRIE2", "VOLATUS",		"BULLDOZER", "CUTTER", "DUMP", "FLATBED", "GUARDIAN",
				"HANDLER", "MIXER", "MIXER2", "RUBBLE", "TIPTRUCK",
				"TIPTRUCK2",				"BARRACKS", "BARRACKS2", "BARRACKS3", "CRUSADER", "RHINO"
,				"OPPRESSOR", "AKUMA", "AVARUS", "BAGGER", "BATI", "BATI2",
				"BF400", "CARBONRS", "CHIMERA", "CLIFFHANGER", "DAEMON",
				"DAEMON2", "DEFILER", "DOUBLE", "ENDURO", "ESSKEY",
				"FAGGIO", "FAGGIO2", "FAGGIO3", "GARGOYLE", "HAKUCHOU",
				"HAKUCHOU2", "HEXER", "INNOVATION", "LECTRO", "MANCHEZ",
				"NEMESIS", "NIGHTBLADE", "PCJ", "RATBIKE", "RUFFIAN",
				"SANCHEZ", "SANCHEZ2", "SANCTUS", "SHOTARO", "SOVEREIGN",
				"THRUST", "VADER", "VINDICATOR", "VORTEX", "WOLFSBANE",
				"ZOMBIEA", "ZOMBIEB", "DIABLOUS", "DIABLOUS2", "FCR",
				"FCR2","BLADE", "BUCCANEER", "BUCCANEER2", "CHINO", "CHINO2",
				"COQUETTE3", "DOMINATOR", "DOMINATOR2", "DUKES", "DUKES2",
				"GAUNTLET", "GAUNTLET2", "FACTION", "FACTION2", "FACTION3",
				"HOTKNIFE", "LURCHER", "MOONBEAM", "MOONBEAM2", "NIGHTSHADE",
				"PHOENIX", "PICADOR", "RATLOADER", "RATLOADER2", "RUINER", "RUINER2", "RUINER3",
				"SABREGT", "SABREGT2", "SLAMVAN", "SLAMVAN2", "SLAMVAN3",
				"STALION", "STALION2", "TAMPA", "VIGERO", "VIRGO",
				"VIRGO2", "VIRGO3", "VOODOO", "VOODOO2",				"BFINJECTION", "BIFTA", "BLAZER", "BLAZER2", "BLAZER3",
				"BLAZER4", "BODHI2", "BRAWLER", "DLOADER", "DUBSTA3",
				"DUNE", "DUNE2", "INSURGENT", "INSURGENT2", "KALAHARI",
				"MARSHALL", "MESA3", "MONSTER", "RANCHERXL", "RANCHERXL2",
				"REBEL", "REBEL2", "SANDKING", "SANDKING2", "TECHNICAL",
				"TROPHYTRUCK", "TROPHYTRUCK2", "TECHNICAL2", "DUNE4", "DUNE5",
				"BLAZER5",	"BESRA", "CARGOPLANE", "CUBAN800", "DODO", "DUSTER",
				"HYDRA", "JET", "LAZER", "LUXOR", "LUXOR2",
				"MAMMATUS", "MILJET", "NIMBUS", "SHAMAL", "STUNT",
				"TITAN", "VELUM", "VELUM2", "VESTRA",	"ASEA", "ASEA2", "ASTEROPE", "COG55", "COG552",
				"COGNOSCENTI", "COGNOSCENTI2", "EMPEROR", "EMPEROR2", "EMPEROR3",
				"FUGITIVE", "GLENDALE", "INGOT", "INTRUDER", "LIMO2",
				"PREMIER", "PRIMO", "PRIMO2", "REGINA", "ROMERO",
				"SCHAFTER2", "SCHAFTER5", "SCHAFTER6", "STANIER", "STRATUM",
				"STRETCH", "SUPERD", "SURGE", "TAILGATER", "WARRENER",
				"WASHINGTON",			"AIRBUS", "BRICKADE", "BUS", "COACH", "RALLYTRUCK",
				"RENTALBUS", "TAXI", "TOURBUS", "TRASH", "TRASH2",
				"WASTELANDER",				"BLIMP3","FREECRAWLER","MENACER","MULE4","OPPRESSOR2","PATRIOT2","PBUS2",
				"POUNDER2","SCRAMJET","SPEEDO4","STAFFORD","STRIKEFORCE","SWINGER","TERBYTE",	"CARACARA2","DRAFTER","DYNASTY","EMERUS","GAUNTLET3","GAUNTLET4","HELLION","ISSI7","JUGULAR",
			"KRIEGER","LOCUST","NEBULA","NEO","NOVAK","PARAGON","PARAGON2","PEYOTE2","RROCKET",
			"S80","THRAX","ZION3","ZORRUSSO",			"BRUISER", "BRUISER2", "BRUISER3", "BRUTUS", "BRUTUS2", "BRUTUS3", "CERBERUS",
			"CERBERUS2", "CERBERUS3", "CLIQUE", "DEATHBIKE", "DEATHBIKE2", "DEATHBIKE3","DEVESTE",
			"DEVIANT", "DOMINATOR4", "DOMINATOR5", "DOMINATOR6", "IMPALER", "IMPALER2", "IMPALER3", "IMPALER4",
			"IMPERATOR", "IMPERATOR2", "IMPERATOR3", "ISSI4", "ISSI5", "ISSI6", "ITALIGTO", "MONSTER3",
			"MONSTER4", "MONSTER5", "RCBANDITO", "SCARAB2", "SCARAB3", "SCHLAGEN", "SLAMVAN4", "SLAMVAN5", "SLAMVAN6", "TOROS", "TULIP", "VAMOS",
			"ZR380", "ZR3802", "ZR3803",		"AUTARCH", "AVENGER", "BARRAGE", "CHERNOBOG", "COMET4", "COMET5",
				"DELUXO", "GT500", "HERMES", "HUSTLER", "KAMACHO","KHANJALI",
				"NEON", "PARIAH", "RAIDEN", "REVOLTER", "RIATA", "RIOT2", "SAVESTRA",
				"SC1", "SENTINEL3", "STREITER", "STROMBERG", "THRUSTER", "VISERIS",
				"VOLATOL", "YOSEMITE", "Z190",			"ALPHA", "BANSHEE", "BESTIAGTS", "BLISTA2", "BLISTA3",
				"BUFFALO", "BUFFALO2", "BUFFALO3", "CARBONIZZARE", "COMET2",
				"COQUETTE", "ELEGY", "ELEGY2", "FELTZER2", "FUROREGT", "FUSILADE",
				"FUTO", "JESTER", "JESTER2", "KHAMELION", "KURUMA",
				"KURUMA2", "LYNX", "MASSACRO", "MASSACRO2", "NINEF",
				"NINEF2", "OMNIS", "PENUMBRA", "RAPIDGT", "RAPIDGT2",
				"RAPTOR", "SCHAFTER3", "SCHAFTER4", "SCHWARTZER", "SEVEN70",
				"SULTAN", "SURANO", "SPECTER", "SPECTER2", "TAMPA2", "TROPOS", "VERLIERER2",
				"RUINER2", "PHANTOM2", "RUSTON",				"BTYPE", "BTYPE2", "BTYPE3", "CASCO", "COQUETTE2",
				"FELTZER3", "JB700", "MAMBA", "MANANA", "MONROE",
				"PEYOTE", "PIGALLE", "STINGER", "STINGERGT", "TORNADO",
				"TORNADO2", "TORNADO3", "TORNADO4", "TORNADO5", "TORNADO6",
				"ZTYPE", "INFERNUS2", "TURISMO2",			"ADDER", "BANSHEE2", "BULLET", "CHEETAH", "ENTITYXF",
				"FMJ", "SHEAVA", "INFERNUS", "NERO", "NERO2","OSIRIS", "LE7B",
				"ITALIGTB", "ITALIGTB2", "PFISTER811", "PROTOTIPO", "REAPER", "SULTANRS", "T20",
				"TEMPESTA", "TURISMOR", "TYRUS", "VACCA", "VOLTIC", "ZENTORNO", "VOLTIC2", "PENETRATOR", "GP1",		"BALLER", "BALLER2", "BALLER3", "BALLER4", "BALLER5",
				"BALLER6", "BJXL", "CAVALCADE", "CAVALCADE2", "CONTENDER",
				"DUBSTA", "DUBSTA2", "FQ2", "GRANGER", "GRESLEY",
				"HABANERO", "HUNTLEY", "LANDSTALKER", "MESA", "MESA2",
				"PATRIOT", "RADI", "ROCOTO", "SEMINOLE", "SERRANO",
				"XLS", "XLS2",			"ARMYTANKER", "ARMYTRAILER", "ARMYTRAILER2", "BALETRAILER", "BOATTRAILER",
				"DOCKTRAILER", "FREIGHTTRAILER", "GRAINTRAILER", "PROPTRAILER", "RAKETRAILER",
				"TANKER", "TANKER2", "TR2", "TR3", "TR4",
				"TRAILERLOGS", "TRAILERS", "TRAILERS2", "TRAILERS3", "TRAILERSMALL",
				"TRFLAT", "TVTRAILER",			"CABLECAR", "FREIGHT", "FREIGHTCAR", "FREIGHTCONT1", "FREIGHTCONT2",
				"FREIGHTGRAIN", "METROTRAIN", "TANKERCAR",				"AIRTUG", "CADDY", "CADDY2", "DOCKTUG", "FORKLIFT",
				"MOWER", "RIPLEY", "SADLER", "SADLER2", "SCRAP",
				"TOWTRUCK", "TOWTRUCK2", "TRACTOR", "TRACTOR2", "TRACTOR3",
				"UTILLITRUCK", "UTILLITRUCK2", "UTILLITRUCK3",				"BISON", "BISON2", "BISON3", "BOBCATXL", "BOXVILLE",
				"BOXVILLE2", "BOXVILLE3", "BOXVILLE4", "BURRITO", "BURRITO2",
				"BURRITO3", "BURRITO4", "BURRITO5", "CAMPER", "GBURRITO",
				"GBURRITO2", "JOURNEY", "MINIVAN", "MINIVAN2", "PARADISE",
				"PONY", "PONY2", "RUMPO", "RUMPO2", "RUMPO3",
				"SPEEDO", "SPEEDO2", "SURFER", "SURFER2", "TACO",
				"YOUGA", "YOUGA2",			"BLAZER5", "BOXVILLE5", "COMET3", "DIABLOUS", "DIABLOUS2", "DUNE4", "DUNE5",
				"ELEGY", "FCR", "FCR2", "ITALIGTB", "ITALIGTB2", "NERO", "NERO2", "PENETRATOR",
				"PHANTOM2", "RUINER2", "SPECTER", "SPECTER2", "TECHNICAL2", "TEMPESTA", "VOLTIC2",
				"WASTELANDER"
			};
		}
	}

	namespace peds {
		inline int selected_index = 1;

		inline int selected_index_vehicle = 1;

		inline bool overide_veh = false;
		inline bool overide_ped = false;
	}

	namespace misc {
		inline bool watermark = true;
		inline int hotkey = VK_F3;
		inline bool lock_menu_layout = false;

		inline int menu_size_x = 550 * 1.2;
		inline int menu_size_y = 430 * 1.2;
	}

	namespace tempcolor
	{
		inline float menu_color[4] = { 140.f, 131.f, 214.f, 255.f };

		inline float box[4] = { 255.f, 255.f, 255.f, 255.f };
		inline float skeleton[4] = { 255.f, 255.f, 255.f, 255.f };

		inline float box_color[4] = { 255.f, 255.f, 255.f, 255.f };
		inline float filled_color[4] = { 0.f, 0.f, 0.f, 30.f };
		inline float distance_color[4] = { 255.f, 255.f, 255.f, 255.f };
		inline float health_color[4] = { 255.f, 255.f, 255.f, 255.f };
		inline float player_name_color[4] = { 255.f, 255.f, 255.f, 255.f };
		inline float weapon_name_color[4] = { 255.f, 255.f, 255.f, 255.f };
		inline float skeleton_color[4] = { 255.f, 255.f, 255.f, 255.f };
		inline float snapline_color[4] = { 255.f, 255.f, 255.f, 255.f };

		inline float crosshair[4] = { 255.f, 255.f, 255.f, 255.f };
		inline float preview_target[4] = { 255.f, 255.f, 255.f, 255.f };

		inline float box_color_visible[4] = { 255.f, 255.f, 255.f, 255.f };
		inline float filled_color_visible[4] = { 0.f, 0.f, 0.f, 0.1f };
		inline float distance_color_visible[4] = { 255.f, 255.f, 255.f, 255.f };
		inline float health_color_visible[4] = { 255.f, 255.f, 255.f, 255.f };
		inline float player_name_color_visible[4] = { 255.f, 255.f, 255.f, 255.f };
		inline float weapon_name_color_visible[4] = { 255.f, 255.f, 255.f, 255.f };
		inline float skeleton_color_visible[4] = { 255.f, 255.f, 255.f, 255.f };
		inline float snapline_color_visible[4] = { 255.f, 255.f, 255.f, 255.f };

		inline float invisible_color[4] = { 255.f, 255.f, 255.f, 255.f };

		inline float fov_color[4] = { 255.f, 255.f, 255.f, 255.f };
		inline float magic_color[4] = { 255.f, 255.f, 255.f, 255.f };

		inline float visible[4] = { 255.f, 255.f, 255.f, 255.f };
		inline float invisible[4] = { 255.f, 255.f, 255.f, 255.f };

		inline float friends_colors[4] = { 255.f, 255.f, 255.f, 255.f };

		inline float lines_colors[4] = { 255.f, 255.f, 255.f, 255.f };
	}
}