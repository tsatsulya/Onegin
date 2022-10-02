#include "string_functions.h"



int split_string(char* full_line, string* array_of_lines) { 
        
    if ( full_line == NULL || array_of_lines == NULL) assert(0 && "!!!  input error  !!!"); 

    int line_count = 1;
    array_of_lines[0].buffer = full_line;


    for (int i = 0; full_line[i] != '\0'; i++) {

        if (full_line[i] == '\n')  {

            full_line[i] = '\0';

            array_of_lines[line_count].buffer = full_line + i + 1;

            array_of_lines[line_count - 1].length = array_of_lines[line_count].buffer - 
                                                    array_of_lines[line_count - 1].buffer - 1;

            line_count++;

        }   
    }

    return line_count;
}




int general_strcmp(string* lhs, string* rhs, int step) {

    char* str1 = lhs->buffer;
    char* str2 = rhs->buffer;
    int len1 = lhs->length;
    int len2 = rhs->length; 
    
    int min_len = (len1 < len2) ? len1 : len2;
    int c = (step > 0) ? 0 : min_len;

    for (; c < min_len && c >= 0; c += step) {
        int i1, i2;
        if ( step > 0 ) {
            i1 = i2 = c;
        } 
        else {
            i1 = len1-c-1;
            i2 = len2-c-1;
        }
        int res = str1[i1] - str2[i2];

        if (res) return res;
        //printf("%d\n", *(str1+c)-*(str2+c));
    }
    return (len2-len1);
}
 int strcmp_(string* lhs, string* rhs) {
    int step = 1;
    return general_strcmp(lhs, rhs, step);
}


int strcmp_reverse(string* lhs, string* rhs) {
    int step = -1;
    return general_strcmp(lhs, rhs, step);
}
// int general_strcmp(string* lhs, string* rhs, int step) {
//     char* str1 = lhs->buffer;
//     char* str2 = rhs->buffer;
    
//     int len1 = lhs->length;
//     int len2 = rhs->length; 
    
//     int min_len = (len1 < len2) ? len1 : len2;
//     int c = (step > 0) ? 0 : min_len;
//     printf("rrr %d\n", c);

//     for (; c < min_len && c >= 0; c += step) {
        
//         int res = str1[c] - str2[c];

//         if (res) return res;
//         //printf("%d\n", *(str1+c)-*(str2+c));
//     }
//     return (len1-len2);
// } 

// int strcmp_(string* lhs, string* rhs) {
//     general_strcmp(lhs, rhs, 1);
//     return 0;
// }

// int strcmp_reverse(string* lhs, string* rhs) {
//     general_strcmp(lhs, rhs, -1);
//     return 0;
// }
 




