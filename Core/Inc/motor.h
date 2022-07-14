#pragma once

#include "hall.h"

extern bool g_m1_motor_is_lifetime_enable;
extern bool g_m2_motor_is_lifetime_enable;


void m1_motor_run(enum direction dir);
void m1_motor_stop(void);
bool m1_motor_is_running(void);
enum direction m1_motor_running_dir(void);

void m2_motor_run(enum direction dir);
void m2_motor_stop(void);
bool m2_motor_is_running(void);
void buzzer(uint16_t repeat);
void m2_motor_init(void);
enum direction m2_motor_running_dir(void);
