#include "dmg_emu.h"
#include "cartridge.h"

uint8_t emu_run(int8_t ** arg) {
    cartridge_context * cartridge;
    if (*arg == NULL)
        terminate(eTermNoRom);

    if (!cartridge_load(*arg))
        terminate(eTermCartridgeLoad);

    cartridge = getCartridgeContext();
}