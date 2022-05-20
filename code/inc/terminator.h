#pragma once
#include "includes.h"

#ifdef SOUT
#undef SOUT
#endif

#ifdef SERR
#undef SERR
#endif

#ifndef OUT_STREAM
#define SOUT stdout
#else
#define SOUT OUT_STREAM
#endif

#ifndef ERR_STREAM
#define SERR stderr
#else
#define SERR ERR_STREAM
#endif

typedef enum {
    eTermRegular,
    eTermNoReason,
    eTermNoRom,
    eTermInvalidRom,
    eTermRomLoad,
    eTermCartridgeLoad,
    eTermNoArgs,
} E_TermReason;

void terminate(E_TermReason e);
void messageOut(int8_t * m);
void messageErr(int8_t * m);
uint8_t registerContext(void * ptr);
void eradicateContext(uint8_t pid);