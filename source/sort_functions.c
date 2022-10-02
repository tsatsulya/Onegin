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
            swap__(i, j, sizeof(string));
        return;
    }
    
    debug_msg(4, ".................>SIZE : %d\n\n", (int)size);
    // if (DEBUG) printf(".................>SIZE : %d\n\n", (int)size);
    debug_msg(4, " -> BEGIN: %s   END: %s\n\n", start->buffer, (start+size-1)->buffer);
    // if (DEBUG) printf(" -> BEGIN: %s   END: %s\n\n", start->buffer, (start+size-1)->buffer);

    j++;
    while( true ) {
        do { 
            i++;
            if (i>=end) break;
            debug_msg(4, "i = { %s }\n\n", i->buffer);
            // if (DEBUG) printf("i = { %s }\n\n", i->buffer);

        } while (cmp_(i, start) < 0);


        do {
            j--;
            debug_msg(4, "j = { %s }\n\n", j->buffer);
            // if (DEBUG) printf("j = { %s }\n\n", j->buffer);

        } while (cmp_(j, start) > 0);
        


        if (i > j) {

            swap__(start, j, sizeof(string));

            qsort_(start, j-start+1, width, strcmp_);
            qsort_(i, end-i+1, width+1, cmp_);
            
            break;
        } 
        
        swap__(i, j, sizeof(string));
    }
}



void swap__(void* buf1, void* buf2, size_t size_)
{
    assert (buf1 != NULL);
    assert (buf2 != NULL);

    short const int ll_bytes = sizeof (long long int),  //8
                    l_bytes  = sizeof (int),            //4
                    s_bytes  = sizeof (short int),      //2 
                    c_bytes  = sizeof (char);           //1


    long long int *buf1_ll = (long long int *) buf1;
    long long int *buf2_ll = (long long int *) buf2;


    int position = 0;

    while (size_ >= ll_bytes)
    {
        long long int temp = 0;
        temp = buf1_ll[position];
        buf1_ll[position] = buf2_ll[position];
        buf2_ll [position] = temp;

        ++position;
        size_ -= ll_bytes;
    }

    long int *buf1_l = (long int *) buf1;
    long int *buf2_l = (long int *) buf2;

    while (size_ >= l_bytes)
    {
        long int temp = 0;
        temp = buf1_l[position];
        buf1_l[position] = buf2_l [position];
        buf2_l[position] = temp;

        ++position;
        size_ -= l_bytes;
    }

    short int *buf1_s = (short int*) buf1_l;
    short int *buf2_s = (short int*) buf2_l;

    while (size_ >= s_bytes)
    {
        short int temp = 0;
        temp = buf1_s[position];
        buf1_s[position] = buf2_s[position];
        buf2_s[position] = temp;

        ++position;
        size_ -= s_bytes;
    }

    char *buf1_c = (char*)buf1_s;
    char *buf2_c = (char*)buf2_s;

    while (size_ >= s_bytes)
    {
        char temp = 0;
        temp = buf1_c[position];
        buf1_c[position] = buf2_c[position];
        buf2_c[position] = temp;

        ++position;
        size_ -= c_bytes;
    }
}

