#include "terminator.h"

static const int8_t * const saReasonLU[] = {
    [eTermRegular] = "Beende Programm regulaer.",
    [eTermNoReason] = "Should NEVER happen.",
    [eTermNoRom] = "No ROM file provided.",
    [eTermInvalidRom] = "ROM file invalid.",
    [eTermRomLoad] = "Could not open ROM file.",
    [eTermCartridgeLoad] = "Ups, cartridge loaded incorrect",
};

static void * apCtxs[0x20] = {NULL};

static void _message(FILE * s, int8_t * m) {
    fprintf(s, "%s\n", m);
}

static void _freeAll(void) {
    for (uint8_t i = 0; i < 0x20; ++i)
        eradicateContext(i);
}

void terminate(E_TermReason e) {
    fprintf(SERR, "%2d: %s\n", e, saReasonLU[e]);
    fprintf(stderr, "Freeing all context pointers.\n");
    exit(-e);
}

void messageOut(int8_t * m) {
    _message(SOUT, m);
}

void messageErr(int8_t * m) {
    _message(SERR, m);
}

uint8_t registerContext(void * ptr) {
    uint8_t pid = 0;
    while (apCtxs[pid] != NULL && pid++ < 0x20);
    apCtxs[pid] = ptr;
    return pid;
}

void eradicateContext(uint8_t pid) {
    if (pid < 0x20 && apCtxs[pid] != NULL)
        free(apCtxs[pid]);
}