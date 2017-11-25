/*
 * Color.h
 *
 * Created: 28.10.2017 21:11:28
 *  Author: Alex
 */ 

#ifndef COLOR_H_
#define COLOR_H_

#include <avr/io.h>
#include <string.h>
#include <avr/pgmspace.h>

#include "../math/math.h"

#define MAX_HUE 1530

typedef struct {
	uint8_t red, green, blue;	
} RgbColor;

typedef struct {
	uint16_t hue;
	uint8_t sat;
	uint8_t val;
} HsvColor;

void toRgb(HsvColor hsvc, RgbColor* p_rgbc);
RgbColor colorFromPallete(uint8_t index, const RgbColor* p_pallete);

#endif /* COLOR_H_ */