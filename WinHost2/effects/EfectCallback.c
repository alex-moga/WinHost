/*
 * RainbowEfect.c
 *
 * Created: 29.10.2017 12:36:49
 *  Author: Alex
 */ 

#include "EffectCallback.h"

extern RgbColor g_leds[LED_COUNT];
static HsvColor g_led_colors[LED_COUNT];

static uint8_t up_down_sat[LED_COUNT];
static uint8_t counter;
static uint8_t heat[LED_COUNT];

void rainbow_init_effect(S_STEP_PARAMS *step_params) {
	//Расчет величины разницы тона в зависимости от колличества светодиодов
	uint16_t delta_hue = MAX_HUE / LED_COUNT;
	if(delta_hue < 128) {
		delta_hue = 128;
	}
	//Установка начального цвета
	HsvColor hsvc;
	unpack_color(step_params->packed_params, &hsvc);
	//Загрузка начальных цветов в буфер
	RgbColor rgbc;	
	for(uint8_t n = 0; n < LED_COUNT; n++ ) {
		g_led_colors[n] = hsvc;
		toRgb(hsvc, &rgbc);
		set_color(n, rgbc);
		hsvc.hue += delta_hue;
		if(hsvc.hue > MAX_HUE) {
			hsvc.hue = hsvc.hue - MAX_HUE;
		}
		up_down_sat[n] = n % 2;
	}
	send_buffer();
	//Установка функции обработчика шага, числа шагов и групповой задержки
	step_params->step_callback = rainbow_step_callback;
	step_params->n_eff_step_count = MAX_HUE;
	refresh();
}

void rainbow_step_callback() {
	RgbColor rgbc;	
	for(uint8_t n = 0; n < LED_COUNT; n++ ) {
		g_led_colors[n].hue += 2;
		if(g_led_colors[n].hue > MAX_HUE) {
			g_led_colors[n].hue = 0;
		}
		if((counter % 2) == 0) {
			if(up_down_sat[n] && (++g_led_colors[n].sat > 254)) {
					up_down_sat[n] = 0;
			} else if(!up_down_sat[n] && (--g_led_colors[n].sat < 50)) {
					up_down_sat[n] = 1;
			}
		}
		if((counter % 20) == 0) {
			g_led_colors[n].val = rand8();
			
		}
		toRgb(g_led_colors[n], &rgbc);
		set_color(n, rgbc);
	}
	counter++;
	send_buffer();
	refresh();
	_delay_us(50);
}

RgbColor rgbc_white = {255, 255, 255};
RgbColor rgbc_none = {0, 0, 0};

void init_strobo_flash(S_STEP_PARAMS *step_params) {
	for(uint8_t n = 0; n < LED_COUNT; n++ ) {
			set_color(n, rgbc_none);
	}
	send_buffer();
	refresh();
	
	step_params->step_callback = strobo_flash_step;
	step_params->n_eff_step_count = 96;
}

void strobo_flash_step() {
	uint8_t led_indx = random8(LED_COUNT);
	
	for(uint8_t n = 0; n < 4; n++) {
		set_color(led_indx, rgbc_white);
		send_buffer();
		refresh();
		_delay_ms(10);
		
		set_color(led_indx, rgbc_none);
		send_buffer();
		refresh();
		_delay_ms(10);
	}
}

void init_fire_effect(S_STEP_PARAMS *step_params) {
	step_params->step_callback = fire_effect_step;
	step_params->n_eff_step_count = 288;
}

static const RgbColor g_flamePallete[16] = {
	{0, 0, 0}, {0x66, 0, 0}, {0x99, 0, 0}, {0xCC, 0, 0}, {0xFF, 0, 0},
	{0xFF, 0x33, 0}, {0xFF, 0x66, 0}, {0xFF, 0x99, 0}, {0xFF, 0xCC, 0}, {0xFF, 0xFF, 0},
	{0xFF, 0xFF, 0x33}, {0xFF, 0xFF, 0x66}, {0xFF, 0xFF, 0x99}, {0xFF, 0xFF, 0xCC}, {0xFF, 0xFF, 0xFF}
};

void fire_effect_step() {
	//Слегка охлаждаем каждую ячейку на произвольную величину
	for( int i = 0; i < LED_COUNT; i++) {
		heat[i] = qsub8( heat[i],  random8ml(0, ((COOLING * 10) / LED_COUNT) + 2));
	}
	
	//Имитируем перемещение тепла вверх
	for( int k= LED_COUNT - 1; k >= 2; k--) {
		heat[k] = (heat[k - 1] + heat[k - 2] ) / 3;
	}
	
	//Произвольно индуцируем новые горячие точки ближе к низу
	if( rand8() < SPARKING ) {
		int y = random8(LED_COUNT);
		heat[y] = qadd8( heat[y], random8ml(160, 255) );
	}
	
	//Теперь маппируем полученные значения температуры на цвет
	for( int n = 0; n < LED_COUNT; n++) {
		uint8_t colorindex = scale8(heat[n], 240);
		RgbColor flame_color = colorFromPallete(colorindex, g_flamePallete);	
		set_color(n, flame_color);
	}
	
	send_buffer();
	refresh();
	
	_delay_ms(70);
}

void init_color_swap(S_STEP_PARAMS *step_params) {
	//init default value and saturation
	for(uint8_t n = 0; n < LED_COUNT; n++) {
		g_led_colors[n].sat = 255;
		g_led_colors[n].val = 255;
	}
	step_params->step_callback = color_swap_step;
	step_params->n_eff_step_count = 255*10;
}

enum COLOR_SWAP_STATE {
	GEN_RAND_COLOR,
	GOTO_WHITE,
	GOTO_COLOR
};

static uint8_t g_sat_counter = 0;
static enum COLOR_SWAP_STATE g_swapc_state = GEN_RAND_COLOR;

void my_delay_us(uint16_t n)
{
	while(n--)
	{
		_delay_us(1);
	}
}

void color_swap_step() {
	RgbColor rgbc;
	switch(g_swapc_state) {
		case GEN_RAND_COLOR:
			//Generate random hue
			for(uint8_t n = 0; n < LED_COUNT; n++) {
				g_led_colors[n].hue = random16(MAX_HUE);
				toRgb(g_led_colors[n], &rgbc);
				set_color(n, rgbc);
			}
			send_buffer();
			refresh();
			g_swapc_state = GOTO_WHITE;
			g_sat_counter = 255;
		break;
	case GOTO_WHITE:
			g_sat_counter -= 3;
			if(g_sat_counter > 0) {
				for(uint8_t n = 0; n < LED_COUNT; n++) {
					g_led_colors[n].sat = g_sat_counter;
					toRgb(g_led_colors[n], &rgbc);
					set_color(n, rgbc);
				}
				send_buffer();
				refresh();
			} else {
				g_swapc_state = GOTO_COLOR;
			}
	break;
	case GOTO_COLOR:
			g_sat_counter += 3;
			if(g_sat_counter < 255) {
				for(uint8_t n = 0; n < LED_COUNT; n++) {
					g_led_colors[n].sat = g_sat_counter;
					toRgb(g_led_colors[n], &rgbc);
					set_color(n, rgbc);
				}
				send_buffer();
				refresh();
			} else {
				g_swapc_state = GEN_RAND_COLOR;
			}
		break;
	}
	my_delay_us(50);
}

