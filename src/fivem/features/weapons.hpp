#pragma once

#include "../classes/classes.hpp"
#include "../settings.hpp"
#include "../native/invoker.hpp"

Vector3 rot_to_directionnnn(Vector3* rot)
{
	float radiansZ = rot->z * 0.0174532924f;
	float radiansX = rot->x * 0.0174532924f;
	float num = abs((float)cos((double)radiansX));
	Vector3 dir = { 0,0,0 };
	dir.x = (float)((double)((float)(-(float)sin((double)radiansZ))) * (double)num);
	dir.y = (float)((double)((float)cos((double)radiansZ)) * (double)num);
	dir.z = (float)sin((double)radiansX);
	return dir;
}
namespace weapon {
	void weapon_modification(void) {
		if (settings::weapon::enabled) {
			hk_World* World = (hk_World*)*(uint64_t*)(fivem::World);
			if (!World)
				return;

			hk_Ped* LocalPlayer = World->LocalPlayer();
			if (!LocalPlayer)
				return;

			hk_WeaponManager* WeaponManager = LocalPlayer->WeaponManager();
			if (!WeaponManager)
				return;

			hk_WeaponInfo* WeaponInfo = WeaponManager->WeaponInfo();
			if (!WeaponInfo)
				return;
			auto player = PLAYER::PLAYER_PED_ID();

			if (settings::weapon::no_recoil) {
				WeaponInfo->SetRecoil(settings::weapon::recoil_value);
			}

			if (settings::weapon::no_spread) {
				WeaponInfo->SetSpread(settings::weapon::spread_value);
			}

			if (settings::weapon::no_reload) {
				WEAPON::REFILL_AMMO_INSTANTLY(player);
			}

			if (settings::weapon::damage_boost) {
				WeaponInfo->Damage_boost(settings::weapon::int_damage);
			}

			if (settings::weapon::infinite_range) {
				WeaponInfo->SetRange(settings::weapon::weapon_range);
			}
			if (settings::weapon::infite_ammo) {

				int max_ammo;
				if (WEAPON::IS_WEAPON_VALID(WeaponInfo->GetHash())) {
					WEAPON::GET_MAX_AMMO(player, WeaponInfo->GetHash(), &max_ammo);
					WEAPON::SET_PED_AMMO(player, WeaponInfo->GetHash(), 100);

				}

		/*		auto WeaponHash = WEAPON::GET_SELECTED_PED_WEAPON(player);

				WEAPON::SET_PED_AMMO(player, WeaponHash, settings::weapon::ammo_to_set);*/
			}

			if (settings::weapon::set_ammo) {
				auto WeaponHash = WEAPON::GET_SELECTED_PED_WEAPON(player);
				if (WEAPON::IS_WEAPON_VALID(WeaponHash))
				WEAPON::SET_PED_AMMO(player, WeaponHash, settings::weapon::ammo_to_set);

				//FixedAmmoCount->SetAmmo(settings::weapon::ammo_to_set);

				settings::weapon::set_ammo = false;
			}
			if (settings::weapon::infite_ammo || settings::weapon::set_ammo) {
				hk_AmmoInfo* AmmoInfo = WeaponInfo->AmmoInfo();
				if (!AmmoInfo)
					return;

				hk_AmmoCount* AmmoCount = AmmoInfo->AmmoCount();
				if (!AmmoCount)
					return;
				hk_FixedAmmoCount* FixedAmmoCount = AmmoCount->FixedAmmoCount();
				if (!FixedAmmoCount)
					return;

			
				if (settings::weapon::force_gun)
				{
					Entity EntityTarget;
					PVector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(0);
					Vector3 rott = Vector3(rot.x, rot.y, rot.z);
					Vector3 dir = rot_to_directionnnn(&rott);
					if (PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &EntityTarget))
					{
						if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
						{
							if (ENTITY::IS_ENTITY_A_PED(EntityTarget)
								&& PED::IS_PED_IN_ANY_VEHICLE(EntityTarget, 1)) {
								EntityTarget = PED::GET_VEHICLE_PED_IS_IN(EntityTarget, 0);
							}
							ENTITY::APPLY_FORCE_TO_ENTITY(EntityTarget, 1, dir.x * 100000.0f, dir.y * 100000.0f, dir.z * 100000.0f, 0.0f, 0.0f, 0.0f, 0, 0, 1, 1, 0, 1);
						}
					}
				}


			}
		}
	}

	void weapon_spawning(void) {
		if (settings::weapon::weapon_spawning::weapon_spawning) {
			if (settings::weapon::weapon_spawning::give) {
				switch (settings::weapon::weapon_spawning::weapon_current)
				{
				case 0: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x92A27487, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 1: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x958A4A8F, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 2: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x99B507EA, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 3: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xDD5DF8D9, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;

				case 4: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x1B06D571, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 5: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xBFE256D4, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 6: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x5EF9FEC4, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 7: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x22D8FE39, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;

				case 8: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x3656C8C1, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 9: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x99AEEB3B, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 10: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xBFD21232, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 11: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x88374054, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 12: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xD205520E, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 13: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x83839C4, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 14: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x47757124, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 15: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xDC4DB296, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 16: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xC1B3C3D1, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 17: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xCB96392F, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 18: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x97EA20B8, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 19: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x13532244, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 20: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x2BE6766B, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 21: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x78A97CD0, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;

				case 22: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xEFE7E2DF, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 23: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xA3D4D34, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 24: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xDB1AA450, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 25: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xBD248B55, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 26: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x1D073A89, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 27: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x555AF99A, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 28: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x7846A318, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 29: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xE284C527, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 30: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x9D61E50F, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 31: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xA89CB99E, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 32: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x3AABBBAA, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 33: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xEF951FBB, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 34: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x12E82D3D, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 35: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xBFEFFF6D, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 36: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x394F415C, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 37: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x83BF0278, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 38: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xFAD1F1C9, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 39: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xAF113F99, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 40: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xC0A3098D, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 41: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x969C3D67, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 42: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x7F229F94, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 43: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x84D6FAFD, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 44: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x624FE830, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 45: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x9D07F764, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 46: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x7FD62962, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 47: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xDBBD7280, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 48: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x61012683, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;

				case 49: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x5FC3C11, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 50: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xC472FE2, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 51: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xA914799, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 52: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xC734385A, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 53: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x6A6C02E0, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 54: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xB1CA77B1, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 55: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xA284510B, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 56: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x42BF8A85, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 57: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x7F7497E5, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 58: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x6D544C99, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;

				case 59: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x63AB0442, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 60: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x781FE4A, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 61: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x93E220BD, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 62: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xA0973D5E, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 63: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xFDBC8A50, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 64: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x497FACC3, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 65: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x24B17070, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 66: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x2C3731D9, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 67: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xAB564B93, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 68: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x787F0BB, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;

				case 69: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xBA45E8B8, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 70: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x23C9F95C, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;

				case 71: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x34A67B97, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 72: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x60EC506, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				case 73: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xFBAB5776, (int)999, (bool)false, (bool)settings::weapon::weapon_spawning::in_hand); break;
				}

				settings::weapon::weapon_spawning::give = false;
			}
		}
	}
}