#include <RAGEhelper.hpp>
#include "src/fivem/classes/classes.hpp"
DWORD64 dwRegistrationTablePtr = 0;
extern PBYTE location;
rage::pgPtrCollection<GtaThread>* GetGtaThreadCollection()
{
	if (!fivem::dwThreadCollectionPtr) {


		DWORD64 dwAddressOfThreadCollection = fivem::dwThreadCollectionPtr;// *(DWORD*)(dwThreadCollectionPtr + 3) + 7;

		MODULEINFO g_MainModuleInfo = { 0 };
		if (!GetModuleInformation(GetCurrentProcess(), GetModuleHandle(0), &g_MainModuleInfo, sizeof(g_MainModuleInfo))) {
		}
		if (!dwAddressOfThreadCollection ||
			dwAddressOfThreadCollection < (DWORD64)g_MainModuleInfo.lpBaseOfDll ||
			dwAddressOfThreadCollection >(DWORD64) g_MainModuleInfo.lpBaseOfDll + g_MainModuleInfo.SizeOfImage
			) {
		}

		fivem::dwThreadCollectionPtr = dwAddressOfThreadCollection;

	}

	return (rage::pgPtrCollection<GtaThread>*) fivem::dwThreadCollectionPtr;
}

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

rage::scrThread* GetActiveThread()
{
	char* moduleTls = *(char**)__readgsqword(0x58);
	return *reinterpret_cast<rage::scrThread**>(get_tls() + fivem::activeThreadTlsOffset); //citizenMP sigs this offset. It's been the same for 3 versions. Not worth it.
}
//I won't even begin to claim that I know what the fuck is going on here. ~gir489


void SetActiveThread(rage::scrThread* thread)
{

	*reinterpret_cast<rage::scrThread**>(get_tls() + fivem::activeThreadTlsOffset) = thread;
}