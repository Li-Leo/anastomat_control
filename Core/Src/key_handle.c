#include "key_handle.h"
#include "key.h"
#include "hall.h"
#include "motor.h"
#include "timer.h"
#include "flash.h"
#include "msg.h"

bool g_m1m2_switch_is_pressed = false;
bool g_m1_motor_run_is_enable = false;
bool g_m1_motor_run_backward_is_enable = false;

bool g_m2_motor_limit_left_is_enable = false;
bool g_m2_motor_limit_right_is_enable = false;

bool g_r_switch_is_pressed = false;
bool g_l_switch_is_pressed = false;

bool g_m2_motor_run_is_enable = true;

uint16_t g_r_switch_counter;
uint16_t g_l_switch_counter;
uint16_t g_pass_commbination[4];

bool g_is_allow_m1_run = false;

void m2_motor_run_enable(void)
{
    g_m2_motor_run_is_enable = true;
    
    if (key_is_pressed(kKeyRSwitch) == true) {
        m2_motor_run(kForward);
        g_r_switch_is_pressed = true;
    } else if (key_is_pressed(kKeyLSwitch) == true) {
        m2_motor_run(kBackward);
        g_l_switch_is_pressed = true;
    }
}

void on_pressed_delay2s_switch_key(KeyID key, int repeat_count)
{
    HAL_Delay(500);
    m2_motor_stop();

    if (g_is_allow_m1_run == true) {
        g_is_allow_m1_run = false;
        HAL_Delay(500);
        m1_motor_run(kForward);
    } else {
        m2_motor_run(m2_motor_running_dir());
    }

}

void on_released_delay2s_switch_key(KeyID key, int repeat_count)
{
    ;
}

void on_pressed_R_switch_key(KeyID key, int repeat_count)
{
    if (!m2_motor_is_running())
    {
        if (key_is_pressed(kRLimit) == true) {
            m2_motor_run(kBackward);
            return;
        }

        if (key_is_pressed(kLLimit) == true) {
            m2_motor_run(kForward);
            return;
        }

        m2_motor_run(kForward);
    }

}

void on_pressed_L_switch_key(KeyID key, int repeat_count)
{
    if (m1_motor_is_running())
        m1_motor_stop();
    
    if (m2_motor_is_running())
        m2_motor_stop();

    // if (m1m2_switch_is_closed() == false && !m2_motor_is_running() && key_is_pressed(kLLimit) == false && g_m2_motor_run_is_enable == true)
    // {
    //     m2_motor_run(kBackward);
    //     g_l_switch_is_pressed = true;
    // }

    // if (m1m2_switch_is_closed() && g_pass_commbination[0] == 1 && g_pass_commbination[1] == 1) {
    //     g_l_switch_counter++;
        
    //     if (g_l_switch_counter == 1) {
    //         g_pass_commbination[2] = 1;
    //     } else if (g_l_switch_counter == 2) {
    //         g_pass_commbination[3] = 1;
    //     } else {
    //         g_pass_commbination[2] = 0;
    //         g_pass_commbination[3] = 0;
    //     }
    // }
}

void on_released_R_switch_key(KeyID key, int repeat_count)
{
    if (g_r_switch_is_pressed) {
        m2_motor_stop();
        g_r_switch_is_pressed = false;
    }
}

void on_released_L_switch_key(KeyID key, int repeat_count)
{
    if (g_l_switch_is_pressed) {
        m2_motor_stop();
        g_l_switch_is_pressed = false;
    }
}

void on_pressed_J_switch_key(KeyID key, int repeat_count)
{
    if (m1m2_switch_is_closed() == true && is_m1_motor_run_enable() == true)
    {
        m1_motor_run(kForward);
        // HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);
    }

    if (m1m2_switch_is_closed() == true && g_m1_motor_run_backward_is_enable)
    {
        m1_motor_stop();
    }
}

void on_released_J_switch_key(KeyID key, int repeat_count)
{
    if (m1m2_switch_is_closed() == true && g_m1_motor_run_backward_is_enable)
    {
        m1_motor_run(kBackward);
    }

    if (m1m2_switch_is_closed() == true && m1_motor_running_dir() == kForward) {
        m1_motor_stop();
    }
}

void on_pressed_return_switch_key(KeyID key, int repeat_count)
{
    m1_motor_stop();
    m1_motor_run(kBackward);
}

void on_pressed_stop_switch_key(KeyID key, int repeat_count)
{
    m1_motor_stop();

    if (key_is_pressed(kRLimit) == true) {
        m2_motor_run(kBackward);
        return;
    }

    if (key_is_pressed(kLLimit) == true) {
        m2_motor_run(kForward);
        return;
    }

    m2_motor_run(m2_motor_running_dir());
}

void on_released_return_switch_key(KeyID key, int repeat_count)
{
    // if (g_lifetime_counter < MAX_LIFETIME) {
    //     g_lifetime_counter++;
    //     flash_write_lifetime_counter(g_lifetime_counter);
    // } else {
    //     msg_post_int(kMsgReachLifetimeLimit, 0);
    // }
}

