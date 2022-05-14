#include <string.h>

#include "cartridge.h"
#include "cartridgeLookup.h"


// M E M B E R
static cartridge_context ctx;

// P R O T O T Y P E S
static uint8_t _verifyHeader(void);
static uint8_t getLicenseeCode(void);
static uint8_t chkSumHeader(void);

// I M P L E M E N T A T I O N S
uint8_t _verifyHeader(void) {
    uint8_t valid = 1;
    uint8_t value;
    // validate fields in cartridge and verify checksum
    value = chkSumHeader();
    valid &= value == ctx.tRomHeader.ucChkSum;
    valid &= ctx.tRomHeader.ucRomSize <= 0x08;
    valid &= ctx.tRomHeader.ucRamSize <= 0x05;
    valid &= ctx.tRomHeader.ucMaskRomVersion == 0x00;

    return valid;
}

uint8_t getLicenseeCode(void) {
    uint8_t result = 0x00;
    uint8_t tmp = ctx.tRomHeader.usLicenseeCode >> 8 & 0xff;
    if (tmp >= 0x30 && tmp <= 0x39)
        result = tmp - 0x30;
    else
        result = tmp - 0x41;

    tmp = ctx.tRomHeader.usLicenseeCode & 0xff;
    
    if (tmp >= 0x30 && tmp <= 0x39)
        result |= (tmp - 0x30) << 4;
    else
        result |= (tmp - 0x41) << 4;

    return result;
}

static uint8_t chkSumHeader(void) {
    uint8_t x = 0;
    uint16_t i = 0x0134;
    while (i <= 0x014c)
        x -= ctx.ucRomData[i++] + 1;
    return x;
    /*
   uint16_t x = 0, i, o;
   for (i=0x0134; i<=0x014c; i++) {
       x = x - ctx.ucRomData[i] - 1;
   }
   return x & 0xff;
    */
}

uint8_t cartridge_load(char * f) {
    uint8_t valid = 0;
    uint32_t read;

    memset((void *) ctx.tRomHeader.ucaTitle, 0, 16);

    FILE * fp = fopen(f, "r");
    if (fp == NULL)
        terminate(eTermRomLoad);

    fseek(fp, 0x0100, SEEK_SET);
    read = fread((void *) &ctx.tRomHeader, 1, sizeof(struct tagCartHeader), fp);
    valid = read == sizeof(struct tagCartHeader);

    read = util_strlen(f);
    ctx.sRomName = (int8_t *) malloc(read + 1);
    memset((void *) ctx.sRomName, 0, read + 1);
    ctx.sRomName = (char * ) memcpy((void *) ctx.sRomName, (void *) f, read);

    read = 32 << ctx.tRomHeader.ucRomSize * 1 << 0x0a;
    ctx.ucRomData = (uint8_t *) malloc(read);
    memset((void *) ctx.ucRomData, 0, read);
    fseek(fp, 0, SEEK_SET);
    read = fread((void *) ctx.ucRomData, 1, read, fp);
    valid &= read == (32 << ctx.tRomHeader.ucRomSize * 1 << 0x0a);

    util_swap(&ctx.tRomHeader.usGlobChkSum);
    return valid && _verifyHeader();
}

cartridge_context * getCartridgeContext(void) {
    return &ctx;
}