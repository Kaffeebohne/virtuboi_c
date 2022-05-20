#pragma once
#include "includes.h"

typedef struct {
    uint8_t bFlagDebugging :1;
    uint8_t bFlagUnused :7;
} T_UTIL_CFG;

uint8_t util_strlen(int8_t * s);
void util_debug(char * s, ...);
void util_swap(uint16_t * p);