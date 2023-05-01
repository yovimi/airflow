#pragma once
#include "includes.h"
#include "imports.h"

constexpr std::uintptr_t cheat_base = 0x35200000;
constexpr std::uintptr_t cheat_size = 0x00580000;
constexpr std::uintptr_t entrypoint = cheat_base + 0x0022178B;
constexpr std::uintptr_t dllmain = cheat_base + 0x0019F180;
constexpr std::uintptr_t setup_hooks = cheat_base + 0x00177460;
constexpr std::uintptr_t setup_funcs = cheat_base + 0x00197730;
constexpr std::uintptr_t init_cheat = cheat_base + 0x0019EC00;
constexpr std::uintptr_t window_handle = cheat_base + 0x003B14A8;
constexpr std::uintptr_t username = cheat_base + 0x003B1558;
constexpr std::uintptr_t username_lenght = cheat_base + 0x003B1568;

int recv_counter = 0;

class airflow_t
{
	std::uintptr_t base;
	std::uintptr_t size;
	std::uintptr_t resource;
public:
	airflow_t(HMODULE mod);

	void relocate();
	void fix_imports();
	void patches();
	void setup_hooks();
	void entry();
};