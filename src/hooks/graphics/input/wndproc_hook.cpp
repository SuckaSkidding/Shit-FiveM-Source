#include <Windows.h>
#include <thread>


#include "../../../../dependencies/imgui/imgui.h"
#include "../../../../dependencies/imgui/imgui_impl_win32.h"

#include "../../../menu/menu.hpp"

static BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam);

static HWND g_hWindow;
static WNDPROC g_oWndProc;
static LRESULT hkWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (!ImGui::GetCurrentContext()) {
        ImGui::CreateContext();
        ImGui_ImplWin32_Init(hWnd);
        ImGuiIO& io = ImGui::GetIO();
        io.IniFilename = io.LogFilename = nullptr;
    }

    LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam,
        LPARAM lParam);


    if (menu::show_menu) {

    	return ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam) == 0;

    }

    return CallWindowProc(g_oWndProc, hWnd, uMsg, wParam, lParam);
}

void HookInputAPI() {
    while (!g_hWindow) {
        EnumWindows(::EnumWindowsCallback,
            reinterpret_cast<LPARAM>(&g_hWindow));
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    g_oWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(
        g_hWindow, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(hkWndProc)));
}

void UnHookInputAPI() {
    if (g_oWndProc) {
        SetWindowLongPtr(g_hWindow, GWLP_WNDPROC,
            reinterpret_cast<LONG_PTR>(g_oWndProc));
    }
}

static BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam) {
    const auto isMainWindow = [handle]() {
        return GetWindow(handle, GW_OWNER) == nullptr &&
            IsWindowVisible(handle) && handle != GetConsoleWindow();
    };

    DWORD pID = 0;
    GetWindowThreadProcessId(handle, &pID);

    if (GetCurrentProcessId() != pID || !isMainWindow()) return TRUE;

    *reinterpret_cast<HWND*>(lParam) = handle;
    return FALSE;
}

HWND GetGameWindow() { return g_hWindow; }
