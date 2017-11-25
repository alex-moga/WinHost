/*
 * CFile1.c
 *
 * Created: 10.11.2017 10:52:37
 *  Author: Alex
 */ 

#include "EffectParams.h"

void pack_color(uint8_t *p_packed_params, HsvColor hsvc) {
	uint8_t offset = HSVC_PARAM_OFFSET;
	
	memcpy(p_packed_params, (const void *)&hsvc.hue, sizeof(uint16_t));
	offset += sizeof(uint16_t);
	memcpy(p_packed_params + offset, (const void *)&hsvc.sat, sizeof(uint8_t));
	offset += sizeof(uint8_t);
	memcpy(p_packed_params + offset, (const void *)&hsvc.val, sizeof(uint8_t));
}

void unpack_color(uint8_t *p_packed_params, HsvColor *p_hsvc) {
	uint8_t offset = HSVC_PARAM_OFFSET;
	
	memcpy(&p_hsvc->hue, (const void *)p_packed_params, sizeof(uint16_t));
	offset += sizeof(uint16_t);
	memcpy(&p_hsvc->sat, (const void *)p_packed_params + offset, sizeof(uint8_t));
	offset += sizeof(uint8_t);
	memcpy(&p_hsvc->val, (const void *)p_packed_params + offset, sizeof(uint8_t));
}