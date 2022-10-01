#pragma once

#include <stdio.h>
#include "debug.h"
#include "types.h"


enum step {
    from_end = -1,
    from_begin = 1
};

void bubble_sort(string* array, int line_count);

void qsort_(void* base, size_t size, size_t width, cmp_func cmp_);
void swap_(string* xp, string* yp);