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


 int strcmp_(string* lhs, string* rhs) {

    int step = 1;
    char* str1 = lhs->buffer;
    char* str2 = rhs->buffer;
    debug_msg(4,"%s ??? %s \n", str1, str2);
    int len1 = lhs->length;
    int len2 = rhs->length; 
    debug_msg(4, "%d ??? %d \n", len1, len2);
    
    int min_len = (len1 < len2) ? len1 : len2;
    int c = (step > 0) ? 0 : min_len;

    for (; c < min_len && c >= 0; c += step) {
        
        int res = str1[c] - str2[c];

        if (res) return res;
        //printf("%d\n", *(str1+c)-*(str2+c));
    }
    return (len2-len1);
}





// int strcmp_reverse(string* i, string* j) {
//     //int step = 1;
//     char* str1 = i->buffer;
//     char* str2 = j->buffer;
    
//     int len1 = i->length;
//     int len2 = j->length; 
//     puts(str1);
//     puts(str2);
//     int min_len = (len1 < len2) ? len1 : len2;
//     //printf("min len is %d\n", min_len);
//     for (int c = 0; c < min_len; c++) {
//         int res = str1[len1-1-c] - str2[len2-1-c];
//         //printf("res is %d\n", res);
//         if (res) {
//             puts("eee");
//             return res;
//             }
//         //debug_msg(3, "%c %s %c \n", str1[len1-1-c], (str1[len1-1-c] - str2[len2-1-c] > 0) ? ">" : "<=",  str2[len2-1-c] );
//     }
//     return (len2-len1);
// }


// int strcmp_reverse(string* i, string* j) {


//     const char* str1 = i->buffer;
//     const char* str2 = j->buffer;

//     int len1 = i->length, len2 = j->length;

//     int min_len = (len1 < len2) ? len1 : len2;

//     for (int i = 0; i < min_len; i++) {

//         int strcmp_ = strcmp(str1+len1-1-i, str2+len2-1-i);

//         if (strcmp_) return strcmp_;
//     }
//     //ass
//     //ads

//     return len1-len2;
// }



// int general_strcmp(string* lhs, string* rhs, int step) {
//     char* str1 = lhs->buffer;
//     char* str2 = rhs->buffer;
    
//     int len1 = lhs->length;
//     int len2 = rhs->length; 
    
//     int min_len = (len1 < len2) ? len1 : len2;
//     int c = (step > 0) ? 0 : min_len;
//     // printf("rrr %d\n", c);

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
 




