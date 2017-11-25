/*
 * math.h
 *
 * Created: 13.11.2017 17:21:19
 *  Author: Alex
 */ 

#ifndef MATH_H_
#define MATH_H_

#include <avr/io.h>

uint8_t rand8();
//uint8_t rand3();
uint16_t rand16();

uint8_t static inline qsub8( uint8_t i, uint8_t j) {
	int t = i - j;
	if( t < 0) {
		t = 0;
	}
	return t;
}

uint8_t static inline random8(uint8_t lim)
{
	uint8_t r = rand8();
	r = (r*lim) >> 8;
	return r;
}

uint16_t static inline random16(uint16_t lim)
{
	uint32_t r = rand16();
	r = (r*lim) >> 16;
	return r;
}

uint8_t static inline random8ml(uint8_t min, uint8_t lim)
{
	uint8_t delta = lim - min;
	uint8_t r = random8(delta) + min;
	return r;
}

uint8_t static inline scale8(uint8_t i, uint8_t scale){
	return ((uint16_t)i * (uint16_t)(scale) ) >> 8;	
}

uint8_t static inline qadd8(uint8_t i, uint8_t j) {
	uint8_t t = i + j;
	if( t > 255) {
		t = 255;
	}
	return t;
};

#endif /* MATH_H_ */