#pragma once
#include "main.h"


#define START_ADDR  0x800FE00
#define FLAG_ADDR  START_ADDR
#define COUNTER_ADDR  0x800FE02

#define MAX_LIFETIME  28

extern uint16_t g_lifetime_counter;

HAL_StatusTypeDef flash_erase_page(uint32_t erase_type, uint32_t page_addr, uint32_t num_of_page);
void flash_write_halfword(uint32_t write_addr, uint16_t data);
uint16_t flash_read_halfword(uint32_t read_addr);
void flash_write_lifetime_counter(uint16_t counter);
void flash_init(void);
void sys_soft_reset(void);

