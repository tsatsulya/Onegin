#include "header/utilities.h"
#include "header/work_with_files.h"
#include "header/work_with_strings.h"

//const int GLOBAL_DEBUG_MODE = 4;

// TODO: learn about fast inverse square root


// TODO: extract this in other headers
void debug_msg(int mode, const char* format, ...);
void bubble_sort(line* array, int line_count);

// TODO: Why "n"? Reconsider.
void nqsort_(void* base, size_t size, size_t width, cmp_func cmp_);

static void print(line* array, int line_count);

int main()
{

    puts("\n\n------------------------------------ begin ------------------------------------\n\n"); //

    int line_count = 0;
    buffer* buf = read_buffer("input_files/in.txt", &line_count);

    FILE* file_out = fopen("SortedText.txt", "w");

    if (errno) {
        printf(" Damn: %s\n", strerror(errno) );
        // TODO: Equivalent to:
        // perror(" Damn: ");
        return 1; // TODO: use EXIT_FAILURE
    }

    if (!file_out) {
        printf(" Damn: %s\n", strerror(errno) );
        return 1;
    }

    line* full_text = build_array_of_lines(buf, line_count);

    debug_msg(3, "ROW COUNT = %d\n", line_count);

    double start = clock();

    if (GLOBAL_DEBUG_MODE >= 2) print(full_text, line_count);


    // bubble_sort(full_text, line_count);
    nqsort_(full_text, line_count, sizeof(line*), strcmp_);

    double end = clock();

    // TODO: extraaaAAAAaaaAAAct!
    if (GLOBAL_DEBUG_MODE>=3) print(full_text, line_count);

   
    printf("TIME: %lf\n\n", (end-start)/(CLOCKS_PER_SEC));

    fprint_(full_text, line_count, file_out);

    fclose(file_out);
    //

    // dtor
    free(buf);
    free(full_text);
    
    puts("\n\n------------------------------------ end -------------------------------------\n\n"); 
    
    return 0;
}


void debug_msg(int mode, const char* format, ...)
{
    if (mode<=GLOBAL_DEBUG_MODE) {//??????????????????????????????
        int d; 
        double f;
        char* s;
        va_list factor;        // TODO: This probably should be unconditional
        va_start(factor, format);  
        
        for(const char *c = format;*c; c++)
        {
            if(*c!='%')
            {
                printf("%c", *c);
                continue;
            }
            switch(*++c)
            {
                case 'd': 
                    d = va_arg(factor, int);
                    printf("%d", d);
                    break;
                case 'f': 
                    f = va_arg(factor, double);
                    printf("%.2lf", f);
                    break;
                case 's':
                    s = va_arg(factor, char*);
                    printf("%s", s);
                    break;

                default:
                    printf("%c", *c);
            }
        }
        va_end(factor);
    }
    return;
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

static void print(line* array, int line_count) {
    // TODO: Maybe rename to something like "print_lines_debug"

    for (int i=0; i<line_count; ++i) {

        printf("Line #%d: { %s }\n", i+1, (array+i)->buffer);
        printf("Size of line : #%d is %d\n\n", i+1, (array+i)->length);

    }
}

void bubble_sort(line* array, int line_count) {

  for (int i = 0; i < line_count - 1; ++i) {
      
    for (int j = 0; j < line_count - i - 1; ++j) {
      
      if (strcmp( (array + j)->buffer, (array + j + 1)->buffer) > 0) {
        
        swap_(array + j, array + j + 1);

      }
    }

    // TODO: Optimize bubble sort, use early exit if array is sorted
  }
}


void nqsort_(void* base, size_t size, size_t width, cmp_func cmp_) {
    // TODO: generalize qsort
    
    line* i = (line*)base;
    line* start = i;
    line* end = start+size-1;
    line* j = start+size-1;

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
    while(1){ // TODO: use bools! Use #include <stdbool.h> (e.g. true in while in this case)
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

            nqsort_(start, j-start+1, width, cmp_);
            nqsort_(i, end-i+1, width+1, cmp_);
            
            break;
        } 
        
        swap_(i, j);
    }
}



//ЭТА ХУЙНЯ НЕ РАБОТАЕТ, ЕСЛИ ЕСТЬ ПОВТОРЯЮЩИЕСЯ СТРОКИ!!!!!!!!!!!!!!!!!!!
//ТЕПЕРЬ ЭТА ХУЙНЯ РАБОТАЕТ, ЕСЛИ ПОВТОРЯЮТСЯ СТРОКИ!!!! НАДО УБРАТЬ \N
//ЭТА ХУЙНЯ СНОВА НЕ РАБОТАЕТ, НАДО МЕНЯТЬ АЛГОРИТМ И СРАТЬ НА ПОВТОРЯЮЩИЕСЯ СТРОКИ!!!
//проверка входных данных
//DEBUG??????????????????????????????????????????
//аргументы для консоли 
//комментарии
// ЗДЕСТЬ БЫЛ ВАСЯ
// ТЕПЕРЬ И САША
// ЗДОРОВА ПАРНИ ТУТ РУСТАМ ВСЕМ ХАЙ
// Хелло Рустам, как зовут?