/*
 * ws2811.h
 *
 * Created: 29.10.2017 13:58:24
 *  Author: Alex
 */ 

#ifndef WS2811_H_
#define WS2811_H_

#define F_CPU 8000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#include "../color/color.h"

#define WS2811_PORT		PORTB
#define WS2811_DDR		DDRB
#define WS2811_PIN		0
#define LED_COUNT		7


void init_led_driver();
void refresh();
void send_buffer();
void set_color(uint8_t nled, RgbColor rgbc);


#endif /* WS2811_H_ */