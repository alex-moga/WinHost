/*
 * EffectParams.h
 *
 * Created: 10.11.2017 10:53:23
 *  Author: Alex
 */ 


#ifndef EFFECTPARAMS_H_
#define EFFECTPARAMS_H_

#include "../color/color.h"
#include "../pipeline/PipelineData.h"

void pack_color(uint8_t *p_packed_params, HsvColor hsvc);
void unpack_color(uint8_t *p_packed_params, HsvColor *p_hsvc);

#endif /* EFFECTPARAMS_H_ */