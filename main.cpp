#include "includes.h"
//#include <VMProtectSDK.h>
#include "discord/Discord.h"
#include <xstring>

using namespace std;

Discord* g_Discord;



__forceinline void discord_main()
{
	g_Discord->Initialize();
	g_Discord->Update();
}

void CheckVersion(std::string version)
{

	Start();
	hk__();
	//discord_main();

}

void RUST_OnLoad(HINSTANCE hModule) {
	CheckVersion(xorstr_("4"));
}
bool DllMain(HMODULE hMod, std::uint32_t call_reason, void*) {
	if (call_reason != DLL_PROCESS_ATTACH)
		return false;
	const auto handle = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(RUST_OnLoad), hMod, 0, nullptr);
	if (handle != NULL)
		CloseHandle(handle);

	return true;
}
