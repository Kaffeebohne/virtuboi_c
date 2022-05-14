
#include <string.h>     // memset
#include <time.h>       // clock_t, clock(), CLOCKS_PER_SEC
#include <unistd.h>     // sleep()

#include "dmg_emu.h"
#include "cartridge.h"

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
    T_Register tRegs[6];
    uint32_t uTickCnt;
} emu_context;

static void _cpu_setup() {
    emu_context.tRegs[0].w = 0x0100; //AF
    emu_context.tRegs[0].w = 0xff13; //BC
    emu_context.tRegs[0].w = 0x00c1; //DE
    emu_context.tRegs[0].w = 0x8403; //HL
    emu_context.tRegs[0].w = 0x0100; //PC
    emu_context.tRegs[0].w = 0xfffe; //SP
}

uint8_t emu_run(int8_t ** arg) {
    emu_context.ucPID = registerContext(&emu_context);
    cartridge_context * cartridge;
    if (*arg == NULL)
        terminate(eTermNoRom);

    if (!cartridge_load(*arg))
        terminate(eTermCartridgeLoad);

    cartridge = getCartridgeContext();
    cartridge->ucPID = registerContext(cartridge);

    _cpu_setup();
    emu_context.ucEmuFlags = (1 << eFIsRunning);
    emu_context.uTickCnt = 0;

    while (emu_context.ucEmuFlags & 1<<eFIsRunning) {

    }

    terminate(eTermRegular);
}