#pragma once
#include <includes.h>
#include <singeton.hpp>

#define PICKUP_MONEY_CASE 0xCE6FDD6B
#define MAIN_PERSISTENT 0x5700179C
#define STARTUP	0X41d6f794
using namespace std;





enum class thread_state_t : std::uint32_t
{
	idle,
	running,
	killed,
	unk_3,
	unk_4,
};

class thread_context_t
{
public:
	std::uint32_t m_thread_id;
	std::uint32_t m_script_hash; // + 4 (program id)
	thread_state_t m_state; // + 8
	std::uint32_t m_instruction_pointer; // 0x0C
	std::uint32_t m_frame_pointer;       // 0x10
	std::uint32_t m_stack_pointer;       // 0x14
	float m_timer_a;                     // 0x18
	float m_timer_b;                     // 0x1C
	float m_timer_c;                     // 0x20
	char m_padding1[0x2C];               // 0x24
	std::uint32_t m_stack_size;          // 0x50
	char m_padding2[0x54];               // 0x54
};
template<typename T = char*>
T get_tls()
{
	static auto tlsIndex = ([]()
		{
			auto base = (char*)GetModuleHandleA(NULL);
			auto moduleBase = (PIMAGE_DOS_HEADER)base;
			auto ntBase = (PIMAGE_NT_HEADERS)(base + moduleBase->e_lfanew);
			auto tlsBase = (PIMAGE_TLS_DIRECTORY)(base + ntBase->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].VirtualAddress);

			return reinterpret_cast<uint32_t*>(tlsBase->AddressOfIndex);
		})();

		auto tlsBase = (LPVOID*)__readgsqword(0x58);
		return (T)tlsBase[*tlsIndex];
}
class game_thread
{
public:
	virtual ~game_thread() = default;
	virtual thread_state_t reset(std::uint32_t script_hash, void* args, std::uint32_t arg_count) = 0;
	virtual thread_state_t run() = 0;
	virtual thread_state_t tick() = 0;
	virtual void kill() = 0;

	inline static game_thread*& GetActiveThread(UINT32 dwTlsOffset)
	{
		return *reinterpret_cast<game_thread**>(get_tls() + dwTlsOffset);
		//return *(game_thread**)(*reinterpret_cast<uintptr_t*>(__readgsqword(0x58)) + 0x848);
	}
	inline static void SetActiveThread(UINT32 dwTlsOffset, game_thread* thread)
	{
		*reinterpret_cast<game_thread**>(get_tls() + dwTlsOffset) = thread;
		//return *(game_thread**)(*reinterpret_cast<uintptr_t*>(__readgsqword(0x58)) + 0x848);
	}
public:
	thread_context_t m_context; // 0x08
	void* m_stack;              // 0xB0
	char m_padding[0x10];       // 0xB8
	const char* m_exit_message; // 0xC8
	char m_name[0x40];          // 0xD0
	void* m_handler;   // 0x110
	char m_padding2[0x28];      // 0x118
	std::uint8_t m_flag1;       // 0x140
	std::uint8_t m_flag2;       // 0x141
	char m_padding3[0x16];      // 0x142
};

class Thread : public Singleton<Thread>
{
private:

public:
	void CallT(game_thread* this_ptr, int ops_to_execute);
};