#pragma once
#include <stdarg.h>
#include <stdio.h>

#define GLOBAL_DEBUG_MODE 0

void debug_msg(int mode, const char* format, ...);