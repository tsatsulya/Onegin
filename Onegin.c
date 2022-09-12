#include <stdio.h>
#include <stdlib.h>
int size_of_file(FILE* file);
int number_of_lines(FILE* file);


typedef struct _file {
    char* buffer;
    int size;
} buffer;

typedef struct _string {
    char* string;
    int length;
} row;

row* initialization (buffer* buf, int* num_of_str);
buffer* _read (const char file_name[], const char mode[]);
int string_handling(char* full_line, row* struct_array);

int main(int argc, char **argv)
{
    puts("\n\n------------------------- begin ------------------------------------\n\n"); 


    buffer* buf = _read("in.txt", "r");
    FILE* file_out = fopen("SortedText.txt", "w");
    //  ПРОВЕРИТЬ, НОРМАЛЬНО ЛИ ОТКРЫЛИСЬ ФАЙЛЫ 


    int row_count = 0;

    //row* struct_array = initialization (buf, &row_count);
    printf("number of lines: %d \n", row_count);

    puts("\n\n-------------------------- end -------------------------------------\n\n"); 

    fclose(file_out);
    
    return 0;
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
    FILE* file = fopen (file_name, mode);

    buffer* elem = (buffer*) calloc (1, sizeof (buffer));

    elem -> size = size_of_file(file);

    char* buffer = (char*) calloc(elem->size, sizeof (char));
    elem -> buffer = buffer;

    fread (buffer, sizeof(char), elem -> size, file);

    fclose (file);

    return elem;
}

row* initialization (buffer* buf, int* row_count)
{
    row* struct_array = (row*) calloc(buf->size, sizeof(row));

    *row_count = string_handling(buf -> buffer, struct_array);

    struct_array = realloc (struct_array, sizeof(struct_array[0]) * (*row_count));

    return struct_array;
}


int string_handling(char* full_line, row* struct_array) 
{
    // ПРОВЕРКА ВЗОДНЫХЗ ДАННЫХ!!!!!!!

    int row_count = 0;
    struct_array[0].string = full_line;

    for (int i = 0; full_line[i] != '\0'; i++) {

        if (full_line[i] == '\n' || full_line[i] == '\r')  {
            
            full_line[i] = '\0';

            struct_array[++row_count].string = full_line + i + 1;
            struct_array[row_count - 1].length = struct_array[row_count].string - struct_array[row_count- 1].string - 1;

        }   
    }
    return row_count;
}