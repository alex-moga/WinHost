/*
 * effects.h
 *
 * Created: 29.10.2017 10:01:52
 *  Author: Alex
 */ 

#ifndef EFFECTS_H_
#define EFFECTS_H_

#include "../drivers/ws2811.h"

enum ParamType {
	INT8_VAL,
	HSV_COLOR,
	RGB_COLOR
};

typedef struct {
	struct {
		uint8_t *packed_param_buff;
		enum ParamType value;
	} step_params;
	uint8_t step_count;										//Число шагов эффекта
	uint8_t step_pos;										//Текущая позиция эффекта
	uint8_t led_count;										//Число светодиодов в эффекте	?
	void (*p_step_callback)(void *p_eff_descr);				//Обработчик шага эффекта
} EffectDescriptor;

#endif /* EFFECTS_H_ */