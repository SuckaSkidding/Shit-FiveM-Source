#pragma once


#include "../classes/classes.hpp"
#include "../settings.hpp"
#include "../native/invoker.hpp"



namespace vehicle {

	void vehicle_modifications(void) {

		if (settings::vehicle::enabled) {

			auto player = PLAYER::PLAYER_PED_ID();
			auto trying_to_open_veicle = PED::GET_VEHICLE_PED_IS_TRYING_TO_ENTER(player);
			auto current_vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), true);



			if (settings::vehicle::godmod) {

				ENTITY::SET_ENTITY_INVINCIBLE(current_vehicle, true);
				ENTITY::SET_ENTITY_PROOFS(current_vehicle, 1, 1, 1, 1, 1, 1, 1, 1);
				VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(current_vehicle, 0);
				VEHICLE::SET_VEHICLE_WHEELS_CAN_BREAK(current_vehicle, 0);
				VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(current_vehicle, 0);
				VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(current_vehicle, false);
				VEHICLE::SET_VEHICLE_WHEELS_CAN_BREAK(current_vehicle, false);
				VEHICLE::SET_VEHICLE_HAS_STRONG_AXLES(current_vehicle, true);

			}

			if (settings::vehicle::auto_start_engine) {

				VEHICLE::SET_VEHICLE_ENGINE_ON(current_vehicle, true, true);

			}

			if (settings::vehicle::auto_open_car) {

				VEHICLE::SET_VEHICLE_DOORS_LOCKED(trying_to_open_veicle, 1);

			}

			if (settings::vehicle::skip_animation) {

				PED::SET_PED_INTO_VEHICLE(player, trying_to_open_veicle, -1);

			}

			if (settings::vehicle::explode_car) {

				VEHICLE::EXPLODE_VEHICLE(current_vehicle, false, true);

				settings::vehicle::explode_car = false;

			}


			if (PED::IS_PED_IN_ANY_VEHICLE(player, false)) {

				settings::vehicle::on_car = true;

			}
			else {

				settings::vehicle::on_car = false;

			}

			if (settings::vehicle::update) {

				VEHICLE::SET_VEHICLE_MOD(current_vehicle, settings::vehicle::mod_idx, settings::vehicle::add_idx, false);
				VEHICLE::SET_VEHICLE_COLOURS(current_vehicle, settings::vehicle::primary_color, settings::vehicle::secondary_color);
				VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(current_vehicle, settings::vehicle::plate_text);



				settings::vehicle::update = false;

			}

			if (settings::vehicle::custom_speed) {

				VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(current_vehicle, settings::vehicle::speed_int);

			}

			if (settings::vehicle::invisible_car) {

				ENTITY::SET_ENTITY_VISIBLE(current_vehicle, false);

			}
			else {

				ENTITY::SET_ENTITY_VISIBLE(current_vehicle, true);

			}
			
			if (settings::vehicle::repair) {

				//VEHICLE::SET_VEHICLE_FIXED(current_vehicle);

				VEHICLE::SET_VEHICLE_ENGINE_HEALTH(current_vehicle, 1000.0f);

				VEHICLE::SET_VEHICLE_TYRE_FIXED(current_vehicle, 0);
				VEHICLE::SET_VEHICLE_TYRE_FIXED(current_vehicle, 1);
				VEHICLE::SET_VEHICLE_TYRE_FIXED(current_vehicle, 4);
				VEHICLE::SET_VEHICLE_TYRE_FIXED(current_vehicle, 5);

				VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(current_vehicle);

				settings::vehicle::repair = false;

			}

			if (settings::vehicle::unlock) {

				VEHICLE::SET_VEHICLE_DOORS_LOCKED(current_vehicle, 1);

				settings::vehicle::unlock = false;
			}

			if (settings::vehicle::lock) {

				VEHICLE::SET_VEHICLE_DOORS_LOCKED(current_vehicle, 3);

				settings::vehicle::lock = false;
			}

		}

	}

}