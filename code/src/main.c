#ifndef _GB_MODEL
#define _GB_MODEL DMG
#endif

#if _GB_MODEL == DMG
#include "dmg_emu.h"
#endif

#ifdef DEBUGGING_ON
static uint8_t ucSwitchDebug = DEBUGGING_ON;
#else
static uint8_t ucSwitchDebug = 0;
#endif

#include <unistd.h> // getopt, optarg, optopt
int main(int argc, char ** argv) {
    T_DMG_CONFIG cfg = {
        .fClk = 4.193403f, //MHz
        .fFPS = 59.7f,
        .ucCfgFlags = 0,
        .sRomName = NULL
    };
    int o;
    cfg.ucCfgFlags = ucSwitchDebug;

    if (argc == 1)
        terminate(eTermNoArgs);

    while((o = getopt(argc, argv, ":dr:")) != -1)
        switch (o) {
            case 'd':
                cfg.ucCfgFlags |= 1;
                break;
            case 'D':
                cfg.ucCfgFlags &= ~1;
            case 'r':
                // rom file
                cfg.sRomName = optarg;
                break;
        }

    return emu_run(&cfg);
}