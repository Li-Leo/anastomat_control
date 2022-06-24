
#ifndef __HALL_H__
#define __HALL_H__

#include "stdint.h"
#include "stdbool.h"

struct hall_state
{
    uint8_t hall_UVW[3];         // 读取三个霍尔的对应状态
    uint8_t hall_state_current;  // 当前霍尔状态
    // uint8_t hall_state_old;      // 历史霍尔状态
};

enum direction
{
    kForward,
    kBackward,

    kDrectionMax,
};

void hall_switch_phase(void);
void m1_motor_toggle_direction(void);
void m1_motor_set_direction(enum direction dir);

#endif /* __HALL_H__ */

