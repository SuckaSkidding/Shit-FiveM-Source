#include <scroupthick.hpp>

#include <thread.hpp>
#include <fiber.hpp>
#include "src/fivem/classes/classes.hpp"
using script_thread_tick_t = uintptr_t(*)(game_thread* thread, int ops_to_execute);
script_thread_tick_t ptr_gta_script_thread_tick = nullptr;
script_thread_tick_t original_native_thread = nullptr;

uintptr_t hooked_native_thread(game_thread* this_ptr, int ops_to_execute) {
	Thread::Instance().CallT(this_ptr, ops_to_execute);//get this pointer and ops_to_execute


	//Log::Msg("[+] name: %s || id: %d || script hash: %llx || opsto_execute %llx", this_ptr->m_name, this_ptr->m_context.m_thread_id, this_ptr->m_context.m_script_hash, ops_to_execute);
	//return return_spoofer::spoof_call(jmp_rdx, original_native_thread, this_ptr, ops_to_execute);
	return original_native_thread(this_ptr, ops_to_execute);
}
void Hooks::Thread(UINT64 scrMeta) {
	Fiber::Instance().Call();
	BYTE scrIndex;

	if (fivem::is2944)
		scrIndex = 64 + 8 * 3;
	else if (fivem::FiveM_2802)
		scrIndex = 32 + 8 * 3;
	else if (fivem::is2612)
		scrIndex = 64 + 8 * 4;
	else if(fivem::is2189)
		scrIndex = 64 + 8 * 4;
	else
		scrIndex = 32 + 8 * 4;
	//SwapVtab Hook
	//Log::Msg("[+] scrMeta >> %llx", scrMeta);
	ptr_gta_script_thread_tick = (script_thread_tick_t)(scrMeta + scrIndex);
	//Log::Msg("[+] ptr_gta_script_thread_tick >> %llx", ptr_gta_script_thread_tick);
	original_native_thread = (script_thread_tick_t)(*(uint64_t*)ptr_gta_script_thread_tick);
	//Log::Msg("[+] original_native_thread >> %llx", original_native_thread);
	*(intptr_t*)ptr_gta_script_thread_tick = (intptr_t)&hooked_native_thread;
	//Log::Msg("[+] &hooked_native_thread >> %llx", &hooked_native_thread);
}
void Hooks::Initialize(UINT64 scrMeta) {
	//Log::Msg("[+] H000ks >> Initializing h000ks...");
	this->Thread(scrMeta);

}