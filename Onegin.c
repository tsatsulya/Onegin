#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h> 


static const int DEBUG = 0; // TODO: remove
typedef struct File {
    char* buffer;
    int size;
} buffer; // TODO: use of typedef struct ... conflicts with idiomatic way

// If you want to use typedef for a custom "type",
// declare it separately.
//
// For example,
// typedef String line;

typedef struct String {
    char* string; // TODO: maybe more like "buffer"?)
    int length;
} line;

//??????????????????????

#ifdef DEBUG
    void debug_print(const char* msg, ...) {
        va_list args; // TODO: learn about va_list (check out man!)
        va_start(msg, args);

        vprintf("\n%s\n", args);


        va_end(args);
    }
#else
    void debug_print(const char* msg) {
    }
#endif

#ifdef DEBUG
#define DEBUG_PRINT(format, ...) printf(format, __VA_ARGS__)
#else
#define DEBUG_PRINT(...) ((void) 0)
#endif

// TODO: learn about fast inverse square root

// ???????????????????????????????????????????????????????


void bubble_sort(line* array, int line_count);

int count_symbols(FILE* file);

line* initialization (buffer* buf, int* num_of_str);

buffer* read_buffer (const char file_name[]);

int string_handling(char* full_line, line* struct_array);

void nqsort_(void* base, size_t size, size_t width, int (*cmp_)(const char*, const char*));

void print(line* array, int line_count);

// enum CmpMode {
//     STRAIGHT,
//     REVERSE
// };

void qsort_(line* begin, line* end, int  REVERSE);

int strcmp_reverse(const char*  i, const char* j);

void fprint_ (const line struct_str[], int size, FILE* file);


int main()
{
    puts("\n\n------------------------------------ begin ------------------------------------\n\n"); 


    buffer* buf = read_buffer("in.txt", "r");
    FILE* file_out = fopen("SortedText.txt", "w");
    if (!buf) return 1;

    if (!file_out) {
        // TODO: reason for failure is stored in errno,
        // learn about perror and strerror, they will help!
        return 1;
    }

    int line_count = 0;

    line* full_text = initialization (buf, &line_count);


    double start = clock();

    //print(full_text, line_count);
    // bubble_sort(full_text, line_count);
    nqsort_(full_text, line_count, sizeof(line*), strcmp_reverse);

    double end = clock();
    if (DEBUG) print(full_text, line_count);

    printf("ROW COUNT = %d\n", line_count);
    printf("TIME: %lf\n\n", (end-start)/(CLOCKS_PER_SEC));

    fprint_(full_text, line_count, file_out);

    fclose(file_out);

    free(buf);
    free(full_text);
    
    puts("\n\n------------------------------------ end -------------------------------------\n\n"); 
    
    return 0;
}



static void print(line* array, int line_count) {
// ^~~ TODO! Make internal functions static
    for (int i=0; i<line_count; ++i) {

        printf("Line #%d: { %s }\n", i+1, (array+i)->string);
        printf("Size of line ; #%d is %d\n\n", i+1, (array+i)->length);

    }
}

int count_symbols(FILE* file) {

    assert(file && "failed to read file");
    // TODO: place if in assert

    fseek(file, 0L, SEEK_END);

    int size = ftell(file);
    printf("SIZE OF FILE: %d\n\n", size);

    return size;

}

int number_of_lines(FILE* file) {

    if (file) assert("failed to read file");

    rewind(file);
    int buffer = 0;
    int line_count = 0;

    while (buffer != EOF) {

        buffer = fgetc(file);
        if (buffer == '\n') {
            ++line_count;
        }
    }
    
    rewind(file);

    return line_count;
}

buffer* read_buffer (const char file_name[])
{

    FILE* file = fopen (file_name); // TODO: just use "r"
                                          //       since it already obvious

    if (file) {
        puts("--> file read successfully\n");
    }
    else
        assert(0 && "!!!  file reading error  !!!");



    buffer* elem = (buffer*) calloc (1, sizeof(*elem));
    // TODO: consider                          ^~~~~

    elem -> size = count_symbols(file);

    printf("--> read file size: %d\n\n", elem->size);
    
    char* buffer = (char*) calloc(elem->size, sizeof (char));
    elem -> buffer = buffer;


    rewind(file); // TODO
    int read_objects = fread (elem->buffer, sizeof(char), elem -> size, file);
    rewind(file); // TODO: no need to rewind


    printf("--> number of read objects: %d\n\n", read_objects);

    fclose (file);

    return elem;
}

