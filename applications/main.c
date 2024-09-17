/*
 * Copyright (c) 2021 hpmicro
 *
 * Change Logs:
 * Date         Author          Notes
 * 2021-08-13   Fan YANG        first version
 *
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "rtt_board.h"
#include <drv_gpio.h>
#include "main.h"

void thread_entry(void *arg);


int main(void)
{
    static uint32_t led_thread_arg = 0;
    rt_thread_t led_thread = rt_thread_create("led_th", thread_entry, &led_thread_arg, 1024, 1, 10);
    rt_thread_startup(led_thread);

    return 0;
}


void force_pwm_out(pwm_output_type_t force_output){
    pwm_config_force_cmd_timing(HPM_PWM0, pwm_force_immediately);
    pwm_enable_pwm_sw_force_output(HPM_PWM0, BOARD_BLDC_WH_PWM_OUTPIN);
    pwm_set_force_output(HPM_PWM0,
                         PWM_FORCE_OUTPUT(BOARD_BLDC_WH_PWM_OUTPIN, force_output));
    pwm_enable_sw_force(HPM_PWM0);
}

void disable_force_pwm_out(){
    pwm_disable_sw_force(HPM_PWM0);
    pwm_disable_pwm_sw_force_output(HPM_PWM0, BOARD_BLDC_WH_PWM_OUTPIN);
}

void thread_entry(void *arg)
{
    rt_pin_mode(APP_LED0_PIN_NUM, PIN_MODE_OUTPUT);
//    rt_pin_mode(UL_PIN_NUM,PIN_MODE_OUTPUT_OD);
//    rt_pin_mode(UH_PIN_NUM,PIN_MODE_OUTPUT_OD);
//    rt_pin_mode(VL_PIN_NUM,PIN_MODE_OUTPUT_OD);
//    rt_pin_mode(VH_PIN_NUM,PIN_MODE_OUTPUT_OD);
//    rt_pin_mode(WH_PIN_NUM,PIN_MODE_OUTPUT_OD);
//    rt_pin_mode(WL_PIN_NUM,PIN_MODE_OUTPUT_OD);
//    rt_pin_mode(SD_PIN_NUM,PIN_MODE_OUTPUT_OD);
//    rt_pin_write(SD_PIN_NUM,0);
    init_pwm_pins(PWM);
    generate_edge_aligned_waveform();
    while(1){
//        rt_thread_mdelay(50);
//        rt_pin_write(UH_PIN_NUM,0);
//        rt_pin_write(UL_PIN_NUM,0);
//        rt_pin_write(VH_PIN_NUM,0);
//        rt_pin_write(VL_PIN_NUM,0);
//        rt_pin_write(WH_PIN_NUM,0);
//        rt_pin_write(WL_PIN_NUM,0);
//        rt_thread_mdelay(50);
//        rt_pin_write(UH_PIN_NUM,0);
//        rt_pin_write(UL_PIN_NUM,0);
//        rt_pin_write(VH_PIN_NUM,0);
//        rt_pin_write(VL_PIN_NUM,0);
//        rt_pin_write(WH_PIN_NUM,0);
//        rt_pin_write(WL_PIN_NUM,0);
        rt_pin_write(APP_LED0_PIN_NUM, APP_LED_ON);
        rt_thread_mdelay(500*3);
        rt_pin_write(APP_LED0_PIN_NUM, APP_LED_OFF);
        rt_thread_mdelay(500*3);


    }
}
