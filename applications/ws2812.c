//
// Created by MacGuffin on 2024/9/17.
//

#include "ws2812.h"
#include "hpm_pwm_drv.h"
#include "hpm_trgm_drv.h"
#include "rtthread.h"


#define TEST_LOOP (799999)

void reset_pwm_counter(void)
{
    pwm_enable_reload_at_synci(PWM);
    //trgm_output_update_source(TRGM, TRGM_PWM_OUTPUT, 1);
    trgm_output_update_source(TRGM, TRGM_PWM_OUTPUT, 0);
}

void generate_edge_aligned_waveform(void){
    uint32_t reload = 799999;
    uint32_t duty, duty_step;
    bool increase_duty_cycle = true;
    uint8_t cmp_index = 0;
    pwm_config_t pwm_config = {0};
    pwm_cmp_config_t cmp_config[2] = {0};
    pwm_stop_counter(PWM);
    reset_pwm_counter();
    pwm_get_default_pwm_config(PWM, &pwm_config);
    pwm_config.enable_output = true;
    pwm_config.dead_zone_in_half_cycle = 0;
    pwm_config.invert_output = false;
    pwm_set_reload(PWM, 0, reload);
    pwm_set_start_count(PWM, 0, 0);
    cmp_config[0].mode = pwm_cmp_mode_output_compare;
    cmp_config[0].cmp = reload + 1;
    cmp_config[0].update_trigger = pwm_shadow_register_update_on_hw_event;

    cmp_config[1].mode = pwm_cmp_mode_output_compare;
    cmp_config[1].cmp = reload;
    cmp_config[1].update_trigger = pwm_shadow_register_update_on_modify;
    /*
     * config pwm as output driven by cmp
     */
    if (status_success != pwm_setup_waveform(PWM, PWM_OUTPUT_PIN, &pwm_config, cmp_index, &cmp_config[0], 1)) {
        printf("failed to setup waveform\n");
        while(1);
    }
    cmp_config[0].cmp = reload >> 1;
    rt_kprintf("reload is %d\n",reload);
    /*
     * config pwm as reference
     */
    pwm_load_cmp_shadow_on_match(PWM, cmp_index + 2, &cmp_config[1]);

    pwm_start_counter(PWM);
    pwm_issue_shadow_register_lock_event(PWM);
    duty_step = reload / 100;
    duty = reload / 100;
    increase_duty_cycle = true;

    for (uint32_t i = 0; i < TEST_LOOP; i++) {
        if (increase_duty_cycle) {
            rt_kprintf("access if\n");
            if ((duty + duty_step) >= reload) {
                increase_duty_cycle = false;
                continue;
            }
            duty += duty_step;
        } else {
            rt_kprintf("join else\n");
            if (duty <= duty_step) {
                increase_duty_cycle = true;
                continue;
            }
            duty -= duty_step;
        }
        pwm_update_raw_cmp_edge_aligned(PWM, cmp_index, reload - duty);
        rt_thread_mdelay(100);
    }
    //pwm_update_raw_cmp_edge_aligned(PWM, 0, reload/2);
}
