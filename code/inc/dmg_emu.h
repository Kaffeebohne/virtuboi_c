#pragma once
#include "includes.h"

typedef struct {
    int8_t * sRomName;
    float fClk; // 4.193403MHz
    float fFPS; // 59.7
    uint8_t ucCfgFlags;
} T_DMG_CONFIG;

uint8_t emu_run(T_DMG_CONFIG * ptConfig);