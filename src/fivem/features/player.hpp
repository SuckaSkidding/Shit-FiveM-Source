#pragma once

#include "../classes/classes.hpp"
#include "../settings.hpp"
#include "../native/invoker.hpp"

namespace player {

	void self(void) {

		if (settings::self::enabled) {

			Player local_player = PLAYER::PLAYER_PED_ID();

			if (settings::self::godmode) {

				ENTITY::SET_ENTITY_INVINCIBLE(local_player, true);

			}
			else {

				ENTITY::SET_ENTITY_INVINCIBLE(local_player, false);

			}

			if (settings::self::invisible) {

				ENTITY::SET_ENTITY_VISIBLE(local_player, false);

			}
			else {

				ENTITY::SET_ENTITY_VISIBLE(local_player, true);

			}

			if (settings::self::no_hs) {

				PED::SET_PED_SUFFERS_CRITICAL_HITS(local_player, false);

			}
			else {

				PED::SET_PED_SUFFERS_CRITICAL_HITS(local_player, true);

			}

			if (settings::self::no_ragdoll) {

				PED::SET_PED_CAN_RAGDOLL(local_player, false);

			}
			else {

				PED::SET_PED_CAN_RAGDOLL(local_player, true);

			}

			if (settings::self::never_wanted) {

				PLAYER::SET_PLAYER_WANTED_LEVEL(local_player, 0, false);
				PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(local_player, false);

			}

			if (settings::self::desync) {

				if (PED::IS_PED_DEAD_OR_DYING(local_player, 1)) {

				}
				else {

					if (SAFE_CALL(GetAsyncKeyState)(0x45) < 0) {



					}
					else {

						auto v1 = rand() % 300 + 61;

						ENTITY::SET_ENTITY_ROTATION(local_player, 0, 0, v1, 1, true);

					}
				}
			}

			if (settings::self::infinite_stamina) {

				PLAYER::RESET_PLAYER_STAMINA(local_player);

			}

			if (settings::self::give_health) {

				ENTITY::SET_ENTITY_HEALTH(local_player, settings::self::give_health_amnt + 100);

				settings::self::give_health = false;

			}

			if (settings::self::give_armor) {

				PED::ADD_ARMOUR_TO_PED(local_player, settings::self::give_armor_amnt);

				settings::self::give_armor = false;

			}


			if (settings::self::revive) {

				PED::RESURRECT_PED(local_player);

				settings::self::revive = false;

			}


			if (settings::self::teleport_to_waypoint) {

				int WaypointHandle = HUD::GET_FIRST_BLIP_INFO_ID(8);

				if (HUD::DOES_BLIP_EXIST(WaypointHandle))
				{
					PVector3 waypoint1 = HUD::GET_BLIP_COORDS(WaypointHandle);

					PED::SET_PED_COORDS_KEEP_VEHICLE(local_player, waypoint1.x, waypoint1.y, waypoint1.z + 1);

				}
				settings::self::teleport_to_waypoint = false;
			}
		}
	}
}
