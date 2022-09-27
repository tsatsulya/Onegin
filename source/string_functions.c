#include "string_functions.h"
// TODO: compiler has "-I" flag, use it!
// E.g. -I ../header, than 



// static int strcmp_(string* i, string* j, enum step step) {
//     char* str1 = i->buffer;
//     char* str2 = j->buffer;
    
//     int len1 = i->length;
//     int len2 = j->length; 
    
//     int min_len = (len1 < len2) ? len1 : len2;
//     int c = (step > 0) ? 0 : min_len;

//     for (; (step > 0) ? (c < min_len) : (c >= 0); c+=step) {
//         int res = *(str1+c)-*(str2+c);
//         if (res) return res;
//         printf("%d\n", *(str1+c)-*(str2+c));
//     }
//     return (len1-len2);
// }

int strings_spliting(char* full_line, string* array_of_lines) { 
        
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

int strcmp_(string* i, string* j) {
    int step = 1;
    char* str1 = i->buffer;
    char* str2 = j->buffer;
    
    int len1 = i->length;
    int len2 = j->length; 
    
    int min_len = (len1 < len2) ? len1 : len2;
    int c = (step > 0) ? 0 : min_len;

    for (; (step > 0) ? (c < min_len) : (c >= 0); c+=step) {
        int res = *(str1+c)-*(str2+c);
        if (res) return res;
        //printf("%d\n", *(str1+c)-*(str2+c));
    }
    return (len1-len2);
}



int strcmp_reverse(string* i, string* j) {
    int step = -1;
    char* str1 = i->buffer;
    char* str2 = j->buffer;
    
    int len1 = i->length;
    int len2 = j->length; 
    
    int min_len = (len1 < len2) ? len1 : len2;
    int c = (step > 0) ? 0 : min_len;

    for (; (step > 0) ? (c < min_len) : (c >= 0); c+=step) {
        int res = *(str1+c)-*(str2+c);
        if (res) return res;
        //printf("%d\n", *(str1+c)-*(str2+c));
    }
    return (len1-len2);
}
