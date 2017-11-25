/*
 * PipelineData.h
 *
 * Created: 07.11.2017 9:04:57
 *  Author: Alex
 */ 


#ifndef PIPELINEDATA_H_
#define PIPELINEDATA_H_

#define PACKED_PARAM_BUFF_LEN	6

#define HSVC_PARAM_OFFSET		0

enum EffectType {
	RAINBOW_EFF,
	FLASH_EFF,
	FLAME_EFF,
	COLOR_SWAP_EFF	
};

typedef void (*STEP_CALLBACK)();

typedef struct {
	uint8_t packed_params[PACKED_PARAM_BUFF_LEN];
	STEP_CALLBACK step_callback;
	uint16_t n_eff_step_count;
} S_STEP_PARAMS;

typedef void (*INIT_CALLBACK)(S_STEP_PARAMS  *p_pipeline_step);

typedef struct {
	INIT_CALLBACK init_callback;
	S_STEP_PARAMS step_params;
	enum EffectType effect_type;	
} S_EFF_PARAMS;

#endif /* PIPELINEDATA_H_ */