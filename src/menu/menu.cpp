#pragma once

#define  IMGUI_DEFINE_MATH_OPERATORS
#include <iostream>

#include "menu.hpp"

#include "../../dependencies/imgui/imgui.h"
#include "../entry/auth.hpp"


#include "../fivem/features/visuals.hpp"
#include "../fivem/features/locations.hpp"
#include "../fivem/features/lists.hpp"
#include "../fivem/features/configs.hpp"

#include "../hooks/hooks.hpp"
#include "bytes.hpp"
#include "custom.hpp"
#include <scripthook.hpp>


using namespace KeyAuth;

std::string name = "Easy";
std::string ownerid = "HuufgZR7th";
std::string secret = "dc724a85b4faa16d1df9b141fd1e5e85c6697159678ab023f9802b4c71ab8e56";
std::string version = "1.0";
std::string url = "https://keyauth.win/api/1.2/";
api KeyAuthApp(name, ownerid, secret, version, url);
char username[25] = "";
char password[25] = "";
char keyy[50] = "";


bool f1_key = false;

bool register_mode = false;
static bool show_menu;



#include <src/fivem/features/noclip.hpp>
#include <radar.hpp>
#include <ImGuiNotify.hpp>

template <typename T>
bool isType(const std::variant<bool, int, float>& var) {
	return std::holds_alternative<T>(var);
}

// Définir une structure pour stocker les éléments
struct FeatureBool {
	std::string texte;
	bool* a;
	int min;
	int max;
};

std::vector<struct FeatureBool> BoolFeatures;

struct FeatureInt {
	std::string texte;
	int* a;
	int min;
	int max;
};

std::vector<struct FeatureInt> IntFeatures;

struct FeatureFloat {
	std::string texte;
	float* a;
	int min;
	int max;
};

std::vector<struct FeatureFloat> FloatFeatures;

char playerName[128] = "Nom du joueur";
ImVec2 playerPos = ImVec2(150, 100); // Position initiale du texte

float health = 100.0f; // Santé initiale
ImVec2 healthBarSize = ImVec2(5, 300); // Taille de la barre de santé
bool isDraggingHealthBar = false; // Indicateur pour glisser la barre de santé
bool isDraggingText = false;

ImVec2 healthBarPosition = ImVec2(230, 115); // Position initiale de la barre de santé
float healthBarSmoothness = 5.0f; // Facteur de lissage (ajustez selon vos préférences)
ImVec2 targetSize = healthBarSize; // Target size of the health bar
float sizeChangeSpeed = 0.5f; // Speed of the size change effect


#define ALPHA    ( ImGuiColorEditFlags_AlphaPreview | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_Float | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_NoBorder )
#define NO_ALPHA ( ImGuiColorEditFlags_NoTooltip    | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_Float | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_NoBorder )
using namespace ImGui;
using ComVec4 = const ImVec4&;
auto Spinner(ImVec2 poss,float radius, float thickness, int num_segments, ComVec4 color) {
	auto window = GetCurrentWindow();
	if (window->SkipItems)
		return;

	auto& g = *GImGui;
	const auto& style = g.Style;
	auto&& pos = poss;
	ImVec2 size{ radius * 2, radius * 2 };
	const ImRect bb{ pos, pos + size };
	ItemSize(bb);
	if (!ItemAdd(bb, 0))
		return;

	window->DrawList->PathClear();
	int start = static_cast<int>(abs(ImSin(static_cast<float>(g.Time * 1.8f)) * (num_segments - 5)));
	const float a_min = IM_PI * 2.0f * ((float)start) / (float)num_segments;
	const float a_max = IM_PI * 2.0f * ((float)num_segments - 3) / (float)num_segments;
	const auto&& centre = ImVec2(pos.x + radius, pos.y + radius);
	for (auto i = 0; i < num_segments; i++) {
		const float a = a_min + ((float)i / (float)num_segments) * (a_max - a_min);
		auto time = static_cast<float>(g.Time);
		window->DrawList->PathLineTo({ centre.x + ImCos(a + time * 8) * radius,
									  centre.y + ImSin(a + time * 8) * radius });
	}
	window->DrawList->PathStroke(GetColorU32(color), false, thickness);
}
bool search_button(const char* label, bool* value , int* valuee ,float *valueee,float rounding, float padding, int min = 0, int max = 0, int type = 0) {

	ImGuiWindow* window = GetCurrentWindow();
	ImGuiID id = window->GetID(label);
	auto draw = window->DrawList;
	ImVec2 pos = window->DC.CursorPos;

	ImVec2 label_size = CalcTextSize(label, 0, 1);

	if (type == 0) {

		ImRect rect(ImVec2(pos.x, pos.y), ImVec2(pos.x + 550, pos.y + 50));
		ItemAdd(rect, id);
		ItemSize(rect, GetStyle().FramePadding.y);

		bool hovered, held;
		bool pressed = ButtonBehavior(rect, id, &hovered, &held, NULL);
		float alpha = 0;

		if (pressed) {
			if(*value)
				*value = false;
			else
				*value = true;


			MarkItemEdited(id);
		}



		alpha = ImLerp(alpha, (*value) ? 1.f : 0.f, 0.1f);

		draw->AddRectFilled(rect.Min, rect.Max, ImColor(34.f / 255.f, 34.f / 255.f, 36.f / 255.f, 0.7f * alpha ), 5, 0);
		draw->AddRectFilled(ImVec2(pos.x, pos.y), ImVec2(pos.x + 5, pos.y + 50 + padding), ImColor(10, 104, 255), 5, ImDrawCornerFlags_Left);
		draw->AddText(ImVec2(pos.x + 20, pos.y + 25 - label_size.y / 2 + padding), GetColorU32(ImGuiCol_Text), label);

		return true;

	}

	if (type == 1) {
		ImRect rect(ImVec2(pos.x, pos.y), ImVec2(pos.x + 250, pos.y + 50));
		ItemAdd(rect, id);
		ItemSize(rect, GetStyle().FramePadding.y);



		draw->AddRectFilled(ImVec2(pos.x, pos.y), ImVec2(pos.x + 550, pos.y + 50), ImColor(34, 34, 36, 50), 5, 0);
		draw->AddRectFilled(ImVec2(pos.x, pos.y), ImVec2(pos.x + 5, pos.y + 50 + padding), ImColor(10, 104, 255), 5, ImDrawCornerFlags_Left);
		draw->AddText(ImVec2(pos.x + 20, pos.y + 25 - label_size.y / 2 + padding), GetColorU32(ImGuiCol_Text), label);
		ImGui::SameLine();
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8);


		ImGui::SliderInt(E("Value"), valuee, min, max);


		return true;
	}

	if (type == 2) {
		ImRect rect(ImVec2(pos.x, pos.y), ImVec2(pos.x + 250, pos.y + 50));
		ItemAdd(rect, id);
		ItemSize(rect, GetStyle().FramePadding.y);



		draw->AddRectFilled(ImVec2(pos.x, pos.y), ImVec2(pos.x + 550, pos.y + 50), ImColor(34, 34, 36, 50), 5, 0);
		draw->AddRectFilled(ImVec2(pos.x, pos.y), ImVec2(pos.x + 5, pos.y + 50 + padding), ImColor(10, 104, 255), 5, ImDrawCornerFlags_Left);
		draw->AddText(ImVec2(pos.x + 20, pos.y + 25 - label_size.y / 2 + padding), GetColorU32(ImGuiCol_Text), label);
		ImGui::SameLine();
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8);


		ImGui::SliderFloat(E("Value"), valueee, min, max);



		return true;
	}

}


bool FeatInit = false;
template <typename T>
struct Feature {
	std::string texte;
	T a;
	int min;
	int max;
};

// Déclarer un vecteur de Feature<T>

//std::vector<Feature> Features;




void menu::init_menu() {
	ImGuiIO& io = ImGui::GetIO();

	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;

	ImFontConfig font_config;
	font_config.PixelSnapH = false;
	font_config.FontDataOwnedByAtlas = false;
	font_config.OversampleH = 5;
	font_config.OversampleV = 5;
	font_config.RasterizerMultiply = 1.2f;

	static const ImWchar ranges[] = {
		0x0020, 0x00FF, // Basic Latin + Latin Supplement
		0x0400, 0x052F, // Cyrillic + Cyrillic Supplement
		0x2DE0, 0x2DFF, // Cyrillic Extended-A
		0xA640, 0xA69F, // Cyrillic Extended-B
		0xE000, 0xE226, // icons
		0,
	};

	font_config.GlyphRanges = ranges;

	io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\tahoma.ttf", 14, &font_config, ranges);
	io.Fonts->AddFontFromMemoryTTF(icons_binary, sizeof icons_binary, 15, &font_config, ranges);
	ImGuiStyle* Style = &ImGui::GetStyle();
	ImVec4* Colors = Style->Colors;
	Colors[ImGuiCol_FrameBg] = ImVec4(ImColor(24, 25, 31));
	Colors[ImGuiCol_FrameBgHovered] = ImVec4(ImColor(24, 25, 31));
	Colors[ImGuiCol_FrameBgActive] = ImVec4(ImColor(24, 25, 31));
	// Our state
	ImVec4 clear_color = ImVec4(10.f / 255, 104.f / 255, 255.f /255, 1.00f);
}
bool croute = false;
char filterText[128];
char filterVehText[128];
char filterConText[128];
char filterModText[128];
char filterSearchText[128];

const char* VehicleName;
const char* ModelName;
ImVec2 WindPos(0,0);



auto draw_console() -> void {

	ImGui::InputTextWithHint(E("##fffff"), "Search", filterSearchText, sizeof(filterSearchText));
	if (ImGui::Button("Clear")) {
		ClearConsole();
	}
	ImGui::SameLine();

	if (ImGui::Button("Copy")) {

	}
	ImGui::Separator();
	ImGui::BeginChild("scrolling");
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 1));



	const auto& messages = GetMessages();
	for (const auto& message : messages) {
		if (strstr(message.c_str(), filterSearchText) != nullptr) {
			ImGui::TextUnformatted(message.c_str());
			ImGui::SameLine();
			if (ImGui::Button("Copy")) {
				ImGui::SetClipboardText(message.c_str());
			}
		}
	}

		//if (ScrollToBottom)
		//    ImGui::SetScrollHere(1.0f);

		ImGui::PopStyleVar();
		ImGui::EndChild();
}
void LoginNow()
{
	KeyAuthApp.init();

	KeyAuthApp.license(keyy);

	if (KeyAuthApp.data.success) {
		settings::auth = 2;
	}
	else {

	}
}

