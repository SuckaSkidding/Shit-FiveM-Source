#pragma once

#include "../hooks/hooks.hpp"

void cheat_init() {

	hooks::Initialize();

}

void cheat_unload() {

	hooks::Shutdown();

}