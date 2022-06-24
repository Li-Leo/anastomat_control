#pragma once
#include "main.h"

bool m1m2_switch_is_closed(void);
void m1_motor_run_disable(void);
void m1_motor_run_enable(void);
bool is_m1_motor_run_enable(void);
void set_key_handler(void);
bool is_m2_motor_reach_left_limit(void);
bool is_m2_motor_reach_right_limit(void);

