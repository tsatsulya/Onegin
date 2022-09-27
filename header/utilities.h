#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <errno.h>
#include <stdarg.h>

const int GLOBAL_DEBUG_MODE = 0; // TODO: what is it doing here? Consider making this macro

// TODO: f_cmon, (wo)maaaan, naming!!
typedef int (*cmp_func)( const void* A, const void* B );

typedef struct Buffer {
    char* buffer;
    int size;
} buffer; // TODO: looks like "string"

typedef struct Line {
    char* buffer;
    int length;
} line;


void swap_(line* xp, line* yp); // TODO: A bit misplaced, I think
// TODO: think if you can integrate your swap in sorting function,
//       to do this you need a more general version of this swap,
//       I suggest signature:

// void swap(void *dst, void *src, size_t size);