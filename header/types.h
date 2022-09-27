#pragma once
typedef struct String {
    
    char* buffer;
    int length;
} string;

typedef int (*cmp_func)( string* A, string* B);
