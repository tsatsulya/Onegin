
#include "../header/work_with_files.h"

int strings_spliting(char* full_line, line* array_of_lines); //

int count_lines(char* full_line) {

    int line_count = 0;
    for (int i = 0; full_line[i] != '\0'; i++) {
        if (full_line[i] == '\n' || full_line[i] == '\r')  {
            line_count++;
        }   
    }
    return line_count;
}

int count_symbols(FILE* file) {

    assert(file && "failed to read file");

    int start_position = ftell(file);//
    rewind(file);//

    fseek(file, 0L, SEEK_END);

    int size = ftell(file);//
    //("SIZE OF FILE: %d\n\n", size);

    fseek(file, start_position, SEEK_SET); //

    return size;

}

buffer* read_buffer(const char file_name[], int* line_count)
{
    
    buffer* elem = (buffer*) calloc (1, sizeof(*elem));
    
    assert(elem && "!!!  failed to allocate memory  !!!"); 

    FILE* file = fopen (file_name, "r");
    if (!file) 
        return elem;

    elem -> size = count_symbols(file);
   
    char* buffer = (char*) calloc(elem->size, sizeof (char));
    //
    elem -> buffer = buffer;

    int read_objects = fread (elem->buffer, sizeof(char), elem -> size+1, file);//
    if (GLOBAL_DEBUG_MODE > 2) 
        fprintf(stderr, "read objects: %d\n\n", read_objects);
    *line_count = count_lines(elem->buffer);

    fclose (file);//

    return elem;
}

line* build_array_of_lines (buffer* buf, int line_count) {

    assert(buf && "!!!  input error  !!!");

    line* full_text = (line*) calloc(line_count, sizeof(line)); //

    strings_spliting(buf -> buffer, full_text);

    assert(full_text && "!!!  failed to allocate memory  !!!"); 

    return full_text;
}

void fprint_ (const line str[], int size, FILE* file) {

    for (int i = 0; i < size; i ++) {

        if (str[i].buffer[0] != '\0')
            fprintf (file, " %s  \n", (str[i].buffer));
    }
}