void menu::render_menu() {
	if (!croute) {
		KeyAuthApp.init();

		//SAFE_CALL(_beginthreadex)(0, 0, (_beginthreadex_proc_type)Heart, 0, 0, 0);
		croute = true;
	}
	if (!f1_key) {
		if (SAFE_CALL(GetAsyncKeyState)((VK_F1)) & 1)
		{
			f1_key = true;
			menu::show_menu = true;
		}
	}

	if (f1_key) {
		if (!settings::init) {
			settings::auth = 1;
			settings::init = true;
		}
	}

	if (f1_key) {
		if (settings::init) {
			if (settings::auth == 1) {

				//Auth::Login(Auth::GetHWID());


				//settings::can_use_menu = true;
				//settings::auth = 2;
				ImGui::GetIO().MouseDrawCursor = true;

				ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(0, 0), ImVec2(fivem::WindowSize.x, fivem::WindowSize.y), ImColor(0, 0, 0, 100));

				PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
				PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(325, 310));

				ImGui::Begin("Easy Cheat | loader", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize); {
					auto window = GetCurrentWindow();
					auto draw = window->DrawList;
					auto pos = window->Pos;
					auto size = window->Size;
					auto style = GetStyle();

					custom.m_anim = ImLerp(custom.m_anim, 1.f, 0.03f);

					draw->AddLine(pos + ImVec2(65, 40), pos + ImVec2(size.x - 15, 40), ImColor(1.f, 1.f, 1.f, 0.05f));


					SetCursorPos(ImVec2(70, 13));

					SetCursorPos(ImVec2(65, 50));
					BeginChild("##login ch  ilds", ImVec2(GetWindowWidth() - 80, GetWindowHeight() - 80)); {

						if (custom.m_tab_login == 0) {
							custom.begin_child("Login", ImVec2(GetWindowWidth(), GetWindowHeight())); {

								ImGui::Text(E("Username:"));
								ImGui::InputText(E("##Username"), username, IM_ARRAYSIZE(username), ImGuiInputTextFlags_Password);
								ImGui::Text(E("Password:"));
								ImGui::InputText(E("##Password"), password, IM_ARRAYSIZE(password), ImGuiInputTextFlags_Password);

								if (ImGui::Button(E("Login"))) {
									KeyAuthApp.login(username, password);
									if (KeyAuthApp.data.success) {
										settings::init = true;
										settings::auth = 2;
										settings::can_use_menu = true;
									}
									else {

									}
									//LoginNow();

								}
							} custom.end_child();
						}
						else {
							custom.begin_child("Register", ImVec2(GetWindowWidth(), GetWindowHeight())); {
								ImGui::Text(E("Username:"));
								ImGui::InputText(E("##name"), username, IM_ARRAYSIZE(username));

								ImGui::Text(E("Password:"));
								ImGui::InputText(E("##Password"), password, IM_ARRAYSIZE(password), ImGuiInputTextFlags_Password);

								ImGui::Text(E("License:"));
								ImGui::InputText(E("##License"), keyy, IM_ARRAYSIZE(keyy));

								if (ImGui::Button(E("Register"))) {
									KeyAuthApp.regstr(username, password, keyy);
									if (KeyAuthApp.data.success) {
										settings::init = true;
										settings::auth = 2;
										settings::can_use_menu = true;
									}
									else {

									}
								}
							} custom.end_child();
						}

					}
					ImGui::EndChild();



					SetCursorPosY(0);
					custom.tab_area("##tab_area", ImVec2(50, size.y), []() {
						for (int i = 0; i < custom.tabs_login.size(); ++i)
							if (custom.tab(custom.login_tabs_icons.at(i), custom.tabs_login.at(i), custom.m_tab_login == i) && custom.m_tab_login != i)
								custom.m_tab_login = i, custom.m_anim = 0.f;
						});
					auto draww = ImGui::GetForegroundDrawList();

					draww->AddImage(logo, pos + ImVec2(17, 15), pos + ImVec2(37, 35), ImVec2(0, 0), ImVec2(1, 1), ImColor(1.f, 1.f, 1.f, 1.f));

					// footer
					//draw->AddRectFilled(pos + ImVec2(0, size.y - 20), pos + size, ImColor(15, 14, 21), style.WindowRounding, ImDrawFlags_RoundCornersBottom);
				//	draw->AddText(pos + ImVec2(5, size.y - 18), GetColorU32(ImGuiCol_Text), E("alprazolam.fun - loader"));
					//draw->AddText(pos + ImVec2(size.x - CalcTextSize(__DATE__).x - 5, size.y - 18), GetColorU32(ImGuiCol_Text), __DATE__);
				} ImGui::End();

				PopStyleVar(2);
			}

			if (settings::auth == 2) {
				if (settings::init) {
					if (settings::can_use_menu) {
			
							visuals::player_esp();
							visuals::vehicle_esp();
							locations::visuals();
							object::visuals();
							if(settings::self::noclip_type == 0)
							noclip::noclip();
							radar::radar();
			
						if (settings::misc::watermark) {

							if (settings::misc::watermark) {

								std::string text = E("Easy public - 2.0.0 - ") + std::string(__DATE__) + E(" beta version logged at : user");

								ImGui::GetForegroundDrawList()->AddText(ImVec2(10, ImGui::GetIO().DisplaySize.y - 25), ImColor(255, 255, 255, 255), text.c_str());

							}
						/*	ImGui::SetNextWindowPos(ImVec2(5, 5));

							if (ImGui::Begin(E("Aspera.re - watermark"), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove)) {
								ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(ImColor(128, 128, 128)));
								ImGui::Text(E("Asperacheat.re | user: user | %s | %.1f fps "), __DATE__, ImGui::GetIO().Framerate);
								ImGui::PopStyleColor();
								ImVec2 windowPos = ImGui::GetWindowPos();
								ImVec2 windowSize = ImGui::GetWindowSize();
								ImGui::GetWindowDrawList()->AddLine(ImVec2(windowPos.x, windowPos.y + windowSize.y - 1), ImVec2(windowPos.x + windowSize.x, windowPos.y + windowSize.y - 1), ImColor(150, 240, 150, 255));
							}

							ImGui::End();*/
						}

						if (settings::visuals::crosshair) {
							if (settings::visuals::crossahir_style == 0) {
								auto draw = ImGui::GetBackgroundDrawList();
								draw->AddCircle(ImVec2(fivem::WindowSize.x / 2, fivem::WindowSize.y / 2), 3, settings::visuals::crosshair_color, 100, 0.0f);
							}

							if (settings::visuals::crossahir_style == 1) {
								auto draw = ImGui::GetBackgroundDrawList();

								auto drx = fivem::WindowSize.x / 2;
								auto dry = fivem::WindowSize.y / 2;

								draw->AddLine({ drx - 10, dry }, { drx + 10 , dry }, settings::visuals::crosshair_color);
								draw->AddLine({ drx, dry - 10 }, { drx, dry + 10 }, settings::visuals::crosshair_color);
							}
						}

						if (settings::visuals::fov_circle) {
							ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(fivem::WindowSize.x / 2, fivem::WindowSize.y / 2), settings::aimbot::aimbot_fov * 10, settings::visuals::fov_color, 100.0f);

							if (settings::visuals::fov_circle_filled) {
								ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(fivem::WindowSize.x / 2, fivem::WindowSize.y / 2), settings::aimbot::aimbot_fov * 10, ImColor(0, 0, 0, 100), 100.0f);
							}
						}
						if (settings::visuals::magic_fov_circle) {
							ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(fivem::WindowSize.x / 2, fivem::WindowSize.y / 2), settings::aimbot::magic_fov * 10, settings::visuals::magic_color, 100.0f);

							if (settings::visuals::magic_fov_circle_filled) {
								ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(fivem::WindowSize.x / 2, fivem::WindowSize.y / 2), settings::aimbot::magic_fov * 10, ImColor(10, 10, 10, 100), 100.0f);
							}
						}

						if ((GetAsyncKeyState)(settings::misc::hotkey) & 1) {
							menu::show_menu = !menu::show_menu;
						}

						if (SAFE_CALL(GetAsyncKeyState)(settings::self::hotkey_noclip) & 1)
						{
							settings::self::noclip = !settings::self::noclip;
						}

				

						ImGui::GetIO().MouseDrawCursor = show_menu;
						auto drawww = ImGui::GetForegroundDrawList();

						if (settings::self::freecam) {
							if (GetAsyncKeyState(VK_RIGHT) & 1) {

								settings::self::FreeCamInt += 1;

							}

							if (GetAsyncKeyState(VK_LEFT) & 1) {

								settings::self::FreeCamInt -= 1;

							}
							if (settings::self::FreeCamInt > 6)
								settings::self::FreeCamInt = 0;
							if (settings::self::FreeCamInt < 0)
								settings::self::FreeCamInt = 6;
							int sizze = CalcTextSize(settings::self::FreeCamType[settings::self::FreeCamInt]).x;
							drawww->AddText(ImVec2(fivem::WindowSize.x / 2 - (sizze / 2), 20), GetColorU32(ImGuiCol_Text), settings::self::FreeCamType[settings::self::FreeCamInt]);

						}
						if (!menu::show_menu)
							return;

						ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(0, 0), ImVec2(fivem::WindowSize.x, fivem::WindowSize.y), ImColor(0, 0, 0, 100));

						static float color[4] = { 1.f, 1.f, 1.f, 1.f };

						PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
						PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(settings::misc::menu_size_x, settings::misc::menu_size_y));

						auto windows_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse;

						if (settings::misc::lock_menu_layout) {
							windows_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;
						}

						ImGui::Begin(E("Alprazolam Main Windows"), NULL, windows_flags); {
							auto window = GetCurrentWindow();
							auto draw = window->DrawList;
							auto pos = window->Pos;
							auto size = window->Size;
							auto style = GetStyle();
							WindPos = ImVec2 ( pos.x + size.x , pos.y);
							custom.m_anim = ImLerp(custom.m_anim, 1.f, 0.03f);

							draw->AddLine(pos + ImVec2(65, 40), pos + ImVec2(size.x - 15, 40), ImColor(1.f, 1.f, 1.f, 0.05f));

							switch (custom.m_tab) {
							case 0:

								SetCursorPos(ImVec2(70, 13));
								BeginGroup();

								for (int i = 0; i < custom.rage_subtabs.size(); ++i) {
									if (custom.sub_tab(custom.rage_subtabs.at(i), custom.m_rage_subtab == i) && custom.m_rage_subtab != i)
										custom.m_rage_subtab = i, custom.m_anim = 0.f;

									if (i != custom.rage_subtabs.size() - 1)
										SameLine();
								}

								EndGroup();

								SetCursorPos(ImVec2(65, 50));
								BeginChild("##rage_childs", ImVec2(GetWindowWidth() - 80, GetWindowHeight() - 80)); {
									switch (custom.m_rage_subtab) {
									case 0:

										custom.begin_child(E("General"), ImVec2(GetWindowWidth() / 2 - GetStyle().ItemSpacing.x / 2, GetWindowHeight())); {
											ImGui::Checkbox(E("Enabled"), &settings::aimbot::enabled);

											//ImGui::Hotkey(E("Aim Key : "), &settings::aimbot::hotkey, ImVec2(160, 20));

											ImGui::Checkbox(E("Visible Check"), &settings::aimbot::only_visible);
											ImGui::Checkbox(E("Trigger Bot"), &settings::aimbot::triggerbot);

							

											ImGui::Checkbox(E("Fov Circle"), &settings::visuals::fov_circle);
											if (settings::visuals::fov_circle) {
												ImGui::SameLine();

												ImGui::ColorEdit4(E(("##fovcolor")), settings::tempcolor::fov_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoBorder);
												settings::visuals::fov_color.Value.x = settings::tempcolor::fov_color[0];
												settings::visuals::fov_color.Value.y = settings::tempcolor::fov_color[1];
												settings::visuals::fov_color.Value.z = settings::tempcolor::fov_color[2];
												settings::visuals::fov_color.Value.w = settings::tempcolor::fov_color[3];

												ImGui::Checkbox(E("Fill Fov Circle"), &settings::visuals::fov_circle_filled);
											}

								/*			ImGui::Checkbox(E("Silent Fov Circle"), &settings::visuals::magic_fov_circle);
											if (settings::visuals::magic_fov_circle) {
												ImGui::SameLine();

												ImGui::ColorEdit4(E(("##magicfovcolor")), settings::tempcolor::magic_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoBorder);
												settings::visuals::magic_color.Value.x = settings::tempcolor::magic_color[0];
												settings::visuals::magic_color.Value.y = settings::tempcolor::magic_color[1];
												settings::visuals::magic_color.Value.z = settings::tempcolor::magic_color[2];
												settings::visuals::magic_color.Value.w = settings::tempcolor::magic_color[3];

												ImGui::Checkbox(E("Silent Fill Fov Circle"), &settings::visuals::magic_fov_circle_filled);
											}*/
											ImGui::Checkbox(E("Prediction"), &settings::aimbot::prediction);

											ImGui::Checkbox(E("Preview Target"), &settings::visuals::preview_target);
											if (settings::visuals::preview_target) {
												ImGui::Combo(E("Preview Style"), &settings::visuals::preview_style, settings::visuals::ssxs, IM_ARRAYSIZE(settings::visuals::ssxs));
											}
											ImGui::Separator();
											ImGui::Text("Ignore");

											ImGui::Checkbox(E("Ignore Invisible"), &settings::aimbot::avoid_invisible);
											ImGui::Checkbox(E("Ignore Friends"), &settings::aimbot::avoid_target_friend);
										} custom.end_child();

										SameLine();

										custom.begin_child(E("Settings"), ImVec2(GetWindowWidth() / 2 - GetStyle().ItemSpacing.x / 2, GetWindowHeight())); {
											ImGui::Combo(E("Aimbot Target"), &settings::aimbot::aimbot_target, settings::aimbot::aimbot_target_list, IM_ARRAYSIZE(settings::aimbot::aimbot_target_list), 4);
											ImGui::Combo(E("Aimbot Bone"), &settings::aimbot::aimbot_bone, settings::aimbot::aimbot_bones_list, IM_ARRAYSIZE(settings::aimbot::aimbot_bones_list));
											ImGui::Combo(E("Aimbot Type"), &settings::aimbot::aimbot_type, settings::aimbot::aimbot_type_list, IM_ARRAYSIZE(settings::aimbot::aimbot_type_list));
										//	ImGui::Checkbox(E("Silent"), &settings::aimbot::silent);

										//	ImGui::Combo(E("Silent Type"), &settings::aimbot::magic_aimbot_type, settings::aimbot::magic_aimbot_type_list, IM_ARRAYSIZE(settings::aimbot::magic_aimbot_type_list));

											ImGui::Separator();
							
											ImGui::SliderInt(E("Field Of View"), &settings::aimbot::aimbot_fov, 0, 60);
											ImGui::SliderInt(E("Silent Field Of View"), &settings::aimbot::magic_fov, 0, 60);

											ImGui::SliderInt(E("Smoothing"), &settings::aimbot::aimbot_smooth, 0, 20);
											ImGui::SliderFloat(E("Curve"), &settings::aimbot::curve, 0, 1);

											ImGui::SliderInt(E("Distance"), &settings::aimbot::aimbot_distance, 0, 1000);
									
										} custom.end_child();

										break;

									case 1:

										custom.begin_child(E("Trigger Option"), ImVec2(GetWindowWidth() / 2 - GetStyle().ItemSpacing.x / 2, GetWindowHeight())); {
									
											ImGui::Checkbox(E("Enable Trigger Bot"), &settings::aimbot::triggerbot);
											ImGui::Checkbox(E("Enable delay "), &settings::aimbot::delay);



								
										} custom.end_child();

										SameLine();

										custom.begin_child(E("Settings"), ImVec2(GetWindowWidth() / 2 - GetStyle().ItemSpacing.x / 2, GetWindowHeight())); {
											ImGui::SliderInt(E("Delay"), &settings::aimbot::triggerbot_delay, 0, 4000,"%d ms");


										} custom.end_child();

										break;
									}
								} EndChild();

								break;

							case 1:

								SetCursorPos(ImVec2(70, 13));
								BeginGroup();

								for (int i = 0; i < custom.visuals_subtabs.size(); ++i) {
									if (custom.sub_tab(custom.visuals_subtabs.at(i), custom.m_visuals_subtab == i) && custom.m_visuals_subtab != i)
										custom.m_visuals_subtab = i, custom.m_anim = 0.f;

									if (i != custom.visuals_subtabs.size() - 1)
										SameLine();
								}

								EndGroup();

								SetCursorPos(ImVec2(65, 50));
								BeginChild("##visuals_childs", ImVec2(GetWindowWidth() - 80, GetWindowHeight() - 80)); {
									switch (custom.m_visuals_subtab) {
									case 0:

										custom.begin_child(E("Players"), ImVec2(GetWindowWidth() / 2 - GetStyle().ItemSpacing.x / 2, GetWindowHeight())); {
											ImGui::Checkbox(E("Enabled"), &settings::visuals::enabled);

											ImGui::Checkbox(E("Visible Check"), &settings::visuals::visible_check);
											if (settings::visuals::visible_check) {
												ImGui::Combo("Visible Check Type", &settings::visuals::visible_check_type, settings::visuals::visible_check_choice_text, IM_ARRAYSIZE(settings::visuals::visible_check_choice_text));
											}
											ImGui::Checkbox(E("Invisible Check"), &settings::visuals::invisible_check);
											if (settings::visuals::invisible_check) {
												if (settings::visuals::invisible_check_type == 1) {
													ImGui::SameLine();

													ImGui::ColorEdit4(E(("##cacalol")), settings::tempcolor::invisible_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoBorder);
													settings::visuals::invisible_color.Value.x = settings::tempcolor::invisible_color[0];
													settings::visuals::invisible_color.Value.y = settings::tempcolor::invisible_color[1];
													settings::visuals::invisible_color.Value.z = settings::tempcolor::invisible_color[2];
													settings::visuals::invisible_color.Value.w = settings::tempcolor::invisible_color[3];
												}
												ImGui::Combo("Invisible Check Type", &settings::visuals::invisible_check_type, settings::visuals::invisible_check_type_text, IM_ARRAYSIZE(settings::visuals::invisible_check_type_text));
											}
											ImGui::Checkbox(E("Friends Check"), &settings::visuals::friend_visuals);
											if (settings::visuals::friend_visuals) {
												if (settings::visuals::friend_visuals_check_type == 1) {
													ImGui::SameLine();

													ImGui::ColorEdit4(E(("##cacaccclol")), settings::tempcolor::friends_colors, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoBorder);
													settings::visuals::friends_colors.Value.x = settings::tempcolor::friends_colors[0];
													settings::visuals::friends_colors.Value.y = settings::tempcolor::friends_colors[1];
													settings::visuals::friends_colors.Value.z = settings::tempcolor::friends_colors[2];
													settings::visuals::friends_colors.Value.w = settings::tempcolor::friends_colors[3];
												}
												ImGui::Combo("Friends Check Type", &settings::visuals::friend_visuals_check_type, settings::visuals::friend_visuals_check_type_text, IM_ARRAYSIZE(settings::visuals::friend_visuals_check_type_text));
											}
											ImGui::Checkbox(E("Box"), &settings::visuals::box_esp);
											if (settings::visuals::box_esp) {
												ImGui::SameLine();

												ImGui::ColorEdit4(E(("##ColosqsqrBo44")), settings::tempcolor::box_color_visible, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoBorder);
												settings::visuals::box_color_visible.Value.x = settings::tempcolor::box_color_visible[0];
												settings::visuals::box_color_visible.Value.y = settings::tempcolor::box_color_visible[1];
												settings::visuals::box_color_visible.Value.z = settings::tempcolor::box_color_visible[2];
												settings::visuals::box_color_visible.Value.w = settings::tempcolor::box_color_visible[3];

												ImGui::SameLine();

												ImGui::ColorEdit4((E("##ColorBddssso44")), settings::tempcolor::box_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoBorder);
												settings::visuals::box_color.Value.x = settings::tempcolor::box_color[0];
												settings::visuals::box_color.Value.y = settings::tempcolor::box_color[1];
												settings::visuals::box_color.Value.z = settings::tempcolor::box_color[2];
												settings::visuals::box_color.Value.w = settings::tempcolor::box_color[3];
											}
											ImGui::Checkbox(E("Filled"), &settings::visuals::filled_esp);
											if (settings::visuals::filled_esp) {
												ImGui::SameLine();

												ImGui::ColorEdit4(("##ColsqdqsdsqsqrBo44"), settings::tempcolor::filled_color_visible, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoBorder);
												settings::visuals::filled_color_visible.Value.x = settings::tempcolor::filled_color_visible[0];
												settings::visuals::filled_color_visible.Value.y = settings::tempcolor::filled_color_visible[1];
												settings::visuals::filled_color_visible.Value.z = settings::tempcolor::filled_color_visible[2];
												settings::visuals::filled_color_visible.Value.w = settings::tempcolor::filled_color_visible[3];

												ImGui::SameLine();

												ImGui::ColorEdit4(("##ColorBsdsqddssso44"), settings::tempcolor::filled_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoBorder);
												settings::visuals::filled_color.Value.x = settings::tempcolor::filled_color[0];
												settings::visuals::filled_color.Value.y = settings::tempcolor::filled_color[1];
												settings::visuals::filled_color.Value.z = settings::tempcolor::filled_color[2];
												settings::visuals::filled_color.Value.w = settings::tempcolor::filled_color[3];
											}
											ImGui::Checkbox(E("Skeleton"), &settings::visuals::skeleton_esp);
											if (settings::visuals::skeleton_esp) {
												ImGui::SameLine();

												ImGui::ColorEdit4(E(("##ColorBo44")), settings::tempcolor::skeleton_color_visible, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoBorder);
												settings::visuals::skeleton_color_visible.Value.x = settings::tempcolor::skeleton_color_visible[0];
												settings::visuals::skeleton_color_visible.Value.y = settings::tempcolor::skeleton_color_visible[1];
												settings::visuals::skeleton_color_visible.Value.z = settings::tempcolor::skeleton_color_visible[2];
												settings::visuals::skeleton_color_visible.Value.w = settings::tempcolor::skeleton_color_visible[3];

												ImGui::SameLine();

												ImGui::ColorEdit4(("##ColorBddo44"), settings::tempcolor::skeleton_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoBorder);
												settings::visuals::skeleton_color.Value.x = settings::tempcolor::skeleton_color[0];
												settings::visuals::skeleton_color.Value.y = settings::tempcolor::skeleton_color[1];
												settings::visuals::skeleton_color.Value.z = settings::tempcolor::skeleton_color[2];
												settings::visuals::skeleton_color.Value.w = settings::tempcolor::skeleton_color[3];
											}

											ImGui::Checkbox(E("Health Bar"), &settings::visuals::health_bar);

											ImGui::Checkbox(E("Player Name"), &settings::visuals::player_name);
											if (settings::visuals::player_name) {
												ImGui::SameLine();

												ImGui::ColorEdit4(("##qC1olorddsdsdsBo44"), settings::tempcolor::player_name_color_visible, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoBorder);
												settings::visuals::player_name_color_visible.Value.x = settings::tempcolor::player_name_color_visible[0];
												settings::visuals::player_name_color_visible.Value.y = settings::tempcolor::player_name_color_visible[1];
												settings::visuals::player_name_color_visible.Value.z = settings::tempcolor::player_name_color_visible[2];
												settings::visuals::player_name_color_visible.Value.w = settings::tempcolor::player_name_color_visible[3];

												ImGui::SameLine();

												ImGui::ColorEdit4(("##Colo12rplayer_nameBddo44"), settings::tempcolor::player_name_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoBorder);
												settings::visuals::player_name_color.Value.x = settings::tempcolor::player_name_color[0];
												settings::visuals::player_name_color.Value.y = settings::tempcolor::player_name_color[1];
												settings::visuals::player_name_color.Value.z = settings::tempcolor::player_name_color[2];
												settings::visuals::player_name_color.Value.w = settings::tempcolor::player_name_color[3];
											}
											ImGui::Checkbox(E("Health Text"), &settings::visuals::health_text);
											if (settings::visuals::health_text) {
												ImGui::SameLine();

												ImGui::ColorEdit4(("##qC1olorBo44"), settings::tempcolor::health_color_visible, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoBorder);
												settings::visuals::health_color_visible.Value.x = settings::tempcolor::health_color_visible[0];
												settings::visuals::health_color_visible.Value.y = settings::tempcolor::health_color_visible[1];
												settings::visuals::health_color_visible.Value.z = settings::tempcolor::health_color_visible[2];
												settings::visuals::health_color_visible.Value.w = settings::tempcolor::health_color_visible[3];

												ImGui::SameLine();

												ImGui::ColorEdit4(("##Colo12rBddo44"), settings::tempcolor::health_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoBorder);
												settings::visuals::health_color.Value.x = settings::tempcolor::health_color[0];
												settings::visuals::health_color.Value.y = settings::tempcolor::health_color[1];
												settings::visuals::health_color.Value.z = settings::tempcolor::health_color[2];
												settings::visuals::health_color.Value.w = settings::tempcolor::health_color[3];
											}

											ImGui::Checkbox(E("Distance"), &settings::visuals::distance_text);
											if (settings::visuals::distance_text) {
												ImGui::SameLine();

												ImGui::ColorEdit4(("##CzeolorBo44"), settings::tempcolor::distance_color_visible, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoBorder);
												settings::visuals::distance_color_visible.Value.x = settings::tempcolor::distance_color_visible[0];
												settings::visuals::distance_color_visible.Value.y = settings::tempcolor::distance_color_visible[1];
												settings::visuals::distance_color_visible.Value.z = settings::tempcolor::distance_color_visible[2];
												settings::visuals::distance_color_visible.Value.w = settings::tempcolor::distance_color_visible[3];

												ImGui::SameLine();

												ImGui::ColorEdit4(("##CssolorBddo44"), settings::tempcolor::distance_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoBorder);
												settings::visuals::distance_color.Value.x = settings::tempcolor::distance_color[0];
												settings::visuals::distance_color.Value.y = settings::tempcolor::distance_color[1];
												settings::visuals::distance_color.Value.z = settings::tempcolor::distance_color[2];
												settings::visuals::distance_color.Value.w = settings::tempcolor::distance_color[3];
											}
											ImGui::Checkbox(E("Weapon Name"), &settings::visuals::weapon_name);
											if (settings::visuals::weapon_name) {
												ImGui::SameLine();

												ImGui::ColorEdit4(("##qC1olordéédBo44"), settings::tempcolor::weapon_name_color_visible, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoBorder);
												settings::visuals::weapon_name_color_visible.Value.x = settings::tempcolor::weapon_name_color_visible[0];
												settings::visuals::weapon_name_color_visible.Value.y = settings::tempcolor::weapon_name_color_visible[1];
												settings::visuals::weapon_name_color_visible.Value.z = settings::tempcolor::weapon_name_color_visible[2];
												settings::visuals::weapon_name_color_visible.Value.w = settings::tempcolor::weapon_name_color_visible[3];

												ImGui::SameLine();

												ImGui::ColorEdit4(("##Colo12rplayerzeze_nameBddo44"), settings::tempcolor::weapon_name_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoBorder);
												settings::visuals::weapon_name_color.Value.x = settings::tempcolor::weapon_name_color[0];
												settings::visuals::weapon_name_color.Value.y = settings::tempcolor::weapon_name_color[1];
												settings::visuals::weapon_name_color.Value.z = settings::tempcolor::weapon_name_color[2];
												settings::visuals::weapon_name_color.Value.w = settings::tempcolor::weapon_name_color[3];
											}

											ImGui::Checkbox(E("Snapline"), &settings::visuals::snapline);
											if (settings::visuals::snapline) {
												ImGui::SameLine();

												ImGui::ColorEdit4(("##qC1olorddddsdsdsdsdBo44"), settings::tempcolor::snapline_color_visible, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoBorder);
												settings::visuals::snapline_color_visible.Value.x = settings::tempcolor::snapline_color_visible[0];
												settings::visuals::snapline_color_visible.Value.y = settings::tempcolor::snapline_color_visible[1];
												settings::visuals::snapline_color_visible.Value.z = settings::tempcolor::snapline_color_visible[2];
												settings::visuals::snapline_color_visible.Value.w = settings::tempcolor::snapline_color_visible[3];

												ImGui::SameLine();

												ImGui::ColorEdit4(("##Colo12rplayer_naazemeBddo44"), settings::tempcolor::snapline_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoBorder);
												settings::visuals::snapline_color.Value.x = settings::tempcolor::snapline_color[0];
												settings::visuals::snapline_color.Value.y = settings::tempcolor::snapline_color[1];
												settings::visuals::snapline_color.Value.z = settings::tempcolor::snapline_color[2];
												settings::visuals::snapline_color.Value.w = settings::tempcolor::snapline_color[3];
											}
								
										} custom.end_child();

										SameLine();

										custom.begin_child(E("Other"), ImVec2(GetWindowWidth() / 2 - GetStyle().ItemSpacing.x / 2, GetWindowHeight())); {
											ImGui::Checkbox(E("Preview ESP"), &settings::visuals::Preview);

											ImGui::Combo(E("Box Style"), &settings::visuals::esp_type, settings::visuals::esp_type_text, IM_ARRAYSIZE(settings::visuals::esp_type_text));

											ImGui::Separator();

											ImGui::Checkbox(E("LocalPlayer"), &settings::visuals::draw_self);
											ImGui::Checkbox(E("Pedestrian"), &settings::visuals::draw_peds);
											ImGui::Checkbox(E("Only Alive"), &settings::visuals::only_alive);

											ImGui::Separator();

											ImGui::Checkbox(E("Outlined Box"), &settings::visuals::outlined);
											ImGui::SliderInt(E("Render Distance"), &settings::visuals::esp_distance, 0, 1000);
											ImGui::SliderInt(E("Box Rounding"), &settings::visuals::box_rounding, 0, 5);
											ImGui::SliderFloat(E("Dynamic debug"), &settings::visuals::Dynamicdebug, -10, 10);

											ImGui::SliderFloat("Box Size", &settings::visuals::box_size, 1.5f, 2.75f);
											ImGui::Combo(E("Health Bar Position"), &settings::visuals::healthbar_type, settings::visuals::healthbar_type_text, IM_ARRAYSIZE(settings::visuals::healthbar_type_text));
										} custom.end_child();

										break;

									case 1:

										custom.begin_child(E("Vehicle"), ImVec2(GetWindowWidth() / 2 - GetStyle().ItemSpacing.x / 2, GetWindowHeight())); {
											ImGui::Checkbox("Enabled", &settings::visuals::vehicle::main_enabled);

											ImGui::InputText(E("Filter"), filterText, sizeof(filterText));

											int selectedItem = -1;

											ImGui::ListBoxHeader(E("##vehicletype"), ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y));

											for (int i = 0; i < IM_ARRAYSIZE(settings::visuals::vehicle::model); i++) {
												const char* weaponName = settings::visuals::vehicle::model[i];

												if (strstr(weaponName, filterText) != nullptr) {
													bool isSelected = (settings::visuals::vehicle::selected == i);
													if (ImGui::Selectable(weaponName, isSelected)) {
														selectedItem = i;
													}
												}
											}
											ImGui::ListBoxFooter();

											if (selectedItem != -1) {
												settings::visuals::vehicle::selected = selectedItem;
											}
										} custom.end_child();

										SameLine();

										custom.begin_child(E("Vehicle Visuals Settings"), ImVec2(GetWindowWidth() / 2 - GetStyle().ItemSpacing.x / 2, GetWindowHeight())); {
											if (settings::visuals::vehicle::selected == 0) {
												ImGui::Checkbox("Enable", &settings::visuals::vehicle::car_enabled);

												ImGui::Checkbox("Marker", &settings::visuals::vehicle::car_marker);
												ImGui::Checkbox("Distance", &settings::visuals::vehicle::car_distance);
												ImGui::Checkbox("Plate", &settings::visuals::vehicle::car_show_plate);
												ImGui::Checkbox("Lock State", &settings::visuals::vehicle::car_lock);
											}

											if (settings::visuals::vehicle::selected == 1) {
												ImGui::Checkbox("Enable", &settings::visuals::vehicle::boat_enabled);

												ImGui::Checkbox("Marker", &settings::visuals::vehicle::boat_marker);
												ImGui::Checkbox("Distance", &settings::visuals::vehicle::boat_distance);
												ImGui::Checkbox("Plate", &settings::visuals::vehicle::boat_show_plate);
												ImGui::Checkbox("Lock State", &settings::visuals::vehicle::boat_lock);
											}

											if (settings::visuals::vehicle::selected == 2) {
												ImGui::Checkbox("Enable", &settings::visuals::vehicle::heli_enabled);

												ImGui::Checkbox("Marker", &settings::visuals::vehicle::heli_marker);
												ImGui::Checkbox("Distance", &settings::visuals::vehicle::heli_distance);
												ImGui::Checkbox("Plate", &settings::visuals::vehicle::heli_show_plate);
												ImGui::Checkbox("Lock State", &settings::visuals::vehicle::heli_lock);
											}
										} custom.end_child();

										break;

									case 2:

										custom.begin_child(E("Object Settings"), ImVec2(GetWindowWidth() / 2 - GetStyle().ItemSpacing.x / 2, GetWindowHeight())); {
											object::settings();
										} custom.end_child();

										SameLine();

										custom.begin_child(E("Object Visuals Settings"), ImVec2(GetWindowWidth() / 2 - GetStyle().ItemSpacing.x / 2, GetWindowHeight())); {
											ImGui::Checkbox(E("Marker"), &settings::visuals::object::marker);
											ImGui::Checkbox(E("Distance"), &settings::visuals::object::distance);
											ImGui::Checkbox(E("Snapline"), &settings::visuals::object::snapline);
										} custom.end_child();

										break;
									case 3:

										custom.begin_child(E("Radar"), ImVec2(GetWindowWidth() / 2 - GetStyle().ItemSpacing.x / 2, GetWindowHeight())); {

											ImGui::Checkbox(E("Radar"), &settings::visuals::radar::enabled);
											ImGui::Checkbox(E("Render Vehicule"), &settings::visuals::radar::draw_vehicle);
											ImGui::Checkbox(E("Render Dead"), &settings::visuals::radar::render_dead);
											ImGui::Checkbox(E("Render Ped"), &settings::visuals::radar::render_ped);




										} custom.end_child();

										SameLine();

										custom.begin_child(E("Other"), ImVec2(GetWindowWidth() / 2 - GetStyle().ItemSpacing.x / 2, GetWindowHeight())); {
											ImGui::SliderInt(E("X Size"), &settings::visuals::radar::size_x, 0, 1000);
											ImGui::SliderInt(E("Y Size"), &settings::visuals::radar::size_y, 0, 1000);
											ImGui::SliderInt(E("Opacity"), &settings::visuals::radar::opacity, 0, 255);

										} custom.end_child();

										break;
									}
								} EndChild();

								break;

							case 2:

								SetCursorPos(ImVec2(70, 13));
								BeginGroup();

								for (int i = 0; i < custom.player_subtabs.size(); ++i) {
									if (custom.sub_tab(custom.player_subtabs.at(i), custom.m_player_subtab == i) && custom.m_player_subtab != i)
										custom.m_player_subtab = i, custom.m_anim = 0.f;

									if (i != custom.player_subtabs.size() - 1)
										SameLine();
								}

								EndGroup();

								SetCursorPos(ImVec2(65, 50));
								BeginChild(E("##player_child"), ImVec2(GetWindowWidth() - 80, GetWindowHeight() - 80)); {
									switch (custom.m_player_subtab) {
									case 0:

										custom.begin_child(E("Self"), ImVec2(GetWindowWidth() / 2 - GetStyle().ItemSpacing.x / 2, GetWindowHeight())); {
											ImGui::Checkbox(E("Enabled"), &settings::self::enabled);

											ImGui::Checkbox(E("Godmode"), &settings::self::godmode);
											ImGui::Checkbox(E("Invisible"), &settings::self::invisible);
											ImGui::Checkbox(E("No HeadShot"), &settings::self::no_hs);
											ImGui::Checkbox(E("No Ragdoll"), &settings::self::no_ragdoll);
											ImGui::Checkbox(E("Infinite Stamina"), &settings::self::infinite_stamina);
											ImGui::Checkbox(E("Desync"), &settings::self::desync);
											ImGui::Checkbox(E("PhysGun"), &settings::self::physic_gun);
											ImGui::Checkbox(E("Rc Car"), &settings::self::rc_car);

											ImGui::SliderInt(E("Health"), &settings::self::give_health_amnt, 0, 100);

											ImGui::SliderInt(E("Armor"), &settings::self::give_armor_amnt, 0, 100);

											if (!settings::self::enabled)
												ImGui::BeginDisabled();

											if (ImGui::Button(E("Give Health"))) {
												settings::self::give_health = true;
											}

											ImGui::SameLine();

											if (ImGui::Button(E("Give Armor"))) {
												settings::self::give_armor = true;
											}

											ImGui::Separator();

											if (ImGui::Button(E("Revive"))) {
												settings::self::revive = true;
											}

											if (ImGui::Button(E("Tp To Waypoint"))) {
												settings::self::teleport_to_waypoint = true;
											}

											if (!settings::self::enabled)
												ImGui::EndDisabled();
										} custom.end_child();

										SameLine();

										custom.begin_child(E("Noclip"), ImVec2(GetWindowWidth() / 2 - GetStyle().ItemSpacing.x / 2, GetWindowHeight())); {
											ImGui::Checkbox(E("Enable Noclip"), &settings::self::noclip);
											if (settings::self::noclip) 
												ImGui::Combo(E("Noclip type"), &settings::self::noclip_type, settings::self::noclip_type_text, IM_ARRAYSIZE(settings::self::noclip_type_text));

											
											ImGui::Checkbox(E("Freecam"), &settings::self::freecam);

											ImGui::Hotkey(E("Hotkey :   "), &settings::self::hotkey_noclip, ImVec2(150, 20));

											ImGui::Separator();

											ImGui::Hotkey(E("Forward :  "), &settings::self::hotkey_forward, ImVec2(150, 20));

											ImGui::Hotkey(E("Backward : "), &settings::self::hotkey_backward, ImVec2(150, 20));

											ImGui::Hotkey(E("Left :     "), &settings::self::hotkey_left, ImVec2(150, 20));

											ImGui::Hotkey(E("Right :    "), &settings::self::hotkey_right, ImVec2(150, 20));
										} custom.end_child();

										break;

				

								

									case 1:

										custom.begin_child(E("Location Settings"), ImVec2(GetWindowWidth() / 2 - GetStyle().ItemSpacing.x / 2, GetWindowHeight())); {
											locations::location_settings();
										} custom.end_child();

										SameLine();

										custom.begin_child(E("Location List"), ImVec2(GetWindowWidth() / 2 - GetStyle().ItemSpacing.x / 2, GetWindowHeight())); {
											locations::location_list();
										} custom.end_child();

										break;
								
								case 2:

									custom.begin_child(E("Model Option"), ImVec2(GetWindowWidth() / 2 - GetStyle().ItemSpacing.x / 2, GetWindowHeight())); {

										if (ImGui::Button(E("Change Model"))) {
											ModelName = settings::self::model_changer::Model[settings::self::model_changer::ModelPos];
											settings::self::model_changer::ModelJoat = rage::joaat(ModelName);
											settings::self::model_changer::ModelChange = true;
										}
									} custom.end_child();

									SameLine();

									custom.begin_child(E("Model Settings"), ImVec2(GetWindowWidth() / 2 - GetStyle().ItemSpacing.x / 2, GetWindowHeight())); {

										ImGui::Text("Filter Model");
										ImGui::InputText(E("##ffff"), filterModText, sizeof(filterModText));

										int selectedItem = -1;

										ImGui::ListBoxHeader(E("##WeaponList"), ImVec2(GetWindowWidth() - GetStyle().ItemSpacing.x, ImGui::GetContentRegionAvail().y - 80));

										for (int i = 0; i < IM_ARRAYSIZE(settings::self::model_changer::Model); i++) {
											const char* weaponName = settings::self::model_changer::Model[i];

											// Vérifier si l'élément correspond au filtre
											if (strstr(weaponName, filterModText) != nullptr) {
												bool isSelected = (settings::self::model_changer::ModelPos == i);
												if (ImGui::Selectable(weaponName, isSelected)) {
													selectedItem = i;
												}
											}
										}

										ImGui::ListBoxFooter();

										if (selectedItem != -1) {
											settings::self::model_changer::ModelPos = selectedItem;
										}


										//ImGui::Checkbox(E("Force In Hand"), &settings::weapon::weapon_spawning::in_hand);

									//	ImGui::Separator();

									//	if (ImGui::Button(E("Give Weapon"))) {
									//		settings::weapon::weapon_spawning::give = true;
									//	}
									} custom.end_child();

									break;

									}
								} EndChild();

								break;

								case 7:

									SetCursorPos(ImVec2(70, 13));
									BeginGroup();

									
									ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 1);
									ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 1);

									ImGui::InputTextWithHint(E("##fffff"),"Search", filterSearchText, sizeof(filterSearchText));
									EndGroup();

									SetCursorPos(ImVec2(65, 50));
									BeginChild(E("##search_child"), ImVec2(GetWindowWidth() - 80, GetWindowHeight() - 80)); {
							
											switch (custom.m_search_subtab) {
											case 0:

												custom.begin_child(E("Features"), ImVec2(GetWindowWidth() - GetStyle().ItemSpacing.x / 2, GetWindowHeight())); {
													if (!FeatInit) {
														BoolFeatures.push_back({ "Aimbot", &settings::aimbot::enabled, 0, 1000 });

														IntFeatures.push_back({ "Visual Distance", &settings::visuals::esp_distance, 0, 1000 });

														FeatInit = true;
													}
													for (FeatureBool& feature : BoolFeatures) {
														if (filterSearchText == "") {

														}
														else
														{
															if (feature.texte.find(filterSearchText) != std::string::npos) {
																search_button(feature.texte.c_str(), feature.a , 0,0, 1, 0, feature.min, feature.max);

															}
														}
												
													}

													for (FeatureInt& feature : IntFeatures) {
														if (filterSearchText == "") {

														}
														else
														{
															if (feature.texte.find(filterSearchText) != std::string::npos) {
																search_button(feature.texte.c_str(), 0,feature.a,0, 1, 0, feature.min, feature.max , 1);

															}
														}
													}	
													for (FeatureFloat& feature : FloatFeatures) {
														if (filterSearchText == "") {

														}
														else
														{
															if (feature.texte.find(filterSearchText) != std::string::npos) {
																search_button(feature.texte.c_str(),0,0,feature.a, 1, 0, feature.min, feature.max, 2);

															}
														}
													}
											
										
													//search_button(E("Aimbot"), settings::aimbot::enabled, 1 , 0);

													//search_button(E("Visual"), settings::visuals::enabled, 1, 0);
													//search_button(E("Visual Distance"), settings::visuals::esp_distance, 1, 0,0,1000);
													//search_button(E("Visual Distance"), settings::visuals::esp_distance, 1, 0,0,1000);
													//search_button(E("Visual Distance"), settings::visuals::esp_distance, 1, 0,0,1000);
													//search_button(E("Visual Distance"), settings::visuals::esp_distance, 1, 0,0,1000);
													//search_button(E("Visual Distance"), settings::visuals::esp_distance, 1, 0,0,1000);
													//search_button(E("Visual Distance"), settings::visuals::esp_distance, 1, 0,0,1000);
													//search_button(E("Visual Distance"), settings::visuals::esp_distance, 1, 0,0,1000);
													//search_button(E("Visual Distance"), settings::visuals::esp_distance, 1, 0,0,1000);
													//search_button(E("Visual Distance"), settings::visuals::esp_distance, 1, 0,0,1000);

										

												} custom.end_child();

												SameLine();

												break;

										
											}
										
									}EndChild();

									break;

								case 8:
									SetCursorPos(ImVec2(70, 13));
									BeginGroup();

									for (int i = 0; i < custom.scripts_subtab.size(); ++i) {
										if (custom.sub_tab(custom.scripts_subtab.at(i), custom.m_scripts_subtab == i) && custom.m_scripts_subtab != i)
											custom.m_scripts_subtab = i, custom.m_anim = 0.f;

										if (i != custom.scripts_subtab.size() - 1)
											SameLine();
									}

									EndGroup();

							
					
									SetCursorPos(ImVec2(65, 50));
									BeginChild(E("##search_child"), ImVec2(GetWindowWidth() - 80, GetWindowHeight() - 80)); {

										switch (custom.m_scripts_subtab) {
										case 0:
											draw_console();

											break;
										case 2:
											InputText("Hash",  hashh, sizeof  hashh);
											if (ImGui::Button("Break"))
											{
												char* endptr;
												uint64_t value = std::strtoull( hashh, &endptr, 16);
												breakednative.push_back(value);
												std::string breakedstr = "Breaked "+ std::string( hashh);
												 breakednative_str.push_back(breakedstr);
											}


											Separator();
											if (ImGui::Button("Clear list"))
											{

												breakednative.clear();
												 breakednative_str.clear();
											}
											if (ImGui::Button("Create folder"))
											{
												"C:/Revo";
											}
											Separator();
											for (int index = 0; index < static_cast<int>( breakednative_str.size()); index++)
											{
												ImGui::Text( breakednative_str[index].c_str());
											}
											break;
										case 3:
											InputText("Str", consolepush, sizeof consolepush);
										
											SameLine();

											if (ImGui::Button("Clear pathmap"))
											{
												g_fastPathMap.clear();
											}
											SameLine();

											Checkbox("Filter-by-CFX-Native", &filterbycfxnative);
											Separator();
											static char bufferr[64];
											InputText("Native-filter", bufferr, sizeof bufferr);
							
											for (const auto& pair : *orin_fastPathMap) {
												uint64_t entrypoint = (uint64_t)GetNativeHandler((uint64_t)pair.first.GetHash());

												std::stringstream ss;
												uint64_t value =pair.first.GetHash();
												std::stringstream sss;
												sss << std::hex << std::uppercase << value;
												std::string hexValue = sss.str();
												if (filterbycfxnative)
												{
													if (hexValue.size() > 8) {
														continue;
													}
												}

												ss << "NAT: 0x" << std::hex << std::uppercase << pair.first.GetHash() << " | 0x" << std::hex << std::uppercase << entrypoint << " | Entrypoint: base_addr + 0x" << entrypoint - (uint64_t)GetModuleHandleA(nullptr) << " | Handler: 0x" << std::hex << std::uppercase << pair.second;
												std::string entrypointHex = ss.str();
												if (entrypointHex.find(bufferr) != std::string::npos) {
													ImGui::Text(entrypointHex.c_str());
													SameLine();
													if (ImGui::Button("Copy")) {
														ImGui::SetClipboardText(entrypointHex.c_str());
													}
												}
											}


											break;
						
										}

									}EndChild();

									break;

								case 5:

									SetCursorPos(ImVec2(70, 13));
									BeginGroup();

									for (int i = 0; i < custom.lists_subtab.size(); ++i) {
										if (custom.sub_tab(custom.lists_subtab.at(i), custom.m_lists_subtab == i) && custom.m_lists_subtab != i)
											custom.m_lists_subtab = i, custom.m_anim = 0.f;

										if (i != custom.lists_subtab.size() - 1)
											SameLine();
									}

									EndGroup();

									SetCursorPos(ImVec2(65, 50));
									BeginChild(E("##misc_child"), ImVec2(GetWindowWidth() - 80, GetWindowHeight() - 80)); {
										if (fivem::IsOffsetWorking) {

											switch (custom.m_lists_subtab) {
											case 0:

												custom.begin_child(E("Player - List"), ImVec2(GetWindowWidth() / 2 - GetStyle().ItemSpacing.x / 2, GetWindowHeight())); {
													lists::players_list();
												} custom.end_child();

												SameLine();

												custom.begin_child(E("Options"), ImVec2(GetWindowWidth() / 2 - GetStyle().ItemSpacing.x / 2, GetWindowHeight())); {
													lists::player_list_option();
												} custom.end_child();

												break;

											case 1:

												custom.begin_child(E("Vehicle - List"), ImVec2(GetWindowWidth() / 2 - GetStyle().ItemSpacing.x / 2, GetWindowHeight())); {
													lists::vehicle_list();
												} custom.end_child();

												SameLine();

												custom.begin_child(E("Options"), ImVec2(GetWindowWidth() / 2 - GetStyle().ItemSpacing.x / 2, GetWindowHeight())); {
													lists::vehicle_list_option();
												} custom.end_child();

												break;
											}
										}
									}EndChild();

									break;

							case 6:

								SetCursorPos(ImVec2(70, 13));
								BeginGroup();

								for (int i = 0; i < custom.misc_subtab.size(); ++i) {
									if (custom.sub_tab(custom.misc_subtab.at(i), custom.m_misc_subtab == i) && custom.m_misc_subtab != i)
										custom.m_misc_subtab = i, custom.m_anim = 0.f;

									if (i != custom.misc_subtab.size() - 1)
										SameLine();
								}

								EndGroup();

								SetCursorPos(ImVec2(65, 50));
								BeginChild("##misc_child", ImVec2(GetWindowWidth() - 80, GetWindowHeight() - 80)); {
									switch (custom.m_misc_subtab) {
									case 0:

										custom.begin_child(E("Misc"), ImVec2(GetWindowWidth() / 2 - GetStyle().ItemSpacing.x / 2, GetWindowHeight())); {
											ImGui::Checkbox(E("Watermark"), &settings::misc::watermark);

											ImGui::Checkbox(E("Crossahir"), &settings::visuals::crosshair);

											if (settings::visuals::crosshair) {
												ImGui::Combo(E("Crossahir Style"), &settings::visuals::crossahir_style, settings::visuals::sss, IM_ARRAYSIZE(settings::visuals::sss));
											}


											ImGui::Checkbox(E("Hitsound"), &settings::visuals::hitsound);
											if (settings::visuals::hitsound) {
												ImGui::InputText("##Hitsound Path", settings::visuals::hitsound_path, IM_ARRAYSIZE(settings::visuals::hitsound_path));
											}
											ImGui::Checkbox(E("Lock menu layout"), &settings::misc::lock_menu_layout);

											ImGui::Hotkey(E("Menu Key : "), &settings::misc::hotkey, ImVec2(160, 20));
										} custom.end_child();

										SameLine();

										custom.begin_child(E("Configs"), ImVec2(GetWindowWidth() / 2 - GetStyle().ItemSpacing.x / 2, GetWindowHeight())); {
											config::configuration();
										} custom.end_child();

										break;
									}
								} EndChild();

								break;

							case 3:

								SetCursorPos(ImVec2(70, 13));
								BeginGroup();

								for (int i = 0; i < custom.weapon_subtab.size(); ++i) {
									if (custom.sub_tab(custom.weapon_subtab.at(i), custom.m_weapon_subtab == i) && custom.m_weapon_subtab != i)
										custom.m_weapon_subtab = i, custom.m_anim = 0.f;

									if (i != custom.weapon_subtab.size() - 1)
										SameLine();
								}

								EndGroup();

								SetCursorPos(ImVec2(65, 50));
								BeginChild(E("##weapon_child"), ImVec2(GetWindowWidth() - 80, GetWindowHeight() - 80)); {
				
										switch (custom.m_weapon_subtab) {
										case 0:

											custom.begin_child(E("Weapon Settings"), ImVec2(GetWindowWidth() / 2 - GetStyle().ItemSpacing.x / 2, GetWindowHeight())); {
												ImGui::Checkbox(E("Enabled"), &settings::weapon::enabled);

												ImGui::Checkbox(E("No Recoil"), &settings::weapon::no_recoil);

												if (settings::weapon::no_recoil) {
													ImGui::SliderInt(E("Recoil"), &settings::weapon::recoil_value, 0, 5);
												}

												ImGui::Checkbox(E("No Spread"), &settings::weapon::no_spread);

												if (settings::weapon::no_spread) {
													ImGui::SliderInt(E("Spread"), &settings::weapon::spread_value, 0, 5);
												}
												ImGui::Checkbox(E("Force Gun"), &settings::weapon::force_gun);

												ImGui::Checkbox(E("No Reload"), &settings::weapon::no_reload);

												if (settings::weapon::no_reload) {
													//ImGui::SliderInt(E("Reload"), &settings::weapon::reload_value, 0, 100);
												}

												ImGui::Checkbox(E("Unlimited Range"), &settings::weapon::infinite_range);

												if (settings::weapon::infinite_range) {
													ImGui::SliderInt(E("Range"), &settings::weapon::weapon_range, 0, 1000);
												}

												ImGui::Checkbox(E("Damage Boost"), &settings::weapon::damage_boost);

												if (settings::weapon::damage_boost) {
													ImGui::SliderInt(E("Damage"), &settings::weapon::int_damage, 0, 1000);
												}

												ImGui::Checkbox(E("Infinite Ammo"), &settings::weapon::infite_ammo);

												ImGui::SliderInt(E("Ammount"), &settings::weapon::ammo_to_set, 0, 999);
												ImGui::Spacing();

												if (ImGui::Button(E("Give Ammo"))) {
													settings::weapon::set_ammo = true;
												}
											} custom.end_child();

											SameLine();

											custom.begin_child(E("Weapon Spawner"), ImVec2(GetWindowWidth() / 2 - GetStyle().ItemSpacing.x / 2, GetWindowHeight())); {
												ImGui::Checkbox(E("Enable"), &settings::weapon::weapon_spawning::weapon_spawning);

												ImGui::Text("Filter Weapon");
												ImGui::InputText(E("##ffff"), filterText, sizeof(filterText));

												int selectedItem = -1;

												ImGui::ListBoxHeader(E("##WeaponList"), ImVec2(GetWindowWidth() - GetStyle().ItemSpacing.x, ImGui::GetContentRegionAvail().y - 80));

												for (int i = 0; i < IM_ARRAYSIZE(settings::weapon::weapon_spawning::weapon_list); i++) {
													const char* weaponName = settings::weapon::weapon_spawning::weapon_list[i];

													// Vérifier si l'élément correspond au filtre
													if (strstr(weaponName, filterText) != nullptr) {
														bool isSelected = (settings::weapon::weapon_spawning::weapon_current == i);
														if (ImGui::Selectable(weaponName, isSelected)) {
															selectedItem = i;
														}
													}
												}

												ImGui::ListBoxFooter();

												if (selectedItem != -1) {
													settings::weapon::weapon_spawning::weapon_current = selectedItem;
												}

												ImGui::Separator();

												ImGui::Checkbox(E("Force In Hand"), &settings::weapon::weapon_spawning::in_hand);

												ImGui::Separator();

												if (ImGui::Button(E("Give Weapon"))) {
													settings::weapon::weapon_spawning::give = true;
												}
											} custom.end_child();

											break;
										
									}
								}EndChild();

								break;

							case 4:

								SetCursorPos(ImVec2(70, 13));
								BeginGroup();

								for (int i = 0; i < custom.vehicule_subtab.size(); ++i) {
									if (custom.sub_tab(custom.vehicule_subtab.at(i), custom.m_vehicule_subtab == i) && custom.m_vehicule_subtab != i)
										custom.m_vehicule_subtab = i, custom.m_anim = 0.f;

									if (i != custom.vehicule_subtab.size() - 1)
										SameLine();
								}

								EndGroup();

								SetCursorPos(ImVec2(65, 50));
								BeginChild(E("##vehiclle_child"), ImVec2(GetWindowWidth() - 80, GetWindowHeight() - 80)); {

									switch (custom.m_vehicule_subtab) {
									case 0:

										custom.begin_child("General", ImVec2(GetWindowWidth() / 2 - GetStyle().ItemSpacing.x / 2, GetWindowHeight())); {
											ImGui::Checkbox(E("Enabled"), &settings::vehicle::enabled);

											ImGui::Checkbox(E("Auto start engine"), &settings::vehicle::auto_start_engine);
											ImGui::Checkbox(E("Force open door"), &settings::vehicle::auto_open_car);
											ImGui::Checkbox(E("Skip animation"), &settings::vehicle::skip_animation);

											ImGui::Checkbox(E("Warp On Key"), &settings::vehicle::warp_on_key);
											if (settings::vehicle::warp_on_key) {
												ImGui::Hotkey(E("Warp Key :"), &settings::vehicle::key_warp, ImVec2(150, 20));
											}

											ImGui::Spacing();
											
											ImGui::Separator();

											ImGui::Text(E("Current Vehicle Option"));

											if (!settings::vehicle::on_car) {
												ImGui::Text(E("Not in a vehicle ! "));
											}
											else {
												ImGui::Checkbox(E("Godmode"), &settings::vehicle::godmod);
												ImGui::Checkbox(E("Invisible Car"), &settings::vehicle::invisible_car);
												ImGui::Checkbox(E("Car Speed"), &settings::vehicle::custom_speed);
												if (settings::vehicle::custom_speed) {
													ImGui::SliderInt(E("Speed Value"), &settings::vehicle::speed_int, 0, 500);
												}

												if (ImGui::Button(E("Repair"))) {
													settings::vehicle::repair = true;
												}

												if (ImGui::Button(E("Unlock Vehicle"))) {
													settings::vehicle::unlock = true;
												}

												ImGui::SameLine();

												if (ImGui::Button(E("Lock Vehicle"))) {
													settings::vehicle::lock = true;
												}
											}
										} custom.end_child();

										SameLine();

										custom.begin_child(E("Vehicle Custom"), ImVec2(GetWindowWidth() / 2 - GetStyle().ItemSpacing.x / 2, GetWindowHeight())); {
											if (!settings::vehicle::on_car) {
												ImGui::Text(E("Not in a vehicle ! "));
											}
											else {
												ImGui::SliderInt((E("Primary")), &settings::vehicle::primary_color, 0, 160, nullptr, ImGuiSliderFlags_AlwaysClamp || ImGuiSliderFlags_NoInput);

												ImGui::SliderInt((E("Secondary")), &settings::vehicle::secondary_color, 0, 160, nullptr, ImGuiSliderFlags_AlwaysClamp || ImGuiSliderFlags_NoInput);

												if (ImGui::Combo(E("Vehicle Mod"), &settings::vehicle::mod_idx, "Spoilers\0Front Bumper\0Rear Bumper\0Side Skirt\0Exhaust\0Frame\0Grille\0Hood\0Fender\0Right Fender\0Roof\0Engine\0Brakes\0Transmission\0Horns\0Suspension\0Armor\0"))
												{
													switch (settings::vehicle::mod_idx)
													{
													}
												}

												ImGui::SliderInt((E("Mod")), &settings::vehicle::add_idx, 0, 40, nullptr, ImGuiSliderFlags_AlwaysClamp || ImGuiSliderFlags_NoInput);

												ImGui::InputText(E("Plate Text"), settings::vehicle::plate_text, IM_ARRAYSIZE(settings::vehicle::plate_text));

												if (ImGui::Button(E("Update"))) {
													settings::vehicle::update = true;
												}

												ImGui::Separator();
											}
										} custom.end_child();

										break;
									case 1:

										custom.begin_child("Spawn option", ImVec2(GetWindowWidth() / 2 - GetStyle().ItemSpacing.x / 2, GetWindowHeight())); {
											if (ImGui::Button(E("Spawm Vehicle"))) {
												settings::vehicle::spawnvehicule = true;
											}
											ImGui::Checkbox(E("Spawn Maxed"), &settings::vehicle::spawn_maxed);
											ImGui::Checkbox(E("Spawn Networked"), &settings::vehicle::networked);



										} custom.end_child();

										SameLine();

										custom.begin_child(E("Vehicle Wanted"), ImVec2(GetWindowWidth() / 2 - GetStyle().ItemSpacing.x / 2, GetWindowHeight())); {
											ImGui::Checkbox(E("Sort by Model"), &settings::vehicle::vehicle_spawning::SortByType);
											if (settings::vehicle::vehicle_spawning::SortByType)
											{
												ImGui::Text("Filter Vehicle");
												ImGui::InputText(E("##ffff"), filterVehText, sizeof(filterVehText));

												int selectedItem = -1;

												ImGui::ListBoxHeader(E("##VehicleList"), ImVec2(GetWindowWidth()  - GetStyle().ItemSpacing.x, ImGui::GetContentRegionAvail().y - 50));

												for (int i = 0; i < IM_ARRAYSIZE(settings::vehicle::vehicle_spawning::allVehicleNames); i++) {
													const char* weaponName = settings::vehicle::vehicle_spawning::allVehicleNames[i];

													// Vérifier si l'élément correspond au filtre
													if (strstr(weaponName, filterVehText) != nullptr) {
														bool isSelected = (settings::vehicle::vehicle_spawning::Selected == i);
														if (ImGui::Selectable(weaponName, isSelected)) {
															selectedItem = i;
														}
													}
												}
												VehicleName = settings::vehicle::vehicle_spawning::allVehicleNames[settings::vehicle::vehicle_spawning::Selected];
												settings::vehicle::vehicle_spawning::VehicleToSpawn = rage::joaat(VehicleName);
												ImGui::ListBoxFooter();

												if (selectedItem != -1) {
													settings::vehicle::vehicle_spawning::Selected = selectedItem;
												}
											}
											else
											{
												ImGui::Combo(E("Vehicle Type"), &settings::vehicle::vehicle_spawning::TypesInt, settings::vehicle::vehicle_spawning::types, IM_ARRAYSIZE(settings::vehicle::vehicle_spawning::types));
												switch (settings::vehicle::vehicle_spawning::TypesInt)
												{
												case 0:

													ImGui::Combo(E("Vehicle Model"), &settings::vehicle::vehicle_spawning::SuperSportsPos, settings::vehicle::vehicle_spawning::SuperSports1, IM_ARRAYSIZE(settings::vehicle::vehicle_spawning::SuperSports1));
													VehicleName = settings::vehicle::vehicle_spawning::SuperSports1[settings::vehicle::vehicle_spawning::SuperSportsPos];
													settings::vehicle::vehicle_spawning::VehicleToSpawn = rage::joaat(VehicleName);
													break;

												case 1:

													ImGui::Combo(E("Vehicle Model"), &settings::vehicle::vehicle_spawning::BoatsPos, settings::vehicle::vehicle_spawning::Boats1, IM_ARRAYSIZE(settings::vehicle::vehicle_spawning::Boats1));
													VehicleName = settings::vehicle::vehicle_spawning::Boats1[settings::vehicle::vehicle_spawning::BoatsPos];
													settings::vehicle::vehicle_spawning::VehicleToSpawn = rage::joaat(VehicleName);
													break;
												case 2:

													ImGui::Combo(E("Vehicle Model"), &settings::vehicle::vehicle_spawning::ComercialPos, settings::vehicle::vehicle_spawning::Commercial1, IM_ARRAYSIZE(settings::vehicle::vehicle_spawning::Commercial1));
													VehicleName = settings::vehicle::vehicle_spawning::Commercial1[settings::vehicle::vehicle_spawning::ComercialPos];
													settings::vehicle::vehicle_spawning::VehicleToSpawn = rage::joaat(VehicleName);
													break;
												case 3:

													ImGui::Combo(E("Vehicle Model"), &settings::vehicle::vehicle_spawning::CompactsPos, settings::vehicle::vehicle_spawning::Compacts1, IM_ARRAYSIZE(settings::vehicle::vehicle_spawning::Compacts1));
													VehicleName = settings::vehicle::vehicle_spawning::Compacts1[settings::vehicle::vehicle_spawning::CompactsPos];
													settings::vehicle::vehicle_spawning::VehicleToSpawn = rage::joaat(VehicleName);
													break;
												case 4:

													ImGui::Combo(E("Vehicle Model"), &settings::vehicle::vehicle_spawning::CoupesPos, settings::vehicle::vehicle_spawning::Coupes1, IM_ARRAYSIZE(settings::vehicle::vehicle_spawning::Coupes1));
													VehicleName = settings::vehicle::vehicle_spawning::Coupes1[settings::vehicle::vehicle_spawning::CoupesPos];
													settings::vehicle::vehicle_spawning::VehicleToSpawn = rage::joaat(VehicleName);
													break;
												case 5:

													ImGui::Combo(E("Vehicle Model"), &settings::vehicle::vehicle_spawning::CyclesPos, settings::vehicle::vehicle_spawning::Cycles1, IM_ARRAYSIZE(settings::vehicle::vehicle_spawning::Cycles1));
													VehicleName = settings::vehicle::vehicle_spawning::Cycles1[settings::vehicle::vehicle_spawning::CyclesPos];
													settings::vehicle::vehicle_spawning::VehicleToSpawn = rage::joaat(VehicleName);
													break;
												case 6:

													ImGui::Combo(E("Vehicle Model"), &settings::vehicle::vehicle_spawning::EmergencyPos, settings::vehicle::vehicle_spawning::Emergency1, IM_ARRAYSIZE(settings::vehicle::vehicle_spawning::Emergency1));
													VehicleName = settings::vehicle::vehicle_spawning::Emergency1[settings::vehicle::vehicle_spawning::EmergencyPos];
													settings::vehicle::vehicle_spawning::VehicleToSpawn = rage::joaat(VehicleName);
													break;
												case 7:

													ImGui::Combo(E("Vehicle Model"), &settings::vehicle::vehicle_spawning::HelicoptersPos, settings::vehicle::vehicle_spawning::Helicopters1, IM_ARRAYSIZE(settings::vehicle::vehicle_spawning::Helicopters1));
													VehicleName = settings::vehicle::vehicle_spawning::Helicopters1[settings::vehicle::vehicle_spawning::HelicoptersPos];
													settings::vehicle::vehicle_spawning::VehicleToSpawn = rage::joaat(VehicleName);
													break;
												case 8:

													ImGui::Combo(E("Vehicle Model"), &settings::vehicle::vehicle_spawning::IndustrialPos, settings::vehicle::vehicle_spawning::Industrial1, IM_ARRAYSIZE(settings::vehicle::vehicle_spawning::Industrial1));
													VehicleName = settings::vehicle::vehicle_spawning::Industrial1[settings::vehicle::vehicle_spawning::IndustrialPos];
													settings::vehicle::vehicle_spawning::VehicleToSpawn = rage::joaat(VehicleName);
													break;
												case 9:

													ImGui::Combo(E("Vehicle Model"), &settings::vehicle::vehicle_spawning::MilitaryPos, settings::vehicle::vehicle_spawning::Military1, IM_ARRAYSIZE(settings::vehicle::vehicle_spawning::Military1));
													VehicleName = settings::vehicle::vehicle_spawning::Military1[settings::vehicle::vehicle_spawning::MilitaryPos];
													settings::vehicle::vehicle_spawning::VehicleToSpawn = rage::joaat(VehicleName);
													break;
												case 10:

													ImGui::Combo(E("Vehicle Model"), &settings::vehicle::vehicle_spawning::MotorcyclesPos, settings::vehicle::vehicle_spawning::Motorcycles1, IM_ARRAYSIZE(settings::vehicle::vehicle_spawning::Motorcycles1));
													VehicleName = settings::vehicle::vehicle_spawning::Motorcycles1[settings::vehicle::vehicle_spawning::MotorcyclesPos];
													settings::vehicle::vehicle_spawning::VehicleToSpawn = rage::joaat(VehicleName);
													break;
												case 11:

													ImGui::Combo(E("Vehicle Model"), &settings::vehicle::vehicle_spawning::MusclePos, settings::vehicle::vehicle_spawning::Muscle1, IM_ARRAYSIZE(settings::vehicle::vehicle_spawning::Muscle1));
													VehicleName = settings::vehicle::vehicle_spawning::Muscle1[settings::vehicle::vehicle_spawning::MusclePos];
													settings::vehicle::vehicle_spawning::VehicleToSpawn = rage::joaat(VehicleName);
													break;
												case 12:

													ImGui::Combo(E("Vehicle Model"), &settings::vehicle::vehicle_spawning::OffRoadPos, settings::vehicle::vehicle_spawning::OffRoad1, IM_ARRAYSIZE(settings::vehicle::vehicle_spawning::OffRoad1));
													VehicleName = settings::vehicle::vehicle_spawning::OffRoad1[settings::vehicle::vehicle_spawning::OffRoadPos];
													settings::vehicle::vehicle_spawning::VehicleToSpawn = rage::joaat(VehicleName);
													break;
												case 13:

													ImGui::Combo(E("Vehicle Model"), &settings::vehicle::vehicle_spawning::PlanesPos, settings::vehicle::vehicle_spawning::Planes1, IM_ARRAYSIZE(settings::vehicle::vehicle_spawning::Planes1));
													VehicleName = settings::vehicle::vehicle_spawning::Planes1[settings::vehicle::vehicle_spawning::PlanesPos];
													settings::vehicle::vehicle_spawning::VehicleToSpawn = rage::joaat(VehicleName);
													break;
												case 14:

													ImGui::Combo(E("Vehicle Model"), &settings::vehicle::vehicle_spawning::SedansPos, settings::vehicle::vehicle_spawning::Sedans1, IM_ARRAYSIZE(settings::vehicle::vehicle_spawning::Sedans1));
													VehicleName = settings::vehicle::vehicle_spawning::Sedans1[settings::vehicle::vehicle_spawning::SedansPos];
													settings::vehicle::vehicle_spawning::VehicleToSpawn = rage::joaat(VehicleName);
													break;
												case 15:

													ImGui::Combo(E("Vehicle Model"), &settings::vehicle::vehicle_spawning::ServicePos, settings::vehicle::vehicle_spawning::Service1, IM_ARRAYSIZE(settings::vehicle::vehicle_spawning::Service1));
													VehicleName = settings::vehicle::vehicle_spawning::Service1[settings::vehicle::vehicle_spawning::ServicePos];
													settings::vehicle::vehicle_spawning::VehicleToSpawn = rage::joaat(VehicleName);
													break;
												case 16:

													ImGui::Combo(E("Vehicle Model"), &settings::vehicle::vehicle_spawning::AfterHours, settings::vehicle::vehicle_spawning::AfterHours1, IM_ARRAYSIZE(settings::vehicle::vehicle_spawning::AfterHours1));
													VehicleName = settings::vehicle::vehicle_spawning::AfterHours1[settings::vehicle::vehicle_spawning::AfterHours];
													settings::vehicle::vehicle_spawning::VehicleToSpawn = rage::joaat(VehicleName);
													break;
												case 17:

													ImGui::Combo(E("Vehicle Model"), &settings::vehicle::vehicle_spawning::dcasino, settings::vehicle::vehicle_spawning::dcasino1, IM_ARRAYSIZE(settings::vehicle::vehicle_spawning::dcasino1));
													VehicleName = settings::vehicle::vehicle_spawning::dcasino1[settings::vehicle::vehicle_spawning::dcasino];
													settings::vehicle::vehicle_spawning::VehicleToSpawn = rage::joaat(VehicleName);
													break;
												case 18:

													ImGui::Combo(E("Vehicle Model"), &settings::vehicle::vehicle_spawning::arenawar, settings::vehicle::vehicle_spawning::arenawar1, IM_ARRAYSIZE(settings::vehicle::vehicle_spawning::arenawar1));
													VehicleName = settings::vehicle::vehicle_spawning::arenawar1[settings::vehicle::vehicle_spawning::arenawar];
													settings::vehicle::vehicle_spawning::VehicleToSpawn = rage::joaat(VehicleName);
													break;
												case 19:

													ImGui::Combo(E("Vehicle Model"), &settings::vehicle::vehicle_spawning::DoomsdayPos, settings::vehicle::vehicle_spawning::Doomsday1, IM_ARRAYSIZE(settings::vehicle::vehicle_spawning::Doomsday1));
													VehicleName = settings::vehicle::vehicle_spawning::Doomsday1[settings::vehicle::vehicle_spawning::DoomsdayPos];
													settings::vehicle::vehicle_spawning::VehicleToSpawn = rage::joaat(VehicleName);
													break;
												case 20:

													ImGui::Combo(E("Vehicle Model"), &settings::vehicle::vehicle_spawning::SportsPos, settings::vehicle::vehicle_spawning::Sports1, IM_ARRAYSIZE(settings::vehicle::vehicle_spawning::Sports1));
													VehicleName = settings::vehicle::vehicle_spawning::Sports1[settings::vehicle::vehicle_spawning::SportsPos];
													settings::vehicle::vehicle_spawning::VehicleToSpawn = rage::joaat(VehicleName);
													break;
												case 21:

													ImGui::Combo(E("Vehicle Model"), &settings::vehicle::vehicle_spawning::SportsClassicPos, settings::vehicle::vehicle_spawning::SportsClassics1, IM_ARRAYSIZE(settings::vehicle::vehicle_spawning::SportsClassics1));
													VehicleName = settings::vehicle::vehicle_spawning::SportsClassics1[settings::vehicle::vehicle_spawning::SportsClassicPos];
													settings::vehicle::vehicle_spawning::VehicleToSpawn = rage::joaat(VehicleName);
													break;
												case 23:

													ImGui::Combo(E("Vehicle Model"), &settings::vehicle::vehicle_spawning::SuperPos, settings::vehicle::vehicle_spawning::Super1, IM_ARRAYSIZE(settings::vehicle::vehicle_spawning::Super1));
													VehicleName = settings::vehicle::vehicle_spawning::Super1[settings::vehicle::vehicle_spawning::SuperPos];
													settings::vehicle::vehicle_spawning::VehicleToSpawn = rage::joaat(VehicleName);
													break;
												case 24:

													ImGui::Combo(E("Vehicle Model"), &settings::vehicle::vehicle_spawning::SUVPos, settings::vehicle::vehicle_spawning::SUVs1, IM_ARRAYSIZE(settings::vehicle::vehicle_spawning::SUVs1));
													VehicleName = settings::vehicle::vehicle_spawning::SUVs1[settings::vehicle::vehicle_spawning::SUVPos];
													settings::vehicle::vehicle_spawning::VehicleToSpawn = rage::joaat(VehicleName);
													break;
												case 25:

													ImGui::Combo(E("Vehicle Model"), &settings::vehicle::vehicle_spawning::TrailerPos, settings::vehicle::vehicle_spawning::Trailer1, IM_ARRAYSIZE(settings::vehicle::vehicle_spawning::Trailer1));
													VehicleName = settings::vehicle::vehicle_spawning::Trailer1[settings::vehicle::vehicle_spawning::TrailerPos];
													settings::vehicle::vehicle_spawning::VehicleToSpawn = rage::joaat(VehicleName);
													break;
												case 26:

													ImGui::Combo(E("Vehicle Model"), &settings::vehicle::vehicle_spawning::TrainsPos, settings::vehicle::vehicle_spawning::Trains1, IM_ARRAYSIZE(settings::vehicle::vehicle_spawning::Trains1));
													VehicleName = settings::vehicle::vehicle_spawning::Trains1[settings::vehicle::vehicle_spawning::TrainsPos];
													settings::vehicle::vehicle_spawning::VehicleToSpawn = rage::joaat(VehicleName);
													break;
												case 27:

													ImGui::Combo(E("Vehicle Model"), &settings::vehicle::vehicle_spawning::UtilityPos, settings::vehicle::vehicle_spawning::Utility1, IM_ARRAYSIZE(settings::vehicle::vehicle_spawning::Utility1));
													VehicleName = settings::vehicle::vehicle_spawning::Utility1[settings::vehicle::vehicle_spawning::UtilityPos];
													settings::vehicle::vehicle_spawning::VehicleToSpawn = rage::joaat(VehicleName);
													break;
												case 28:

													ImGui::Combo(E("Vehicle Model"), &settings::vehicle::vehicle_spawning::VansPos, settings::vehicle::vehicle_spawning::Vans1, IM_ARRAYSIZE(settings::vehicle::vehicle_spawning::Vans1));
													VehicleName = settings::vehicle::vehicle_spawning::Vans1[settings::vehicle::vehicle_spawning::VansPos];
													settings::vehicle::vehicle_spawning::VehicleToSpawn = rage::joaat(VehicleName);
													break;
												case 29:

													ImGui::Combo(E("Vehicle Model"), &settings::vehicle::vehicle_spawning::IMPORTEXPORT, settings::vehicle::vehicle_spawning::IMPORTEXPORT1, IM_ARRAYSIZE(settings::vehicle::vehicle_spawning::IMPORTEXPORT1));
													VehicleName = settings::vehicle::vehicle_spawning::IMPORTEXPORT1[settings::vehicle::vehicle_spawning::IMPORTEXPORT];
													settings::vehicle::vehicle_spawning::VehicleToSpawn = rage::joaat(VehicleName);
													break;
												}
											}






										} custom.end_child();

										break;

									}
								}EndChild();

								break;
							}

							SetCursorPosY(0);
							custom.tab_area(E("##tab_area"), ImVec2(50, size.y), []() {
								for (int i = 0; i < custom.tabs.size(); ++i)
									if (custom.tab(custom.tabs_icons.at(i), custom.tabs.at(i), custom.m_tab == i) && custom.m_tab != i)
										custom.m_tab = i, custom.m_anim = 0.f;
								});
							auto draww = ImGui::GetForegroundDrawList();

							draww->AddImage(logo, pos + ImVec2(17, 15), pos + ImVec2(37, 35), ImVec2(0, 0), ImVec2(1, 1), ImColor(1.f, 1.f, 1.f, 1.f));

						//	draw->AddRectFilled(pos + ImVec2(0, size.y - 20), pos + size, ImColor(15, 14, 21), style.WindowRounding, ImDrawFlags_RoundCornersBottom);
					//		draw->AddText(pos + ImVec2(5, size.y - 18), GetColorU32(ImGuiCol_Text), E("alprazolam.fun - internal for fivem"));
						//	draw->AddText(pos + ImVec2(size.x - CalcTextSize(user_name.c_str()).x - 5, size.y - 18), GetColorU32(ImGuiCol_Text), user_name.c_str());
						} ImGui::End();
						if (settings::visuals::Preview && custom.m_tab == 1 && custom.m_visuals_subtab == 0) {
							PushStyleVar(ImGuiStyleVar_WindowMinSize, { 300,430 * 1.2 });

							ImGui::SetNextWindowSize({300,430 * 1.2});
							ImGui::SetNextWindowPos({ WindPos.x + 10 ,  WindPos.y});
							ImGui::Begin(E("Preview Windows"), NULL, windows_flags); {
								auto window = GetCurrentWindow();
								auto draw = window->DrawList;
								auto pos = window->Pos;
								auto size = window->Size;
								auto style = GetStyle();

								custom.m_anim = ImLerp(custom.m_anim, 1.f, 0.03f);
								ImVec2 CursorPos = ImGui::GetWindowPos();

								ImVec2 Ped_Location = ImVec2(CursorPos.x + ImGui::GetWindowSize().x / 2, CursorPos.y + 265);
								float Height = 300;
								float Width = (Height / 2);
								float CornerSize = (Width) / 4.f;
								if(settings::visuals::box_esp)
								ImGui::GetWindowDrawList()->AddRect(ImVec2(Ped_Location.x - Width / 2, Ped_Location.y - Height / 2), ImVec2(Ped_Location.x + Width / 2, Ped_Location.y + Height / 2), settings::visuals::box_color,settings::visuals::box_rounding);

								ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(CursorPos.x, CursorPos.y), ImVec2(CursorPos.x + ImGui::GetWindowSize().x, CursorPos.y + 50), ImColor(0,0,0,255) );
								ImGui::GetWindowDrawList()->AddText( ImVec2(CursorPos.x + ImGui::GetWindowSize().x / 2 - (ImGui::CalcTextSize("Preview").x / 2), CursorPos.y + 35), ImColor(255, 255, 255, 255), "Preview");


								// Récupération de la position de la souris
								ImVec2 mousePos = ImGui::GetMousePos() - window->Pos;

								// Text Drag
								{	if (settings::visuals::player_name) {
									ImGui::SetCursorPos({ playerPos.x - (ImGui::CalcTextSize("Name").x / 2) ,playerPos.y });
									ImGui::Text("Name");
								
										if (ImGui::IsMouseDragging(0) && ImGui::IsItemHovered() && !isDraggingHealthBar) {

											if (playerPos.y < 250) {
												ImGui::SetCursorPos({ 150 - (ImGui::CalcTextSize("Name").x / 2),100 });

												ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 100));

												ImGui::Text("Name");
												ImGui::PopStyleColor();
											}
											else {
												if (healthBarPosition.y == 265 + 155)
												{
													ImGui::SetCursorPos({ 150 - (ImGui::CalcTextSize("Name").x / 2),435 });

												}
												else
												{
													ImGui::SetCursorPos({ 150 - (ImGui::CalcTextSize("Name").x / 2),420 });

												}

												ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 100));

												ImGui::Text("Name");
												ImGui::PopStyleColor();
											}

											isDraggingText = true;
										}
									}
									// Si le bouton de la souris est enfoncé, le texte est en cours de glissement
							
										if (!ImGui::IsMouseDown(0)) {
											if (isDraggingText) {
												if (playerPos.y < 250) {
													playerPos = { 150,100 };



												}
												else {
													if (healthBarPosition.y == 265 + 155)
													{
														playerPos = { 150,435 };

													}
													else
													{
														playerPos = { 150,420 };

													}

												}
											}
											isDraggingText = false;
										}

										if (playerPos.y > 250) {
											if (healthBarPosition.y == 265 + 155)
											{
												playerPos = { 150,435 };

											}
											else
											{
												playerPos = { 150,420 };

											}

										}
								

									// Si le bouton de la souris est relâché, le glissement du texte s'arrête
							
							
							

									
									// Si le texte est en cours de glissement, mettez à jour sa position
									if (isDraggingText) {
										playerPos = mousePos;
									}
								}
								// Health Drag
								{	
									if (settings::visuals::health_bar) {
								
									ImGui::SetCursorPos(healthBarPosition);

									ImGui::ProgressBar(health / 100.0f, healthBarSize);
									}
									// Récupération de la position de la souris


									// Si le bouton de la souris est enfoncé, commencez à glisser la barre de santé
									if (ImGui::IsMouseDragging(0) && ImGui::IsItemHovered() && !isDraggingText) {
								
										isDraggingHealthBar = true;
									}

									// Si le bouton de la souris est relâché, arrêtez de glisser la barre de santé
									if (!ImGui::IsMouseDown(0)) {
										if (isDraggingHealthBar) {
											if (healthBarPosition.y > CursorPos.y + 250) {
												healthBarSize = ImVec2(150, 5); // Taille de la barre de santé
												healthBarPosition.x = 75;

												healthBarPosition.y = 265 + 155;
												settings::visuals::healthbar_type = 2;
											}
											else {
												healthBarSize = ImVec2(5, 300); // Taille de la barre de santé
												healthBarPosition.y = 115;


											}
											if (healthBarSize.x == 5) {
												if (healthBarPosition.x < ImGui::GetWindowSize().x / 2) {

													settings::visuals::healthbar_type = 1;

													healthBarPosition.x = 65;


												}
												else {
													settings::visuals::healthbar_type = 0;

													healthBarPosition.x = 230;


												}
											}
									
										}
										isDraggingHealthBar = false;
									}
									if (isDraggingHealthBar) {
										healthBarSize = ImVec2(
											healthBarSize.x + (targetSize.x - healthBarSize.x) * sizeChangeSpeed,
											healthBarSize.y + (targetSize.y - healthBarSize.y) * sizeChangeSpeed
										);
										if (healthBarPosition.y >  280) {
											targetSize = ImVec2(150, 5); // New size when released

										}
										else {
											targetSize = ImVec2(5, 300); // New size when released




										}

										ImVec2 targetPosition = ImVec2(mousePos.x - healthBarSize.x / 2, mousePos.y - healthBarSize.y / 2);
										healthBarPosition = ImVec2(
											healthBarPosition.x + (targetPosition.x - healthBarPosition.x) / healthBarSmoothness,
											healthBarPosition.y + (targetPosition.y - healthBarPosition.y) / healthBarSmoothness
										);
							
									}
								}
				


							}
							ImGui::End();
							PopStyleVar();

						}
			
						PopStyleVar(2);
						ImGui::RenderNotifications();

					}
					else {
						//KeyAuthApp.ban(E("Don't try to crack my loader"));
					//	exit(3);
					}
				}
				else {
				//	KeyAuthApp.ban(E("Don't try to crack my loader"));
				//	exit(3);
				}
			}
		}
	}
} 