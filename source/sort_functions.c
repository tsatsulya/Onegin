#include "sort_functions.h"
#include "string_functions.h"
#include "stdbool.h"

void bubble_sort(string* array, int line_count) {

    bool is_sorted;

    for (int i = 0; i < line_count - 1; ++i) {
        
        is_sorted = true;
        
        for (int j = 0; j < line_count - i - 1; ++j) {

            if (strcmp_( (array + j), (array + j + 1)) > 0) {
                
                is_sorted = false;

                swap_(array + j, array + j + 1);

            }
        }
        if (is_sorted) break;
    }
}

void swap_(string* xp, string* yp) {
    string temp = *xp;
    *xp = *yp;
    *yp = temp;
}


void qsort_(void* base, size_t size, size_t width, cmp_func cmp_) {
    
    string* i = (string*)base;
    string* start = i;
    string* end = start+size-1;
    string* j = start+size-1;

    if (size <= 1) return;

    if (size == 2) {
        int res = cmp_(i, j);
        if (res > 0) 
            swap_(i, j);
        return;
    }
    
    debug_msg(3, ".................>SIZE : %d\n\n", (int)size);
    // if (DEBUG) printf(".................>SIZE : %d\n\n", (int)size);
    debug_msg(3, " -> BEGIN: %s   END: %s\n\n", start->buffer, (start+size-1)->buffer);
    // if (DEBUG) printf(" -> BEGIN: %s   END: %s\n\n", start->buffer, (start+size-1)->buffer);

    j++;
    while( true ) {
        do { 
            i++;
            if (i>=end) break;
            debug_msg(3, "i = { %s }\n\n", i->buffer);
            // if (DEBUG) printf("i = { %s }\n\n", i->buffer);

        } while (cmp_(i, start) < 0);


        do {
            j--;
            debug_msg(3, "j = { %s }\n\n", j->buffer);
            // if (DEBUG) printf("j = { %s }\n\n", j->buffer);

        } while (cmp_(j, start) > 0);
        


        if (i > j) {

            swap_(start, j);

            qsort_(start, j-start+1, width, strcmp_);
            qsort_(i, end-i+1, width+1, cmp_);
            
            break;
        } 
        
        swap_(i, j);
    }
}
