#pragma once

#include <stdio.h>
#include "debug.h"
#include "types.h"


void swap_(string* xp, string* yp); // TODO: A bit misplaced, I think
// TODO: think if you can integrate your swap in sorting function,
//       to do this you need a more general version of this swap,
//       I suggest signature:

// void swap(void *dst, void *src, size_t size);