line* initialization (buffer* buf, int* line_count)
{  // TODO: rename
    puts("--> rows nitialization...\n");

    if ( buf == NULL || line_count == NULL) { puts("!!!  input error  !!!"); assert(0); }

    line* full_text = (line*) calloc(buf->size, sizeof(line));

    if (full_text == NULL) { puts("!!!  failed to allocate memory  !!!"); assert(0); }

    *line_count = string_handling(buf -> buffer, full_text);

    full_text = (line*) realloc (full_text, sizeof(full_text[0]) * (*line_count));

    if (full_text == NULL) {puts("!!!  failed to reallocate memory  !!!"); assert(0);}

    return full_text;
}

int string_handling(char* full_line, line* struct_array) { // TODO: rename 2nd param
    // TODO: rename 
    puts("--> string handling...\n");
    
    if ( full_line == NULL || struct_array == NULL) { puts("!!!  input error  !!!"); assert(0); }

    int line_count = 0; // TODO: probably should start from 1
    struct_array[0].string = full_line;

    for (int i = 0; full_line[i] != '\0'; i++) {

        if (full_line[i] == '\n' || full_line[i] == '\r')  {
            // TODO: questionable:                  ^~~~
            full_line[i] = '\0';
            line_count++;

            struct_array[line_count].string = full_line + i + 1;

            struct_array[line_count - 1].length = struct_array[line_count].string - struct_array[line_count- 1].string - 1;
        }   
    }

    // TODO: calculte length of the last line
    puts("--> handling is over!\n");
    return line_count;
}

void swap_(line* xp, line* yp)
{
    // TODO: extract in macro (also, see __LINE__, __FILE__, __TIME__, __DATA__, __FUNCTION__)
    if (DEBUG) printf("\n\nSWAP:3  { %s -> %s }\n\n", xp->string, yp->string);

    line temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void fprint_ (const line struct_str[], int size, FILE* file) {

    for (int i = 0; i < size; i ++) {

        if (struct_str[i].string[0] != '\0')
            fprintf (file, "  { %s }\n", (struct_str[i].string));
    }
}

int strcmp_reverse(const char*  i, const char* j) {

    const char* str1 = i;
    const char* str2 = j;

    int len1 = strlen(str1), len2 = strlen(str2);

    if (DEBUG) printf("len1 = %d ; len2 = %d \n", len1, len2);
    int min_len = (len1 < len2) ? len1 : len2;


    for (int i = 0; i < min_len; i++) {

        int strcmp_ = strcmp(str1+len1-1-i, str2+len2-1-i);
        //puts(str1+len1-1-i); puts(str2+len2-1-i);
        if (strcmp_) return strcmp_;
    }

    return len1-len2;
}



void bubble_sort(line* array, int line_count) {

  for (int i = 0; i < line_count - 1; ++i) {
      
    for (int j = 0; j < line_count - i - 1; ++j) {
      
      if (strcmp( (array + j) ->string, (array + j + 1)->string) > 0) {
        
        swap_(array + j, array + j + 1);

      }
    }
  }
}


void nqsort_(void* base, size_t size, size_t width, int (*cmp_)(const char*, const char*)) {
    // TODO: generalize qsort
    
    line* i = base;
    line* start = i;
    line* end = start+size-1;
    line* j = start+size-1;

    if (size <= 1) return;

    if (size == 2) {
        int res = cmp_(i->string, j->string);
        if (res > 0) 
            swap_(i, j);
        return;
    }

    if (DEBUG) printf(".................>SIZE : %d\n\n", size);
    if (DEBUG) printf(" -> BEGIN: %s   END: %s\n\n", start->string, (start+size-1)->string);
    //srand(time(NULL));


    char* pivot = start->string;

    j++;
    while(1){
        do { 
            i++;
            if (i>=end) break;
            if (DEBUG) printf("i = { %s }\n\n", i->string);

        } while (cmp_(i->string, pivot) < 0);


        do {
            j--;
            if (DEBUG) printf("j = { %s }\n\n", j->string);

        } while (cmp_(j->string, pivot) > 0);
        


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