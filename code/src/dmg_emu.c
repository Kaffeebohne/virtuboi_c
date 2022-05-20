
#include <string.h>     // memset
#include <time.h>       // clock_t, clock(), CLOCKS_PER_SEC
#include <unistd.h>     // sleep()

#include "dmg_emu.h"
#include "cartridge.h"
#include "mmu.h"

#define GET_LO(d16)     ((d16) & 0x00ff)
#define GET_HI(d16)     ((d16) & 0xff00) >> 8
#define SET_LO(d16,d8)  (((d16) & 0xff00) | (d8))
#define SET_HI(d16,d8)  (((d16) & 0x00ff) | ((d8) << 8))
#define SET_B8(d8,b,d1) ((d8) & ~(1 << (b)) | (d1) << (b))

enum {
    eRegAF = 0,
    eRegBC,
    eRegDE,
    eRegHL,
    eRegPC,
    eRegSP,
    eNbrRegs
};

typedef union {
    struct {
        uint8_t bLo;
        uint8_t bHi;
    };
    uint16_t w;
} T_Register;

enum {
    eFIsRunning = 0,
    eFIsPaused,
    eFIsStepping,

};

struct {
    uint8_t ucPID;
    uint8_t ucEmuFlags;
    T_Register tRegs[eNbrRegs];
    uint32_t uTickCnt;
    // uint8_t 
    uint8_t ucReadByte :2;
    uint8_t ucTCycles :3;
    uint8_t ucUnused :3;
} emu_context;

static T_DMG_CONFIG *tConfig;

static void _cpu_setup() {
    emu_context.tRegs[eRegAF].w = 0x0100; //AF
    emu_context.tRegs[eRegBC].w = 0xff13; //BC
    emu_context.tRegs[eRegDE].w = 0x00c1; //DE
    emu_context.tRegs[eRegHL].w = 0x8403; //HL
    emu_context.tRegs[eRegPC].w = 0x0100; //PC
    emu_context.tRegs[eRegSP].w = 0xfffe; //SP
}

static void _tick(void) {
    ++emu_context.uTickCnt;
}

static void _fetch() {
    mmu_read(emu_context.tRegs[eRegPC].w);
}

uint8_t emu_run(T_DMG_CONFIG * ptConfig) {
    emu_context.ucPID = registerContext(&emu_context);
    cartridge_context * cartridge;
    tConfig = ptConfig;

    if (!cartridge_load(tConfig->sRomName))
        terminate(eTermCartridgeLoad);

    cartridge = getCartridgeContext();
    cartridge->ucPID = registerContext(cartridge);

    _cpu_setup();
    emu_context.ucEmuFlags = (1 << eFIsRunning);
    emu_context.uTickCnt = 0;

    while (emu_context.ucEmuFlags & 1<<eFIsRunning) {
        _fetch();
        _tick();
    }

    terminate(eTermRegular);
}