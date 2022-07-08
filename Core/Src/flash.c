
#include "flash.h"
#include "timer.h"
#include "cmsis_armcc.h"
#include "motor.h"

uint16_t g_lifetime_counter;

void flash_write_halfword(uint32_t write_addr, uint16_t data)
{

    HAL_FLASH_Unlock();
    HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, write_addr, data);
    HAL_FLASH_Lock();
}

uint16_t flash_read_halfword(uint32_t read_addr)
{
    uint16_t ret;

    ret = *(uint16_t *) (read_addr);
    return ret;
}

HAL_StatusTypeDef flash_erase_page(uint32_t erase_type, uint32_t page_addr, uint32_t num_of_page)
{

    FLASH_EraseInitTypeDef erase_config = {.TypeErase = erase_type, .PageAddress = page_addr, .NbPages = num_of_page};
    uint32_t page_error;
    HAL_StatusTypeDef status;

    HAL_FLASH_Unlock();
    status = HAL_FLASHEx_Erase(&erase_config, &page_error);
    HAL_FLASH_Lock();

    return status;
}

void led_set(void)
{
    if (g_lifetime_counter <= 25) {
        HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(LED_ORANGE_GPIO_Port, LED_ORANGE_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
    } else if (g_lifetime_counter <= 27) {
        HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_ORANGE_GPIO_Port, LED_ORANGE_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
    } else {
        HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_ORANGE_GPIO_Port, LED_ORANGE_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
    }
}

void flash_write_lifetime_counter(uint16_t counter)
{
    flash_erase_page(FLASH_TYPEERASE_PAGES, START_ADDR, 1);
    flash_write_halfword(FLAG_ADDR, 0xA55A);
    flash_write_halfword(COUNTER_ADDR, counter);
}

void flash_init(void)
{
    uint16_t flag;
    HAL_StatusTypeDef status;

    flag = flash_read_halfword(FLAG_ADDR);

    if (flag != 0xA55A) {
        status = flash_erase_page(FLASH_TYPEERASE_PAGES, START_ADDR, 1);
    
        if (status == HAL_OK) {
            g_lifetime_counter = 0;
            flash_write_halfword(FLAG_ADDR, 0xA55A);
            flash_write_halfword(COUNTER_ADDR, 0);
            g_m1_motor_is_lifetime_enable = true;
            g_m2_motor_is_lifetime_enable = true;
        }
    } else {
        g_lifetime_counter = flash_read_halfword(COUNTER_ADDR);

#ifdef __DEBUG

#else
    if (g_lifetime_counter < MAX_LIFETIME) {
        g_m1_motor_is_lifetime_enable = true;
        g_m2_motor_is_lifetime_enable = true;
    } else {
        g_m1_motor_is_lifetime_enable = false;
        g_m2_motor_is_lifetime_enable = false;
    }

#endif

    }

    timer_set_handler(kTimerLedCheck, led_set);
    timer_start_periodic_every(kTimerLedCheck, 200);
    led_set();
}

void sys_soft_reset(void)// 软重启
{
    SCB->AIRCR =0X05FA0000 | (uint32_t)0x04;
}

// void soft_reset(void)
// { 
//     __set_FAULTMASK(1);  // 关闭所有中端
//     NVIC_SystemReset();     // 复位
// }


