#include "../header/work_with_strings.h"



int strings_spliting(char* full_line, line* array_of_lines) { 
        
    if ( full_line == NULL || array_of_lines == NULL) { puts("!!!  input error  !!!"); assert(0); }
    // TODO: vidimo net

    int line_count = 1;
    array_of_lines[0].buffer = full_line;


    for (int i = 0; full_line[i] != '\0'; i++) {

        if (full_line[i] == '\n')  {
            full_line[i] = '\0';
            line_count++;

            array_of_lines[line_count - 1].buffer = full_line + i + 1;

            array_of_lines[line_count - 2].length = array_of_lines[line_count - 1].buffer - 
                                                    array_of_lines[line_count - 2].buffer - 1;
        }   
    }

    return line_count;
}

int strcmp_reverse(const void* x, const void* y) {

    line* i = ( line* )x;
    line* j = ( line* )y;

    const char* str1 = i->buffer;
    const char* str2 = j->buffer;

    int len1 = i->length, len2 = j->length;

    int min_len = (len1 < len2) ? len1 : len2;

    for (int i = 0; i < min_len; i++) {

        int strcmp_ = strcmp(str1+len1-1-i, str2+len2-1-i);

        if (strcmp_) return strcmp_;
    }
    //ass
    //ads

    return len1-len2;
}

int strcmp_(const void* x, const void* y) { ///

    line* i = ( line* )x;
    line* j = ( line* )y;

    const char* str1 = i->buffer;
    const char* str2 = j->buffer;

    int len1 = i->length, len2 = j->length;

    int min_len = (len1 < len2) ? len1 : len2;

    for (int i = 0; i < min_len; i++) {

        int strcmp_ = strcmp(str1+i, str2+i);
        if (strcmp_) return strcmp_;
    }

    return len1-len2;
}
