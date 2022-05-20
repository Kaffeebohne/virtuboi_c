#pragma once

#include "includes.h"

typedef void(*pFInst)(void *, void *);

typedef enum {
    eImpl,
    eAR8,
    eAR16,
    eAI8,
    eAI16,
} E_ADDR_TYPE;

typedef struct {
    int8_t sMnemonic[8];
    uint8_t ucBytes :4;
    uint8_t ucCycles :4;
    E_ADDR_TYPE eAdr[2];
    pFInst pf;
} T_INSTRUCTION;

enum {
    bFlagZero = 1 << 7,
    bFlagNegative = 1 << 6,
    bFlagHalf = 1 << 5,
    bFlagCarry = 1 << 4,
};

void nop(void *, void*);
void hlt(void *, void*);
void stp(void *, void*);
void ldr(void *, void*);
void ldi(void *, void*);
void str(void *, void*);
void sti(void *, void*);
void inc(void *, void*);
void dec(void *, void*);
void rlca(void *, void*);
void rla(void *, void*);
void rrca(void *, void*);
void rra(void *, void*);
void daa(void *, void*);
void scf(void *, void*);
void cpl(void *, void*);
void ccp(void *, void*);
void add(void *, void*);
void sub(void *, void*);
void jr(void *, void*);
void adc(void *, void*);
void sbc(void *, void*);
void lan(void *, void*);
void lor(void *, void*);
void lxr(void *, void*);
void lcp(void *, void*);
void ret(void *, void*);
void reti(void *, void*);
void call(void *, void*);
void push(void *, void*);
void pop(void *, void*);
void jp(void *, void*);
void di(void *, void*);
void ei(void *, void*);
void rst(void *, void*);
void rlc(void *, void*);
void rl(void *, void*);
void rrc(void *, void*);
void rr(void *, void*);
void sla(void *, void*);
void sra(void *, void*);
void swap(void *, void*);
void srl(void *, void*);
void bit(void *, void*);
void set(void *, void*);
void res(void *, void*);
