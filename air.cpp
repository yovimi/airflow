#include "air.h"
#include <format>

void* original_dll_main = nullptr;

BOOL __stdcall hk_dll_main(HMODULE mod, DWORD res, LPVOID reserve)
{
    printf(sk("(t.me/yowablog) hello from dllmain =)"));

    *reinterpret_cast<uintptr_t*>(window_handle) = reinterpret_cast<uintptr_t>(FindWindowW((L"Valve001"), NULL));
    memcpy((void*)(username), sk("varya <3"), sizeof(sk("varya <3")));
    *reinterpret_cast<int*>(username_lenght) = sizeof(sk("varya <3")) - 1;

    ((void(*)())(setup_funcs))();

    return 1;
}

airflow_t::airflow_t(HMODULE mod)
{
    AllocConsole();
    freopen_s(reinterpret_cast<FILE**>(stdin), "CONIN$", "r", stdin);
    freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);
    SetConsoleTitleA(sk("=("));
    HRSRC res = FindResourceA(mod, (LPCSTR)0x65, "GOVNO");
    HGLOBAL load = LoadResource(mod, res);
    size = SizeofResource(mod, res);
    resource = reinterpret_cast<uint32_t>(LockResource(load));
}

void airflow_t::relocate()
{
    printf(sk("(t.me/yowablog) relocate.....\n"));
    base = cheat_base; VirtualAlloc((LPVOID)cheat_base, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    memcpy(reinterpret_cast<void*>(base), reinterpret_cast<void*>(resource), size);
}

void airflow_t::fix_imports()
{
    printf(sk("(t.me/yowablog) relocate imports.....\n"));
    for (const auto& imp : g_imports)
    {
        *reinterpret_cast<uintptr_t*>(base + imp.offset) = reinterpret_cast<uintptr_t>(GetProcAddress(LoadLibraryA(imp.mod.c_str()), imp.func.c_str()));
    }
}

void airflow_t::setup_hooks()
{
    printf(sk("(t.me/yowablog) setup hooks.....\n"));

    if (MH_Initialize() != MH_OK)
        printf(sk("(-_-) failed init hook system!\n"));

    if (MH_CreateHook(reinterpret_cast<void*>(dllmain), hk_dll_main, &original_dll_main) != MH_OK)
        printf(sk("(-_-) failed hook -> dllmain!\n"));

    if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
        printf(sk("(-_-) failed enable hooks!\n"));
}

void airflow_t::patches()
{

}

void airflow_t::entry()
{
    printf(sk("call shit!\n"));
    LPVOID auth_token = VirtualAlloc(0, 0x1000, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    memcpy(auth_token, "slavaukraineslavaukraineslavaukraineslavaukraineslavaukraine97b", sizeof("slavaukraineslavaukraineslavaukraineslavaukraineslavaukraine97b"));
    printf(sk("1!\n"));
    ((void(_stdcall*)(LPVOID, DWORD, LPVOID))(entrypoint))(reinterpret_cast<HMODULE>(cheat_base), 1, auth_token);
}

void core(HMODULE mod)
{
     airflow_t* cheat = new airflow_t(mod);

     cheat->relocate();
     cheat->fix_imports();
     cheat->patches();
     cheat->setup_hooks();
     while (GetModuleHandleA(sk("serverbrowser.dll")) == 0);
     cheat->entry();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)core, hModule, 0, 0);
    }

    return 1;
}

