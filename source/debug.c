#include "debug.h" // TODO: fix

void debug_msg(int mode, const char* format, ...) {
    if (mode<=GLOBAL_DEBUG_MODE) {
        int d; // TODO: Please
        double f; // TODO: Be
        char* s; // Better than GNU developers
        va_list factor;         
        va_start(factor, format); 
        
        for(const char *c = format;*c; c++)
        {
            if(*c!='%')
            {
                printf("%c", *c);
                continue;
            }
            switch(*++c) 
            {
                case 'd': 
                    d = va_arg(factor, int);
                    printf("%d", d);
                    break;
                case 'f': 
                    f = va_arg(factor, double);
                    printf("%.2lf", f);
                    break;
                case 's':
                    s = va_arg(factor, char*);
                    printf("%s", s);
                    break;

                default:
                    printf("%c", *c);
            }
        }
        va_end(factor);
    }
    return;
}
