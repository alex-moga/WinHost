/*
 * Pipeline.h
 *
 * Created: 04.11.2017 15:53:39
 *  Author: Alex
 */ 

#ifndef PIPELINE_H_
#define PIPELINE_H_

#include "../drivers/ws2811.h"
#include "../effects/EffectCallback.h"

#define EFFECT_COUNT 2

void build_effect_pipeline();
void run_pipeline();
void init_strobo_flash();

#endif /* PIPELINE_H_ */