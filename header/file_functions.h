#pragma once
#include <errno.h>
#include <stdio.h>
#include "debug.h"
#include <assert.h>
#include "types.h"
#include "string_functions.h"
#include <stdlib.h>

int count_lines(char* full_line);

int count_symbols(FILE* file);

string* read_buffer(const char file_name[]);

string* create_arr_of_splited_lines (string* buf, int line_count);

void fprint_without_blank_lines(FILE* file, const string str[], int size);

void reading(const char input_file_path[], const char output_file_path[], string** full_text, int* line_count);
