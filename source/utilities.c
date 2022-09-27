#include "../header/utilities.h"

void swap_(line* xp, line* yp)
{
    line temp = *xp;
    *xp = *yp;
    *yp = temp;
}
