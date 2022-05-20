#pragma once

#include "includes.h"

#define LEN(a,b) ((b) - (a) + 1)

struct tagCartHeader {
    uint8_t ucaEntryPoint[4];
    uint8_t ucaNintendoLogo[0x30];
    uint8_t ucaTitle[16];
    int16_t usLicenseeCode;
    uint8_t ucSgbFlag;
    uint8_t ucCartType;
    uint8_t ucRomSize;
    uint8_t ucRamSize;
    uint8_t ucDstCode;
    uint8_t ucOldLicensee;
    uint8_t ucMaskRomVersion;
    uint8_t ucChkSum;
    uint16_t usGlobChkSum;
};

typedef struct {
    uint8_t * ucRomData;
    struct tagCartHeader tRomHeader;
    uint8_t ucPID;
} cartridge_context;

uint8_t cartridge_load(char * f);
cartridge_context * getCartridgeContext(void);