#pragma warning(disable : 4530)
#define _CRT_SECURE_NO_WARNINGS

#define StrA
#define StrW

#define noauth
//#define disable

#include <stdint.h>
#include <Windows.h>
#include <psapi.h>
#include <d3d11.h>
#include <string>
#include <codecvt>
#include <locale>
#include <cstdint>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <emmintrin.h>
#include "winternl.h"
#include <vector>
#include <fstream>
#include "Cheat/Hooks/offsets.h"
#include "Utils/Math/crc32.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <signal.h>
#include <sstream>
#include <thread>
#include "Utils/xorstr.h"
#include <comdef.h>
#include "Cheat/Visuals/menu/imgui/imgui.h"
#include <Lmcons.h>
#include "Utils/Il2cpp/Memory.h"
#include "Utils/Il2cpp/Dumper.h"
#include "Utils/Math/structs.h"
#include "Utils/Math/vector.h"
#include "Utils/Math/math.h"
#include "Utils/vars.h"
#include "Utils/Math/weapons.h"
#include "Utils/class.h"
#include "Utils/Il2cpp/il2cpp.h"
#include "Cheat/Game/game.h"
#include "Cheat/Misc/f_object.h"
#pragma comment(lib, "d3d11.lib")
#include "Cheat/Visuals/menu/imgui/imgui_freetype.h"
#include "Cheat/Visuals/menu/imgui/imgui_impl_win32.h"
#include "Cheat/Visuals/menu/imgui/imgui_impl_dx11.h"
#include "Cheat/Visuals/menu/imgui/imgui_internal.h"
#include "Utils/sounds.h"
#include <format>
#include <filesystem>
#include <fstream>
#include <ostream>

#pragma comment(lib, "urlmon.lib")
ImFont* Iconsis_Font;
ImFont* diamond;
ImFont* IconFont;
ImFont* worldico;

ImFont* Iconsis_Font_2;
ImFont* fIcons, * fMain, * fSmall, * fSmallIcons, * fName, * flogs, * fIcons2, * fWeapons1, * Cuniaabyser, * Cuniaabyser12, * Cuniaabyser1, * Verdanaboltbyser, * Verdanabyser, * Custom, * indShandow;

static ImVec2 menu_size = ImVec2(690, 500);
static ImVec2 prev_size = ImVec2(200, 350);
HWND game_window;
HRESULT(*present_original)(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags) = nullptr;
HRESULT(*resize_original)(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags) = nullptr;
ID3D11Device* device = nullptr;
ID3D11DeviceContext* immediate_context = nullptr;
ID3D11RenderTargetView* render_target_view = nullptr;
Vector2 screen_size = { 0, 0 };
D3D11_VIEWPORT viewport;

inline ImDrawList* DrawList;
float size_name = 15.f;
#include "Cheat/Config/SimpleIni.h"
#include "Cheat/Config/Config.h"
#include "Cheat/Visuals/menu/imgui/Shadows.h"
#include "Cheat/Render.h"
#include "Cheat/Visuals/logger.hpp"
#include "Cheat/Hooks/minhook/include/MinHook.h"
#include "Cheat/Visuals/logsystem.h"
#include "Cheat/Misc/aim.h"
#include "Cheat/Misc/nanoaim.hpp"
#include "Cheat/Misc/misc.h"
#include "Cheat/Misc/other.hpp"
#include "Cheat/Visuals/esp.h"
#include "Cheat/Game/gamethread.h"
#include "Cheat/Hooks/hooks.h"
#include "Cheat/config.cpp"
#include "Cheat/Game/entities.h"
#include "Cheat/Visuals/Rendering.h"

#include "Cheat/Visuals/menu/menu.h"
#include "Startup.h"
#include "Utils/Il2cpp/lazy_importer.hpp"
#include "Utils/Internet.h"
#pragma comment(lib, "ntdll.lib")
#pragma comment(lib, "winmm.lib")