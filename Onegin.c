#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h> 

typedef struct _file {
    char* buffer;
    int size;
} buffer;

typedef struct _string {
    char* string;
    int length;
} row;

const int DEBUG = 1;


int size_of_file(FILE* file);

int number_of_lines(FILE* file);

row* initialization (buffer* buf, int* num_of_str);

buffer* _read (const char file_name[], const char mode[]);

int string_handling(char* full_line, row* struct_array);

void print(row* array, int row_count);

row* HoarePartition (row* p, row* r);

void QuickSort(row* start, row* end);

void swap(row* array, int x, int y);

int cmp_(const char* s1, const char* s2);

void qsort_(row* begin, row* end);


int main(int argc, char **argv)
{
    puts("\n\n------------------------- begin ------------------------------------\n\n"); 


    buffer* buf = _read("in.txt", "r");
    FILE* file_out = fopen("SortedText.txt", "w");

    //  ПРОВЕРИТЬ, НОРМАЛЬНО ЛИ ОТКРЫЛИСЬ ФАЙЛЫ  

    int row_count = 0;
    row* struct_array = initialization (buf, &row_count);

    double start = clock();

    print(struct_array, row_count);
 
    qsort_(struct_array, struct_array+row_count-1);
 
    print(struct_array, row_count);
 
 
    double end = clock();
 
 
    printf("TIME: %lf\n\n", (end-start)/1000);

    
    fclose(file_out);

    puts("\n\n-------------------------- end -------------------------------------\n\n"); 
    
    return 0;
}



void print(row* array, int row_count) {
    for (int i=0; i<row_count; ++i) {
        printf("Row #%d: { %s }\n", i+1, (array+i)->string);
        printf("Size of row #%d is %d\n\n", i+1, (array+i)->length);
    }
}

int size_of_file(FILE* file) {

    fseek(file, 0L, SEEK_END);
    return ftell(file);

}

int number_of_lines(FILE* file) {

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
        puts("!!!  reading error  !!!"); assert(0); }

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

    row* struct_array = (row*) calloc(buf->size, sizeof(row));

    if (struct_array == NULL) { puts("!!!  failed to allocate memory  !!!"); assert(0); }

    *row_count = string_handling(buf -> buffer, struct_array);

    struct_array = realloc (struct_array, sizeof(struct_array[0]) * (*row_count));

    if (struct_array == NULL) {puts("!!!  failed to reallocate memory  !!!"); assert(0);}

    return struct_array;
}

int string_handling(char* full_line, row* struct_array) 
{
    puts("--> string handling...\n");
    int n_count = 0;
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
    puts("done!");
    return row_count;
}

int cmp_(const char* s1, const char* s2) {
    if (strcmp(s1, s2) >= 0) return 1;
    return 0;
}

void swap_(row* xp, row* yp)
{
   // printf("SWAP:3  { %s -> %s }\n\n", xp->string, yp->string);
    row temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void qsort_(row* i, row* j) {

    
    row* start = i;
    row* end = j;
    int size = j-i;
    
    if (size <= 1) return;

    int r = rand()%size;
    
    char* element = (i+r)->string;

    if (DEBUG) {
        printf(" -> SIZE: %d\n", size);
        printf("r = %d\n", r);
        printf(" -> ELEMENT: %s\n", element);
        printf(" -> BEGIN: %s   END: %s\n\n", i->string, (i+size)->string);
    }

    while (1) {
        while (strcmp(element, i->string)>=0)  {
            
            i++;
            if (DEBUG) printf("     -> i = %d, { %s }\n", i, i->string);

        }

        while (strcmp(element, j->string)<0) {
        
            j--;
            if (DEBUG) printf("     -> j = %d, { %s }\n", j, j->string);
        
        }
        
        
        if (j < i) {
            qsort_(start, i-1);
            qsort_(j+1, end);
            return;
        }
        swap_(i, j);
    }
}


//ЭТА ХУЙНЯ НЕ РАБОТАЕТ, ЕСЛИ ЕСТЬ ПОВТОРЯЮЩИЕСЯ СТРОКИ!!!!!!!!!!!!!!!!!!!
//ТЕПЕРЬ ЭТА ХУЙНЯ РАБОТАЕТ, ЕСЛИ ПОВТОРЯЮТСЯ СТРОКИ!!!! НАДО УБРАТЬ \N
//ЭТА ХУЙНЯ СНОВА НЕ РАБОТАЕТ, НАДО МЕНЯТЬ АЛГОРИТМ И СРАТЬ НА ПОВТОРЯЮЩИЕСЯ СТРОКИ!!!