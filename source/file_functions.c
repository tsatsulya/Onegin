
#include "file_functions.h"

FILE* fopen_with_verification(const char file_name[], const char mode[]) {
    errno = 0;
    FILE* file = fopen(file_name, mode);
    if (errno) {
        perror("file opening error: \n");
        return NULL;
        }
    return file;
}
int fread_with_verification(char** buffer, size_t size_t, int size, FILE* file) {
    errno = 0;
    int read_objects = fread(*buffer, size_t, size, file);
    if (errno) 
        perror("file reading error: \n");
    return read_objects;
}
void fclose_with_verification(FILE* file) {
    errno = 0;
    fclose(file);
    if (errno) 
        perror("file opening error: \n");
}
void rewind_with_verification(FILE* file) {
    errno = 0;
    rewind(file);
    if (errno) 
        perror("rewind error: \n");
}
void fseek_with_verification(FILE *file, long offset, int whence) {
    errno = 0;
    fseek(file, offset, whence);
    if (errno) 
        perror("fseek error: \n");
}



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

    int start_position = ftell(file);

    rewind_with_verification(file);

    fseek_with_verification(file, 0L, SEEK_END);

    int size = ftell(file);

    fseek_with_verification(file, start_position, SEEK_SET); 

    return size;

}

string* read_buffer(const char file_name[]) {   

    string* elem = (string*) calloc (1, sizeof(*elem));
    
    assert(elem && "!!!  failed to allocate memory  !!!"); 

    FILE* file = fopen_with_verification(file_name, "r");
    
    if (!file) {
        perror("Damn: ");
        return elem;
    }
    
    elem->length = count_symbols(file);
   
    char* buffer = (char*) calloc(elem->length, sizeof (char));
    
    assert(buffer && "!!!  failed to allocate memory  !!!"); 
    
    elem->buffer = buffer;

  
    int read_objects = fread_with_verification(&(elem->buffer), sizeof(char), elem->length, file);


    if (errno) perror(" Damn: \n");

 
    debug_msg(3, "read objects: %d\n\n", read_objects);
    // TODO:  ^ enum!!!

    fclose_with_verification(file); 
    file = NULL;

    if (errno) perror(" Damn: \n");

    return elem;
}
string* create_arr_of_splited_lines (string* buf, int line_count) { 

    assert(buf && "!!!  input error  !!!");

    string* full_text = (string*) calloc(line_count, sizeof(string)); //
    if (!full_text) {
        perror("Damn: ");
        assert(0);
    }

    split_string(buf->buffer, full_text);

    return full_text;
}



void fprint_without_blank_lines (FILE* file, const string str[], int size) {

    for (int i = 0; i < size; i ++) {

        if (str[i].buffer[0] != '\0')
            fprintf (file, "%s\n", (str[i].buffer));
    }
}



  // TODO: Use named designators, they are awesome!
    // Check this out:
    // *elem = { .buffer = buffer, .size = size };

    // Cool, huh? With enough practice you can do it too!

    // Note, this is a C++ extension.
    // However, if you want to maintain C support there is a similar feature:
    //
    // Called "Compound literal", e.g.
    // (buffer) { .buffer = buffer, .size = size }

    // There a lot you can do with this feature, e.g.
    // int *array = &(int[]) { 1, 2, 3, 4 };

    // But don't overuse it, as it's pretty esoteric

      // TODO, maybe do something like CHECK_ERRNO(fread(...))
    // int read_objects = CHECK_ERRNO(fread(...));
    //
    // There's a handy extension you can use to achive this, e.g. 
    // int hello = ({
    //     if (1 == 0)
    //         2;
    //     1;
    // });


    // void reading(const char input_file_path[], const char output_file_path[], string** full_text, int* line_count) {

//     string* buf = read_buffer("input_file_path");
//     *line_count = count_lines(buf->buffer);

//     if (errno) {
//         perror(" Damn fopen: ");
//         return EXIT_FAILURE;
//     }


//     *full_text = create_arr_of_splited_lines(buf, line_count);
// }