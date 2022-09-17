#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h> 


// int int_cmp(int a, int b)

typedef struct _file { // File or file_t
    char* buffer;
    int size;
    // move all calculated values here
} buffer;

typedef struct _string {
    char* string;
    int length;
} row; // line?

// #ifdef DEBUG
//     void debug_print(const char* msg) {
//         fprintf(stderr, "%s", msg);
//     }
// #else
//     void debug_print(const char* msg) {
//     }
// #endif


void bubbleSort(row* array, int row_count);

int size_of_file(FILE* file);

row* initialization (buffer* buf, int* num_of_str);

buffer* _read (const char file_name[], const char mode[]);

int string_handling(char* full_line, row* struct_array);

void print(row* array, int row_count);

// enum CmpMode {
//     STRAIGHT,
//     REVERSE
// };

void qsort_(row* begin, row* end, int  REVERSE);

int strcmp_reverse(char*  i, char* j);

void fprint_ (const row struct_str[], int size, FILE* file);


int main()
{
    //const int REVERSE = 1;
    const int DEBUG = 0;
    
    puts("\n\n------------------------------------ begin ------------------------------------\n\n"); 


    buffer* buf = _read("in.txt", "r");
    FILE* file_out = fopen("SortedText.txt", "w");
    if (!buf) return 1;
    if (!file_out) return 1;

    int row_count = 0;

    row* full_text = initialization (buf, &row_count);


    double start = clock();

    //print(full_text, row_count);
 
    //qsort_(full_text, full_text+row_count-1, REVERSE);
  
    bubbleSort(full_text, row_count);

    double end = clock();


    printf("ROW COUNT = %d\n", row_count);
    printf("TIME: %lf\n\n", (end-start)/(CLOCKS_PER_SEC));

    fprint_(full_text, row_count, file_out);

    fclose(file_out);

    free(buf);
    free(full_text);
    
    puts("\n\n------------------------------------ end -------------------------------------\n\n"); 
    
    return 0;
}



void print(row* array, int row_count) {

    for (int i=0; i<row_count; ++i) {

        printf("Row #%d: { %s }\n", i+1, (array+i)->string);
        printf("Size of row #%d is %d\n\n", i+1, (array+i)->length);

    }
}

int size_of_file(FILE* file) {

    if (file) assert("failed to read file");

    fseek(file, 0L, SEEK_END);

    int size = ftell(file);
    printf("SIZE OF FILE: %d\n\n", size);

    return size;

}

int number_of_lines(FILE* file) {

    if (file) assert("failed to read file");

    rewind(file);
    int buffer = 0;
    int row_count = 0;

    while (buffer != EOF) {

        buffer = fgetc(file);
        if (buffer == '\n') {
            ++row_count;
        }
    }
    
    rewind(file);

    return row_count;
}

buffer* _read (const char file_name[], const char mode[])
{
    puts("--> reading input file...\n");

    FILE* file = fopen (file_name, mode);


    if (file) {
        puts("--> file read successfully\n"); }
    else {
        puts("!!!  file reading error  !!!"); assert(0); }


    buffer* elem = (buffer*) calloc (1, sizeof (buffer));

    elem -> size = size_of_file(file);

    printf("--> read file size: %d\n\n", elem->size);
    
    char* buffer = (char*) calloc(elem->size, sizeof (char));
    elem -> buffer = buffer;


    rewind(file);
    int read_objects = fread (elem->buffer, sizeof(char), elem -> size, file);
    rewind(file);


    printf("--> number of read objects: %d\n\n", read_objects);

    fclose (file);

    return elem;
}

