#pragma once

#include "hall.h"

void m1_motor_run(enum direction dir);
void m1_motor_stop(void);
bool m1_motor_is_running(void);

void m2_motor_run(enum direction dir);
void m2_motor_stop(void);
bool m2_motor_is_running(void);
void buzzer(uint16_t repeat);
