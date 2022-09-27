#include "../header/debug.h"

void debug_msg(int mode, const char* format, ...) {
    if (mode<=GLOBAL_DEBUG_MODE) {//??????????????????????????????
        int d; 
        double f;
        char* s;
        va_list factor;         // указатель на необязательный параметр
        va_start(factor, format);   // устанавливаем указатель
        
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
