#include "motor.h"
#include "main.h"
#include "tim.h"
#include "timer.h"
#include "flash.h"

static bool g_m1_motor_is_running;
static enum direction g_m1_motor_running_direction;

bool g_m1_motor_is_lifetime_enable = true;
bool g_m2_motor_is_lifetime_enable = true;

static bool g_m2_motor_is_running;

static uint16_t g_buzzer_counter;
static uint16_t g_buzzer_repeat;

void m1_motor_run(enum direction dir)
{
    if (!m1_motor_is_running() && g_m1_motor_is_lifetime_enable) {
        m1_motor_stop_output();
        HAL_TIM_Base_Stop_IT(&htim1);
        HAL_Delay(100);
        m1_motor_set_direction(dir);
        HAL_TIM_Base_Start_IT(&htim1);
        g_m1_motor_is_running = true;
        g_m1_motor_running_direction = dir;
    }
}

void m1_motor_stop()
{
    if (m1_motor_is_running()) {
        m1_motor_stop_output();
        g_m1_motor_is_running = false;
    }
}

enum direction m1_motor_running_dir()
{
    return g_m1_motor_running_direction;
}

bool m1_motor_is_running()
{
    return g_m1_motor_is_running;
}


void m2_motor_set_direction(enum direction dir)
{
    if (dir == kForward)
        HAL_GPIO_WritePin(SMotor_DIR_GPIO_Port, SMotor_DIR_Pin, GPIO_PIN_SET);
    else if (dir == kBackward)
        HAL_GPIO_WritePin(SMotor_DIR_GPIO_Port, SMotor_DIR_Pin, GPIO_PIN_RESET);
}

void m2_motor_run(enum direction dir)
{
    if (!m2_motor_is_running() && g_m2_motor_is_lifetime_enable) {
        HAL_TIM_PWM_Stop(&htim14, TIM_CHANNEL_1);
        m2_motor_set_direction(dir);
        HAL_Delay(50);
        HAL_TIM_MspPostInit(&htim14);
        HAL_TIM_PWM_Start(&htim14, TIM_CHANNEL_1);
        g_m2_motor_is_running = true;
    }
}

void m2_motor_stop()
{
    if (m2_motor_is_running()) {
        HAL_TIM_PWM_Stop(&htim14, TIM_CHANNEL_1);
        GPIO_InitTypeDef GPIO_InitStruct = {0};
        GPIO_InitStruct.Pin = SMotor_PWM_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        HAL_GPIO_Init(SMotor_PWM_GPIO_Port, &GPIO_InitStruct);
        HAL_GPIO_WritePin(SMotor_PWM_GPIO_Port, SMotor_PWM_Pin, GPIO_PIN_RESET);
        g_m2_motor_is_running = false;
    }
}

bool m2_motor_is_running()
{
    return g_m2_motor_is_running;
}

void buzzer_on(void)
{
    HAL_TIM_PWM_Start(&htim17, TIM_CHANNEL_1);
}

void buzzer_off(void)
{
    HAL_TIM_PWM_Stop(&htim17, TIM_CHANNEL_1);
}


void buzzer_internal(void)
{
    g_buzzer_counter++;
    buzzer_on();
    timer_set_handler(kTimerDelayBuzzerInternal, buzzer_off);
    timer_start_oneshot_after(kTimerDelayBuzzerInternal, 200);
    if (g_buzzer_counter >= g_buzzer_repeat) {
        timer_stop(kTimerDelayBuzzer);
        // timer_stop();
    }
}

void buzzer(uint16_t repeat)
{
    g_buzzer_counter = 0;
    g_buzzer_repeat = repeat;

    timer_set_handler(kTimerDelayBuzzer, buzzer_internal);
    timer_start_periodic_every(kTimerDelayBuzzer, 500);
    buzzer_internal();
}
