/*
 * Pipeline.c
 *
 * Created: 04.11.2017 16:46:16
 *  Author: Alex
 */ 

#include "Pipeline.h"

S_EFF_PARAMS eff_params[EFFECT_COUNT];
static uint8_t g_eff_indx = 0;
static uint8_t g_total_effects = 0;

void build_effect_pipeline() {	
	//Установка эффекта цвета
	eff_params[g_total_effects].init_callback = init_color_swap;
	eff_params[g_total_effects].effect_type = COLOR_SWAP_EFF;
	g_total_effects++;
	
	//Установка эффекта пламени
	eff_params[g_total_effects].init_callback = init_fire_effect;
	eff_params[g_total_effects].effect_type = FLASH_EFF;
	g_total_effects++;
	
	//Установка параметров эффекта Rainbow 
	HsvColor hsvc = {0, 200, 255};
	pack_color(eff_params[g_total_effects].step_params.packed_params, hsvc);
	eff_params[g_total_effects].init_callback = rainbow_init_effect;
	eff_params[g_total_effects].effect_type = RAINBOW_EFF;
	g_total_effects++;
	
	//Установка параметров эффекта Flash  
	eff_params[g_total_effects].init_callback = init_strobo_flash;
	eff_params[g_total_effects].effect_type = FLASH_EFF;
	g_total_effects++;
}

void run_pipeline() {
	//Чтение начальных параметров
	S_EFF_PARAMS *p_eff_params = &eff_params[g_eff_indx];
	//Инициализация эффекта
	p_eff_params->init_callback(&p_eff_params->step_params);
	//Отображение шага эффекта
	for(uint16_t ic = 0; ic < p_eff_params->step_params.n_eff_step_count; ic++) {
		p_eff_params->step_params.step_callback();
	}
	//Переход к следующему эффекту
	if(++g_eff_indx == g_total_effects) {
		g_eff_indx = 0;
	}
}