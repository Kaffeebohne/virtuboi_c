#pragma once
#include "includes.h"

typedef struct {

} T_MMU_CONFIG;

uint8_t mmu_read(uint16_t a);
void mmu_write(uint16_t a, uint8_t d);
uint8_t mmu_setup(T_MMU_CONFIG * ptConfig);