row* initialization (buffer* buf, int* row_count)
{  
    puts("--> rows nitialization...\n");

    if ( buf == NULL || row_count == NULL) { puts("!!!  input error  !!!"); assert(0); }

    row* full_text = (row*) calloc(buf->size, sizeof(row));

    if (full_text == NULL) { puts("!!!  failed to allocate memory  !!!"); assert(0); }

    *row_count = string_handling(buf -> buffer, full_text);

    full_text = (row*)(realloc (full_text, sizeof(full_text[0]) * (*row_count)));

    if (full_text == NULL) {puts("!!!  failed to reallocate memory  !!!"); assert(0);}

    return full_text;
}

int string_handling(char* full_line, row* struct_array) 
{
    puts("--> string handling...\n");
    
    if ( full_line == NULL || struct_array == NULL) { puts("!!!  input error  !!!"); assert(0); }

    int row_count = 0;
    struct_array[0].string = full_line;

    for (int i = 0; full_line[i] != '\0'; i++) {

        if (full_line[i] == '\n' || full_line[i] == '\r')  {
            
            full_line[i] = '\0';
            row_count++;

            struct_array[row_count].string = full_line + i + 1;

            struct_array[row_count - 1].length = struct_array[row_count].string - struct_array[row_count- 1].string - 1;
        }   
    }
    puts("--> handling is over!\n");
    return row_count;
}

void swap_(row* xp, row* yp)
{
    if (DEBUG) printf("\n\nSWAP:3  { %s -> %s }\n\n", xp->string, yp->string);

    row temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// ptr to cmp function
void qsort_(row* i, row* j, int REVERSE) {

    row* start = i;
    row* end = j;
    int size = j-i+1;

    if (size <= 1) return;

    if (size == 2) {
        int res = REVERSE ? strcmp_reverse(i->string, j->string) : strcmp(i->string, j->string);
        if (res > 0) 
            swap_(i, j);
        return;
    }

    if (DEBUG) printf(".................>SIZE : %d\n\n", size);
    if (DEBUG) printf(" -> BEGIN: %s   END: %s\n\n", start->string, (end)->string);
    //srand(time(NULL));


    char* pivot = start->string;

    j++;
    while(1){
        do { 
            i++;
            if (!i->string) break;
            if (DEBUG) printf("i = { %s }\n\n", i->string);

        } while ( (REVERSE ? strcmp_reverse(i->string, pivot) : strcmp(i->string, pivot)) < 0);


        do {
            j--;
            if (DEBUG) printf("j = { %s }\n\n", j->string);

        } while ( (REVERSE ? strcmp_reverse(j->string, pivot) : strcmp(j->string, pivot)) > 0);
        


        if (i > j) {

            swap_(start, j);

            qsort_(start, j-1, REVERSE);
            qsort_(i, end, REVERSE);
            
            break;
        } 
        
        swap_(i, j);
    }
}

void fprint_ (const row struct_str[], int size, FILE* file) {

    for (int i = 0; i < size; i ++) {

        if (struct_str[i].string[0] != '\0')
            fprintf (file, "  { %s }\n", (struct_str[i].string));
    }
}

int strcmp_reverse(char*  i, char* j) {

    char* str1 = i;
    char* str2 = j;

    int len1 = strlen(str1), len2 = strlen(str2);

    if (DEBUG) printf("len1 = %d ; len2 = %d \n", len1, len2);
    int min_len = (len1 < len2) ? len1 : len2;


    for (int i = 0; i < min_len; i++) {

        int strcmp_ = strcmp(str1+len1-1-i, str2+len2-1-i);
        //puts(str1+len1-1-i); puts(str2+len2-1-i);
        if (strcmp_) return strcmp_;
    }

    return len1-len2;

    // if (len1<len2) return -1;
    // if (len1>len2) return 1;
    // return 0;
}





void bubbleSort(row* array, int row_count) {

  for (int i = 0; i < row_count - 1; ++i) {
      
    for (int j = 0; j < row_count - i - 1; ++j) {
      
      if (strcmp( (array + j) ->string, (array + j + 1)->string) > 0) {
        
        swap_(array + j, array + j + 1);

      }
    }
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