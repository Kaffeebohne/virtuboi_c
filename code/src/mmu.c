#include "mmu.h"

// should act as the memory controller. probably all read/write
// goes through this module. Means also here must the future
// debugger and jit memory manipulator be attached

uint8_t mmu_read(uint16_t a) {
    (void) a;
    return 0;
}

void mmu_write(uint16_t a, uint8_t d) {
    (void) a;
    (void) d;
}

uint8_t mmu_setup(T_MMU_CONFIG * ptConfig) {
    (void) ptConfig;
    return 1;
}