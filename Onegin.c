#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct _file {
    char* buffer;
    int size;
} buffer;

typedef struct _string {
    char* string;
    int length;
} row;

int size_of_file(FILE* file);
int number_of_lines(FILE* file);
row* initialization (buffer* buf, int* num_of_str);
buffer* _read (const char file_name[], const char mode[]);
int string_handling(char* full_line, row* struct_array);
void print(row* array, int row_count);
void swap(row* array, int x, int y);


int main(int argc, char **argv)
{
    puts("\n\n------------------------- begin ------------------------------------\n\n"); 


    buffer* buf = _read("in.txt", "r");
    FILE* file_out = fopen("SortedText.txt", "w");
    //  ПРОВЕРИТЬ, НОРМАЛЬНО ЛИ ОТКРЫЛИСЬ ФАЙЛЫ  

    int row_count = 0;
    row* struct_array = initialization (buf, &row_count);
    printf("Row count is %d\n\n", row_count);

    print(struct_array, row_count);
    swap(struct_array, 1, 2);
    print(struct_array, row_count);


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
    return row_count;
}

void swap(row* array, int x, int y) {
    row tmp = *(array+x);
    *(array + x) = *(array+y);
    *(array+y) =  tmp;
}

int cmp(char* s1, char* s2) {
    if (strcmp(s1, s2) >= 0) return 1;
    return 0;
}

void qsort(row* rows_array, int row_count, int starter){
    if (row_count <= 1) return;

    for (int i = 0; i<row_count; ++i) {
        if (i == starter) continue;
        char* str1 = (rows_array + starter)->string;
        char* str2 = (rows_array + i)->string;
    }
}