
#include "hall.h"
#include "tim.h"

struct hall_state hall;
bool g_direction;


void motor_switch_direction(void)
{
    if (g_direction)
        g_direction = false;
    else
        g_direction = true;
}

void hall_switch_direction(void)
{
    if (HAL_GPIO_ReadPin(Hall_A_GPIO_Port, Hall_A_Pin) == GPIO_PIN_SET)
    {
        hall.hall_UVW[0] = 1;
    }
    else
    {
        hall.hall_UVW[0] = 0;
    }

    if (HAL_GPIO_ReadPin(Hall_B_GPIO_Port, Hall_B_Pin) == GPIO_PIN_SET)
    {
        hall.hall_UVW[1] = 1;
    }
    else
    {
        hall.hall_UVW[1] = 0;
    }

    if (HAL_GPIO_ReadPin(Hall_C_GPIO_Port, Hall_C_Pin) == GPIO_PIN_SET)
    {
        hall.hall_UVW[2] = 1;
    }
    else
    {
        hall.hall_UVW[2] = 0;
    }

    hall.hall_state_current = hall.hall_UVW[0] + (hall.hall_UVW[1] << 1) + (hall.hall_UVW[2] << 2);

    if (!g_direction)
        hall.hall_state_current = 7 - hall.hall_state_current;

#if 1
    // if (hall.hall_state_current != hall.hall_state_old)
    // {
    //     switch (hall.hall_state_current)
    //     {
    //     case 0x5:
    //     {
    //         mos_U_VN(); // A+B-
    //     }
    //     break;

    //     case 0x1:
    //     {
    //         mos_U_WN(); // A+C-
    //     }
    //     break;

    //     case 0x3:
    //     {
    //         mos_V_WN(); // B+C-
    //     }
    //     break;

    //     case 0x2:
    //     {
    //         mos_V_UN(); // B+A-
    //     }
    //     break;

    //     case 0x6:
    //     {
    //         mos_W_UN(); // C+A-
    //     }
    //     break;

    //     case 0x4:
    //     {
    //         mos_W_VN(); // C+B-
    //     }
    //     break;

    //     default:
    //     {
    //         stop_motor();
    //     }
    //     break;
    //     }
    // }

    // if (hall.hall_state_old == hall.hall_state_current)
    {

        switch (hall.hall_state_current)
        {
        case 0x5:
        {
            mos_U_VN(); // A+B-
        }
        break;

        case 0x1:
        {
            mos_U_WN(); // A+C-
        }
        break;

        case 0x3:
        {
            mos_V_WN(); // B+C-
        }
        break;

        case 0x2:
        {
            mos_V_UN(); // B+A-
        }
        break;

        case 0x6:
        {
            mos_W_UN(); // C+A-
        }
        break;

        case 0x4:
        {
            mos_W_VN(); // C+B-
        }
        break;

        default:
        {
            stop_motor();
        }
        break;
        }
    }

    // hall.hall_state_old = hall.hall_state_current;
#endif
}

