#include "utilities.h"

void swap_(string* xp, string* yp)
{
    string temp = *xp;
    *xp = *yp;
    *yp = temp;
}
