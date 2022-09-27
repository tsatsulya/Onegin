#pragma once
#include <errno.h>
#include <stdio.h>
#include "debug.h"
#include <assert.h>
#include "types.h"

#include <stdlib.h>

//#include "debug.h"
// TODO: reconsider name of this file (especially "work with" part :)

int count_lines(char* full_line);

int count_symbols(FILE* file);

string* read_buffer(const char file_name[], int* line_count);

string* create_arr_of_splited_lines (string* buf, int line_count);

void fprint_without_blank_lines(const string str[], int size, FILE* file);