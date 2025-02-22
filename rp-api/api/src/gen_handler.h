/**
 * $Id: $
 *
 * @brief Red Pitaya library Generate handler interface
 *
 * @Author Red Pitaya
 *
 * (c) Red Pitaya  http://www.redpitaya.com
 *
 * This part of code is written in C programming language.
 * Please visit http://en.wikipedia.org/wiki/C_(programming_language)
 * for more details on the language used herein.
 */

#ifndef GENERATE_HANDLER_H_
#define GENERATE_HANDLER_H_


#include "rp_cross.h"

int gen_SetDefaultValues();
int gen_Disable(rp_channel_t chanel);
int gen_Enable(rp_channel_t chanel);
int gen_EnableSync(bool enable);
int gen_IsEnable(rp_channel_t channel, bool *value);
int gen_setAmplitude(rp_channel_t channel, float amplitude);
int gen_getAmplitude(rp_channel_t channel, float *amplitude);
int gen_setOffset(rp_channel_t channel, float offset) ;
int gen_getOffset(rp_channel_t channel, float *offset) ;
int gen_setFrequency(rp_channel_t channel, float frequency);
int gen_setFrequencyDirect(rp_channel_t channel, float frequency); // Used for sweepmode
int gen_getFrequency(rp_channel_t channel, float *frequency);
int gen_setSweepStartFrequency(rp_channel_t channel, float frequency);
int gen_getSweepStartFrequency(rp_channel_t channel, float *frequency);
int gen_setSweepEndFrequency(rp_channel_t channel, float frequency);
int gen_getSweepEndFrequency(rp_channel_t channel, float *frequency);
int gen_setPhase(rp_channel_t channel, float phase);
int gen_getPhase(rp_channel_t channel, float *phase);
int gen_setWaveform(rp_channel_t channel, rp_waveform_t type);
int gen_getWaveform(rp_channel_t channel, rp_waveform_t *type);
int gen_setSweepMode(rp_channel_t channel, rp_gen_sweep_mode_t mode);
int gen_getSweepMode(rp_channel_t channel, rp_gen_sweep_mode_t *mode);
int gen_setSweepDir(rp_channel_t channel, rp_gen_sweep_dir_t mode);
int gen_getSweepDir(rp_channel_t channel, rp_gen_sweep_dir_t *mode);
int gen_setArbWaveform(rp_channel_t channel, float *data, uint32_t length);
int gen_getArbWaveform(rp_channel_t channel, float *data, uint32_t *length);
int gen_setDutyCycle(rp_channel_t channel, float ratio);
int gen_getDutyCycle(rp_channel_t channel, float *ratio);
int gen_setRiseTime(rp_channel_t channel, float time);
int gen_getRiseTime(rp_channel_t channel, float *time);
int gen_setFallTime(rp_channel_t channel, float time);
int gen_getFallTime(rp_channel_t channel, float *time);
int gen_setRiseFallMin(rp_channel_t channel, float min);
int gen_setRiseFallMax(rp_channel_t channel, float max);
int gen_getRiseFallMin(rp_channel_t channel, float *min);
int gen_getRiseFallMax(rp_channel_t channel, float *max);
int gen_setGenMode(rp_channel_t channel, rp_gen_mode_t mode);
int gen_getGenMode(rp_channel_t channel, rp_gen_mode_t *mode);
int gen_setBurstCount(rp_channel_t channel, int num);
int gen_getBurstCount(rp_channel_t channel, int *num);
int gen_setBurstRepetitions(rp_channel_t channel, int repetitions);
int gen_getBurstRepetitions(rp_channel_t channel, int *repetitions);
int gen_setBurstPeriod(rp_channel_t channel, uint32_t period);
int gen_getBurstPeriod(rp_channel_t channel, uint32_t *period);

int gen_setTriggerSource(rp_channel_t chanel, rp_trig_src_t src);
int gen_getTriggerSource(rp_channel_t chanel, rp_trig_src_t *src);
int gen_Trigger(uint32_t channel);
int gen_TriggerSync();
int gen_TriggerOnly(uint32_t channel);

int gen_SynchroniseSM();
int gen_ResetChannelSM(rp_channel_t channel);
int triggerIfInternal(rp_channel_t channel);

int synthesize_signal(rp_channel_t channel);
int synthesis_sin(float *data_out,uint16_t buffSize);
int synthesis_sweep(float frequency,float frequency_start,float frequency_end,float phaseRad,rp_gen_sweep_mode_t mode,rp_gen_sweep_dir_t dir,float *data_out,uint16_t buffSize);
int synthesis_triangle(float *data_out,uint16_t buffSize);
int synthesis_arbitrary(rp_channel_t channel, float *data_out, uint32_t * size);
int synthesis_square(float frequency, float riseTime, float fallTime, float *data_out,uint16_t buffSize);
int synthesis_rampUp(float *data_out,uint16_t buffSize);
int synthesis_rampDown(float *data_out,uint16_t buffSize);
int synthesis_DC(float *data_out,uint16_t buffSize);
int synthesis_DC_NEG(float *data_out,uint16_t buffSize);
int synthesis_PWM(float ratio, float *data_out,uint16_t buffSize);

#if defined Z10 || defined Z20_125 || defined Z20 || defined Z20_125_4CH
int gen_setBurstLastValue(rp_channel_t channel, float amplitude);
int gen_getBurstLastValue(rp_channel_t channel, float *amplitude);
#endif

#ifdef Z20_250_12
int gen_setGainOut(rp_channel_t channel,rp_gen_gain_t mode);
int gen_getGainOut(rp_channel_t channel,rp_gen_gain_t *status);
int gen_setEnableTempProtection(rp_channel_t channel, bool enable);
int gen_getEnableTempProtection(rp_channel_t channel, bool *enable);
int gen_setLatchTempAlarm(rp_channel_t channel, bool status);
int gen_getLatchTempAlarm(rp_channel_t channel, bool *status);
int gen_getRuntimeTempAlarm(rp_channel_t channel, bool *status);
#endif

#endif
