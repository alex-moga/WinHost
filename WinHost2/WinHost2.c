/*
 * WinHost2.c
 *
 * Created: 28.10.2017 21:05:10
 *  Author: Alex
 */ 

#include <avr/io.h>
#include "effects/EffectCallback.h"

HsvColor hsvc;
RgbColor rgbc;
uint8_t buff[64];

uint8_t a;

//255, 127, 130
extern RgbColor g_leds[LED_COUNT];

int main(void)
{
	init_led_driver();
	build_effect_pipeline();
	
    while(1)
    {
        run_pipeline();
    }
}