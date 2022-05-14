#include "includes.h"
#include <stdarg.h>

#ifdef DEBUGGING_ON
void util_debug(char * f, ...) {
    fprintf(stdout, "DEBUGGING...\n");
    va_list a;
    va_start(a,f);
    vfprintf(stdout,f,a);
    va_end(a);
}
#else
void util_debug(char * s, ...) {
}
#endif

uint8_t util_strlen(int8_t * s) {
    uint8_t l = 0;
    while (*s++ != '\0' && ++l);
    return l;
}

void util_swap(uint16_t * p) {
    *p = ((*p & 0x00ff) << 8) | ((*p & 0xff00) >> 8);
}