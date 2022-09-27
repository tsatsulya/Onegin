#pragma once

#include "utilities.h"

int count_lines(char* full_line);

int count_symbols(FILE* file);

buffer* read_buffer(const char file_name[], int* line_count);

line* build_array_of_lines (buffer* buf, int line_count);

void fprint_ (const line str[], int size, FILE* file);