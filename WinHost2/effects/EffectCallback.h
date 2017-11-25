/*
 * RainbowEffect.h
 *
 * Created: 29.10.2017 15:10:51
 *  Author: Alex
 */ 

#ifndef RAINBOWEFFECT_H_
#define RAINBOWEFFECT_H_

#include "../pipeline/Pipeline.h"
#include "../pipeline/PipelineData.h"
#include "../math/math.h"
#include "EffectParams.h"

#define EFFECT_STEP_LENGTH_MS 7000
#define COOLING  55
#define SPARKING 120

void rainbow_init_effect(S_STEP_PARAMS *p_pipeline_step);
void rainbow_step_callback();

void init_strobo_flash(S_STEP_PARAMS *step_params);
void strobo_flash_step();

void init_fire_effect(S_STEP_PARAMS *step_params);
void fire_effect_step();

void init_color_swap(S_STEP_PARAMS *step_params);
void color_swap_step();

#endif /* RAINBOWEFFECT_H_ */