void on_released_stop_switch_key(KeyID key, int repeat_count)
{
    // HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
    if (m1_motor_is_running() && m1_motor_running_dir() == kBackward) {
        m1_motor_stop();
        m1_motor_run_disable();
        g_m1_motor_run_backward_is_enable = false;

        if (g_lifetime_counter < MAX_LIFETIME) {
            g_lifetime_counter++;
            flash_write_lifetime_counter(g_lifetime_counter);
        } else {
            msg_post_int(kMsgReachLifetimeLimit, 0);
        }
    }
}

void on_pressed_m1m2_switch_key(KeyID key, int repeat_count)
{
    g_m1m2_switch_is_pressed = true;
    timer_start_oneshot_after(kTimerDelay15s, M1_M2_DELAY);
    m2_motor_stop();

    g_r_switch_counter = 0;
    g_l_switch_counter = 0;
}

void on_released_m1m2_switch_key(KeyID key, int repeat_count)
{
    g_m1m2_switch_is_pressed = false;
    m1_motor_run_disable();
    m1_motor_stop();

    if (g_pass_commbination[0] == 1 && g_pass_commbination[1] == 1 
        && g_pass_commbination[2] == 1 && g_pass_commbination[3] == 1) {
        g_pass_commbination[0] = 0;
        g_pass_commbination[1] = 0;
        g_pass_commbination[2] = 0;
        g_pass_commbination[3] = 0;
        flash_erase_page(FLASH_TYPEERASE_PAGES, START_ADDR, 1);
        sys_soft_reset();
    }
}

bool m1m2_switch_is_closed()
{
    return g_m1m2_switch_is_pressed;
}

void m1_motor_run_enable(void)
{
    g_m1_motor_run_is_enable = true;
    if (key_is_pressed(kKeyJSwitch))
        on_pressed_J_switch_key(kKeyJSwitch, 0);
}

void m1_motor_run_disable(void)
{
    g_m1_motor_run_is_enable = false;
}

bool is_m1_motor_run_enable(void)
{
    return g_m1_motor_run_is_enable;
}

void on_pressed_hold_right_limit_key(KeyID key, int repeat_count)
{
    m2_motor_stop();
    m2_motor_run(kBackward);
    g_is_allow_m1_run = true;
    // m1_motor_run(kForward);
}

void on_released_right_limit_key(KeyID key, int repeat_count)
{
    g_m2_motor_limit_right_is_enable = false;
}

bool is_m2_motor_reach_right_limit(void)
{
    return g_m2_motor_limit_right_is_enable;
}

void on_pressed_hold_left_limit_key(KeyID key, int repeat_count)
{
    m2_motor_stop();
    m2_motor_run(kForward);
    // m1_motor_run(kForward);
}

void on_released_left_limit_key(KeyID key, int repeat_count)
{
    g_m2_motor_limit_left_is_enable = false;
}

bool is_m2_motor_reach_left_limit(void)
{
    return g_m2_motor_limit_left_is_enable;
}

// void on_pressed_left_limit_key(KeyID key, int repeat_count)
// {
//     m2_motor_stop();
// }

void set_key_handler(void)
{
    // timer_set_handler(kTimerDelay15s, m1_motor_run_enable);
    // timer_set_handler(kTimerDelay2s, m2_motor_run_enable);

    // if (g_lifetime_counter < MAX_LIFETIME) {

    // } else {
    //     buzzer(3);
    // }

    key_set_handler(kKeyRSwitch, kKeyEventPressed, on_pressed_R_switch_key);
    key_set_handler(kKeyLSwitch, kKeyEventPressed, on_pressed_L_switch_key);
    // key_set_handler(kKeyRSwitch, kKeyEventReleased, on_released_R_switch_key);
    // key_set_handler(kKeyLSwitch, kKeyEventReleased, on_released_L_switch_key);

    // key_set_handler(kKeyJSwitch, kKeyEventPressed, on_pressed_J_switch_key);
    // key_set_handler(kKeyJSwitch, kKeyEventReleased, on_released_J_switch_key);
    // key_set_handler(kKeyJSwitch, kKeyEventHold, on_pressed_J_switch_key);

    key_set_handler(kKeyReturnSwitch, kKeyEventPressed, on_pressed_return_switch_key);
    // key_set_handler(kKeyReturnSwitch, kKeyEventReleased, on_released_return_switch_key);
    key_set_handler(kKeyStopSwitch, kKeyEventPressed, on_pressed_stop_switch_key);

    // key_set_handler(kM1M2Switch, kKeyEventPressed, on_pressed_m1m2_switch_key);
    // key_set_handler(kM1M2Switch, kKeyEventReleased, on_released_m1m2_switch_key);

    key_set_handler(kRLimit, kKeyEventPressed, on_pressed_hold_right_limit_key);
    // key_set_handler(kRLimit, kKeyEventHold, on_pressed_hold_right_limit_key);

    key_set_handler(kLLimit, kKeyEventPressed, on_pressed_hold_left_limit_key);
    // key_set_handler(kLLimit, kKeyEventHold, on_pressed_hold_left_limit_key);

    // key_set_handler(kRLimit, kKeyEventReleased, on_released_right_limit_key);
    // key_set_handler(kLLimit, kKeyEventReleased, on_released_left_limit_key);

    key_set_handler(kDelay2s, kKeyEventPressed, on_pressed_delay2s_switch_key);
    // key_set_handler(kDelay2s, kKeyEventReleased, on_released_delay2s_switch_key);
}
