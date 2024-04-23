#pragma once


#include "../classes/classes.hpp"
#include "../settings.hpp"

#include <src/fivem/native/invoker.hpp>

static float noclipspeed = 1.00001f;
static bool speed = false;
static bool nogravity = true;


namespace noclip {

	void noclip(void) {

		if (settings::self::noclip) {

			hk_World* World = (hk_World*)*(uint64_t*)(fivem::World);
			if (!World)
				return;

			hk_Ped* LocalPlayer = World->LocalPlayer();
			if (!LocalPlayer)
				return;

			hk_ObjectNavigationPed* Nav = LocalPlayer->ObjectNavigation();
			if (!Nav)
				return;

			Vector3 ActualPos = LocalPlayer->GetCoordinate();

			if (LocalPlayer->IsInAVehicule() == true) {
				return;
			}
			if (LocalPlayer->GetHealth() < 100)
				return;

			if (SAFE_CALL(GetAsyncKeyState)(VK_LSHIFT))
				speed = true;
			else
				speed = false;

			if (speed)
			{
				noclipspeed = 1.0f;
			}
			else
			{
				noclipspeed = 0.1f;

			}


			Nav->SetRotation(Vector4(0, 0, 0, 0));


		

			if (SAFE_CALL(GetAsyncKeyState)(settings::self::hotkey_forward) & 0x8000)
			{
				LocalPlayer->SetVelocity();

				DWORD64 addr = fivem::GetCamera();
				Vector3 TPSangles = *(Vector3*)(addr + 0x40);
				if (TPSangles == Vector3(0, 0, 0))
				{
					TPSangles = *(Vector3*)(addr + 0x40);
				}
				Vector3 newpos = ActualPos;
				newpos.x += (TPSangles.x * noclipspeed);
				newpos.y += (TPSangles.y * noclipspeed);
				newpos.z += (TPSangles.z * noclipspeed);
				LocalPlayer->SetCoordinate(newpos);
				Nav->SetCoordinate(newpos);
			}

			if (SAFE_CALL(GetAsyncKeyState)(settings::self::hotkey_backward) & 0x8000)
			{
				LocalPlayer->SetVelocity();

				DWORD64 addr = fivem::GetCamera();
				Vector3 TPSangles = *(Vector3*)(addr + 0x40);
				if (TPSangles == Vector3(0, 0, 0))
				{
					TPSangles = *(Vector3*)(addr + 0x40);
				}
				Vector3 newpos = ActualPos;
				newpos.x -= (TPSangles.x * noclipspeed);
				newpos.y -= (TPSangles.y * noclipspeed);
				newpos.z -= (TPSangles.z * noclipspeed);
				LocalPlayer->SetCoordinate(newpos);
				Nav->SetCoordinate(newpos);
			}

			if (SAFE_CALL(GetAsyncKeyState)(settings::self::hotkey_left) & 0x8000)
			{
				LocalPlayer->SetVelocity();

				DWORD64 addr = fivem::GetCamera();
				Vector3 TPSangles = *(Vector3*)(addr + 0x40);
				if (TPSangles == Vector3(0, 0, 0))
				{
					TPSangles = *(Vector3*)(addr + 0x40);
				}
				Vector3 newpos = ActualPos;
				newpos.x -= (TPSangles.y * noclipspeed);
				newpos.y += (TPSangles.x * noclipspeed);
				newpos.z += (TPSangles.z * noclipspeed);
				LocalPlayer->SetCoordinate(newpos);
				Nav->SetCoordinate(newpos);
			}

			if (SAFE_CALL(GetAsyncKeyState)(settings::self::hotkey_right) & 0x8000)
			{
				LocalPlayer->SetVelocity();

				DWORD64 addr = fivem::GetCamera();
				Vector3 TPSangles = *(Vector3*)(addr + 0x40);
				if (TPSangles == Vector3(0, 0, 0))
				{
					TPSangles = *(Vector3*)(addr + 0x40);
				}
				Vector3 newpos = ActualPos;
				newpos.x += (TPSangles.y * noclipspeed);
				newpos.y -= (TPSangles.x * noclipspeed);
				newpos.z -= (TPSangles.z * noclipspeed);
				LocalPlayer->SetCoordinate(newpos);
				Nav->SetCoordinate(newpos);
			}

			//	ENTITY::SET_ENTITY_COLLISION(local_player, false, false);

		}

	}
}