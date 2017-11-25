/*
 * math.c
 *
 * Created: 13.11.2017 17:22:09
 *  Author: Alex
 */ 

#include "math.h"

static uint8_t lfsr8 = 0xAC;
static uint8_t bit8;

uint8_t rand8()
{
	bit8  = ((lfsr8 >> 0) ^ (lfsr8 >> 2) ^ (lfsr8 >> 3) ^ (lfsr8 >> 4) ) & 1;
	return lfsr8 =  (lfsr8 >> 1) | (bit8 << 7);
}

static unsigned short lfsr16 = 0xACE1u;
static unsigned  bit16;

unsigned rand16()
{
	bit16  = ((lfsr16 >> 0) ^ (lfsr16 >> 2) ^ (lfsr16 >> 3) ^ (lfsr16 >> 5) ) & 1;
	return lfsr16 =  (lfsr16 >> 1) | (bit16 << 15);
}

/*static uint8_t lfsr3 = 0x03;
static uint8_t bit3;

uint8_t rand3()
{
	bit3  = ((lfsr3 >> 0) ^ (lfsr3 >> 1)) & 1;
	return lfsr3 =  (lfsr3 >> 1) | (bit3 << 2);
}*/








