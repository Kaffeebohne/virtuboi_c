#include "includes.h"
#include <stdarg.h>

static T_UTIL_CFG * cfg;

void _util_debug_on(char * f, ...) {
    fprintf(stdout, "DEBUGGING...\n");
    va_list a;
    va_start(a,f);
    vfprintf(stdout,f,a);
    va_end(a);
}
void _util_debug_off(char * s, ...) {
}

void (*_util_debug[])(char * s, ...) = {
    _util_debug_off, _util_debug_on
};

void util_debug(char * s, ...) {
    va_list a;
    _util_debug[cfg->bFlagDebugging](s,a);
}

uint8_t util_strlen(int8_t * s) {
    uint8_t l = 0;
    while (*s++ != '\0' && ++l);
    return l;
}

void util_swap(uint16_t * p) {
    *p = ((*p & 0x00ff) << 8) | ((*p & 0xff00) >> 8);
}

void util_init(T_UTIL_CFG * ptConfig) {
    cfg = ptConfig;
}