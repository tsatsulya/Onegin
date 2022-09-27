#include "utilities.h"
#include "types.h"
#include <time.h>
#include "file_functions.h"
#include "string_functions.h"
#include "sort_functions.h"
//const int GLOBAL_DEBUG_MODE = 4;

// TODO: learn about fast inverse square root

static void dbg_print_lines(string* array, int line_count);


int main() {

    puts("\n\n------------------------------------ begin ------------------------------------\n\n"); //

    int line_count = 0;
    string* buf = read_buffer("input_files/in.txt", &line_count);

    FILE* file_out = fopen("SortedText.txt", "w");

    if (errno) {
        perror(" Damn: ");
        return EXIT_FAILURE;
    }

    if (!file_out) {
        perror(" Damn: ");
        return EXIT_FAILURE;
    }

    string* full_text = create_arr_of_splited_lines(buf, line_count);

    debug_msg(3, "ROW COUNT = %d\n", line_count);

    double start = clock();

    if (GLOBAL_DEBUG_MODE >= 2) dbg_print_lines(full_text, line_count);


    // bubble_sort(full_text, line_count);
    qsort_(full_text, line_count, sizeof(string*), strcmp_);

    double end = clock();

    // TODO: extraaaAAAAaaaAAAct!
    if (GLOBAL_DEBUG_MODE>=3) dbg_print_lines(full_text, line_count);

   
    printf("TIME: %lf\n\n", (end-start)/(CLOCKS_PER_SEC));

    fprint_without_blank_lines(full_text, line_count, file_out);

    fclose(file_out);
    //

    // dtor
    free(buf);
    free(full_text);
    puts("\n\n------------------------------------ endm -------------------------------------\n\n"); 
    
    return 0;
}



// TODO: Example of simple debugging wrapper:
//
// #ifdef GLOBAL_MODE
// #define print_dbg(...) my_print_debug(__VA_ARGS__)
// #else
// #define print_dbg(...) ((void) 0)
// #endif
//
// This lets you define GLOBAL_MODE conditionally
// using compiler flag "-D", for example:
//
// g++ -DGLOBAL_MODE   my-source-code.cpp
//
// Or even:
//
// g++ -DGLOBAL_MODE=1 my-source-code.cpp
// note:            ^~
//
// You can add this to your build system!
// For example:
//
// make release -j$(nproc) DEBUG=1
// # can make debug build

static void dbg_print_lines(string* array, int line_count) {

    for (int i=0; i<line_count; ++i) {

        printf("Line #%d: { %s }\n", i+1, (array+i)->buffer);
        printf("Size of line : #%d is %d\n\n", i+1, (array+i)->length);

    }
}




//ЭТА ХУЙНЯ НЕ РАБОТАЕТ, ЕСЛИ ЕСТЬ ПОВТОРЯЮЩИЕСЯ СТРОКИ!!!!!!!!!!!!!!!!!!!
//ТЕПЕРЬ ЭТА ХУЙНЯ РАБОТАЕТ, ЕСЛИ ПОВТОРЯЮТСЯ СТРОКИ!!!! НАДО УБРАТЬ \N
//ЭТА ХУЙНЯ СНОВА НЕ РАБОТАЕТ, НАДО МЕНЯТЬ АЛГОРИТМ И СРАТЬ НА ПОВТОРЯЮЩИЕСЯ СТРОКИ!!!
//проверка входных данных
//DEBUG??????????????????????????????????????????
//аргументы для консоли 

// ЗДЕСТЬ БЫЛ ВАСЯ
// ТЕПЕРЬ И САША
// ЗДОРОВА ПАРНИ ТУТ РУСТАМ ВСЕМ ХАЙ
// Хелло Рустам, как зовут?