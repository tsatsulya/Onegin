#include <stdio.h>
#include <stdlib.h>
int size_of_file(FILE* file);
int number_of_lines(FILE* file);
int main(int argc, char **argv)
{
    puts("\n\n------------------------- begin ------------------------------------\n\n"); 



    int size = 0; //size of file 

    char ** arr;
    int * symbols_in_row; 

    int row_count = 0;
    int buffer = 0;
    FILE *input = fopen("in.txt", "r");

    if (!input) puts("INPUT ERROR");

    rewind(input);

    row_count = number_of_lines(input);
    printf("number of lines: %d \n", row_count);

    arr = (char **)malloc((row_count + 1) * sizeof(char *));
    symbols_in_row = (int *)malloc((row_count + 1) * sizeof(int));


    int i = 0;
    int num = 0;
    while (buffer != EOF) {
        buffer = fgetc(input); 
        ++num;
        if (buffer == '\n') {
            symbols_in_row[i] = num;
            num = 0;
        }
        printf("symbol = %c\n", (char)buffer);
    }
    symbols_in_row[row_count] = num;

    fclose(input);
    puts("\n\n-------------------------- end -------------------------------------\n\n"); 


    
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