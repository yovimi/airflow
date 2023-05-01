#pragma once
#include <windows.h>
#include <string>
#include <vector>
#include "minhook/minhook.h"
#include <cstdint>
#include <intrin.h>
#include <iostream>
#include "utils.h"
#include "crypt.h"

enum type
{
	call = 0,
	jmp = 1
};

