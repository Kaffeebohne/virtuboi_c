#include "includes.h"

uint8_t _strlen(int8_t * s) {
    uint8_t l = 0;
    while (++l && *s++ != '\0');
    return l;
}