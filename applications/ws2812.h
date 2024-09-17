//
// Created by MacGuffin on 2024/9/17.
//

#ifndef RTTHREAD_WS2812_H
#define RTTHREAD_WS2812_H
#include "hpm_pwm_drv.h"
#include "board.h"
void generate_edge_aligned_waveform(void);
#define PWM HPM_PWM0
#define PWM_OUTPUT_PIN BOARD_BLDC_WH_PWM_OUTPIN
#define TRGM HPM_TRGM0
#define TRGM_PWM_OUTPUT HPM_TRGM0_OUTPUT_SRC_PWM0_SYNCI
#endif //RTTHREAD_WS2812_H
