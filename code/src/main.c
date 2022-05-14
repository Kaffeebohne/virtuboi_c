#ifndef _GB_MODEL
#define _GB_MODEL DMG
#endif

#if _GB_MODEL == DMG
#include "dmg_emu.h"
#endif

int main(int argc, char ** argv) {
    (void) argc;
    // TODO optarg command line arguments before
    //      handing over the rom location
    return emu_run((int8_t **) ++argv);
}