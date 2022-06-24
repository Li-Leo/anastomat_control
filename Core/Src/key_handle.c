#include "key_handle.h"
#include "key.h"
#include "hall.h"
#include "motor.h"
#include "timer.h"

bool g_m1m2_switch_is_pressed = false;
bool g_m1_motor_run_is_enable = false;

bool g_m2_motor_limit_left_is_enable = false;
bool g_m2_motor_limit_right_is_enable = false;

void on_pressed_R_switch_key(KeyID key, int repeat_count)
{
  if (m1m2_switch_is_closed() == false && is_m2_motor_reach_right_limit() == false) {
    m2_motor_run(kForward);
  }
}

void on_pressed_L_switch_key(KeyID key, int repeat_count)
{
  if (m1m2_switch_is_closed() == false && is_m2_motor_reach_left_limit() == false) {
    m2_motor_run(kBackward);
  }
}

void on_released_LR_switch_key(KeyID key, int repeat_count)
{
  m2_motor_stop();
}

void on_pressed_J_switch_key(KeyID key, int repeat_count)
{
  if (m1m2_switch_is_closed() == true && is_m1_motor_run_enable() == true) {
    m1_motor_run(kForward);
  }
}

void on_pressed_return_switch_key(KeyID key, int repeat_count)
{

  if (m1m2_switch_is_closed() == true && is_m1_motor_run_enable() == true) {
    m1_motor_run(kBackward);
  }
}

void on_released_return_switch_key(KeyID key, int repeat_count)
{
  
}

void on_pressed_stop_switch_key(KeyID key, int repeat_count)
{
  // HAL_GPIO_WritePin(LED_ORANGE_GPIO_Port, LED_ORANGE_Pin, GPIO_PIN_RESET);
  m1_motor_stop();
  buzzer(5);
}

void on_pressed_m1m2_switch_key(KeyID key, int repeat_count)
{
  g_m1m2_switch_is_pressed = true;
  timer_start_oneshot_after(kTimerDelay15s, 15 * 1000);
}

void on_released_m1m2_switch_key(KeyID key, int repeat_count)
{
  g_m1m2_switch_is_pressed = false;
  m1_motor_run_disable();
}

bool m1m2_switch_is_closed()
{
  return g_m1m2_switch_is_pressed;
}

void m1_motor_run_enable(void)
{
  g_m1_motor_run_is_enable = true;
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
    g_m2_motor_limit_right_is_enable = true;
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
    g_m2_motor_limit_left_is_enable = true;
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
    timer_set_handler(kTimerDelay15s, m1_motor_run_enable);

    key_set_handler(kKeyRSwitch, kKeyEventPressed, on_pressed_R_switch_key);
    key_set_handler(kKeyLSwitch, kKeyEventPressed, on_pressed_L_switch_key);
    key_set_handler(kKeyRSwitch, kKeyEventReleased, on_released_LR_switch_key);
    key_set_handler(kKeyLSwitch, kKeyEventReleased, on_released_LR_switch_key);

    key_set_handler(kKeyJSwitch, kKeyEventPressed, on_pressed_J_switch_key);
    key_set_handler(kKeyReturnSwitch, kKeyEventPressed, on_pressed_return_switch_key);
    key_set_handler(kKeyReturnSwitch, kKeyEventReleased, on_released_return_switch_key);
    key_set_handler(kKeyStopSwitch, kKeyEventPressed, on_pressed_stop_switch_key);

    key_set_handler(kM1M2Switch, kKeyEventPressed, on_pressed_m1m2_switch_key);
    key_set_handler(kM1M2Switch, kKeyEventReleased, on_released_m1m2_switch_key);

    key_set_handler(kRLimit, kKeyEventPressed, on_pressed_hold_right_limit_key);
    key_set_handler(kRLimit, kKeyEventHold, on_pressed_hold_right_limit_key);

    key_set_handler(kLLimit, kKeyEventPressed, on_pressed_hold_left_limit_key);
    key_set_handler(kLLimit, kKeyEventHold, on_pressed_hold_left_limit_key);

    key_set_handler(kRLimit, kKeyEventReleased, on_released_right_limit_key);
    key_set_handler(kLLimit, kKeyEventReleased, on_released_left_limit_key);
}

