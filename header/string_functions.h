#include "types.h"
#include <assert.h>
#include <stdio.h>
#include "utilities.h"

enum step {
    from_end = -1,
    from_begin = 1
};

int strings_spliting(char* full_line, string* array_of_lines) ;

int strcmp_reverse(string* i, string* j);
int strcmp_(string* i, string* j);

