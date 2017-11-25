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
	uint8_t step_count;										//����� ����� �������
	uint8_t step_pos;										//������� ������� �������
	uint8_t led_count;										//����� ����������� � �������	?
	void (*p_step_callback)(void *p_eff_descr);				//���������� ���� �������
} EffectDescriptor;

#endif /* EFFECTS_H_ */