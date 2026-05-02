#include "lnf_LED.h"

/**
 * @brief 指定组的led显示指定的数字
 *
 * @param 要点亮的led的组  [1, 5]  前4组是显示4个数字, 第5组是显示冒号
 * @param 这组led 要显示的数字
 *
 * @return
 */
void Inf_LED_ShowNum(uint8_t group, uint8_t num)
{
    // 熄灭所有LRD
    gpio_direction_output(IO_PORTC_01, 1);
    gpio_direction_output(IO_PORTC_02, 1);
    gpio_direction_output(IO_PORTC_03, 1);
    gpio_direction_output(IO_PORTC_04, 1);
    gpio_direction_output(IO_PORTC_05, 1);


    if(group == 1)
    {
        gpio_direction_output(IO_PORTC_01, 0);
    }
    else if(group == 2)
    {
        gpio_direction_output(IO_PORTC_02, 0);
    }
    else if(group == 3)
    {
        gpio_direction_output(IO_PORTC_03, 0);

    }
    else if(group == 4)
    {
        gpio_direction_output(IO_PORTC_04, 0);

    }
    else if(group == 5)
    {
        gpio_direction_output(IO_PORTC_05, 0);

        gpio_direction_output(IO_PORTA_06, 0);
        gpio_direction_output(IO_PORTA_07, 0);
        gpio_direction_output(IO_PORTA_08, 0);
        gpio_direction_output(IO_PORTA_09, 0);
        gpio_direction_output(IO_PORTA_10, 0);
        gpio_direction_output(IO_PORTC_06, 0);
        gpio_direction_output(IO_PORTC_10, 0);

        if(num == 0)
        {
            gpio_direction_output(IO_PORTC_06, 0);  // 熄灭冒号
        }
        else
        {
            gpio_direction_output(IO_PORTC_06, 1);  // 点亮冒号
        }
        return;

    }

    if(num == 0)
    {
        /*
             -
            | |
            | |
             -
        */
        gpio_direction_output(IO_PORTA_06, 1);  // 最上面的LED
        gpio_direction_output(IO_PORTA_07, 1);  // 顺时针
        gpio_direction_output(IO_PORTA_08, 1);
        gpio_direction_output(IO_PORTA_09, 1);
        gpio_direction_output(IO_PORTA_10, 1);
        gpio_direction_output(IO_PORTC_06, 1);
        gpio_direction_output(IO_PORTC_10, 0);  // 中间横着的LED
    }
    else if(num == 1)
    {
        /*

               |
               |

         */
        gpio_direction_output(IO_PORTA_06, 0);
        gpio_direction_output(IO_PORTA_07, 1);
        gpio_direction_output(IO_PORTA_08, 1);
        gpio_direction_output(IO_PORTA_09, 0);
        gpio_direction_output(IO_PORTA_10, 0);
        gpio_direction_output(IO_PORTC_06, 0);
        gpio_direction_output(IO_PORTC_10, 0);
    }
    else if(num == 2)
    {
        /*
              -
               |
              -
             |
              -
         */
        gpio_direction_output(IO_PORTA_06, 1);
        gpio_direction_output(IO_PORTA_07, 1);
        gpio_direction_output(IO_PORTA_08, 0);
        gpio_direction_output(IO_PORTA_09, 1);
        gpio_direction_output(IO_PORTA_10, 1);
        gpio_direction_output(IO_PORTC_06, 0);
        gpio_direction_output(IO_PORTC_10, 1);
    }
    else if(num == 3)
    {
        /*
              -
               |
              -
               |
              -
         */
        gpio_direction_output(IO_PORTA_06, 1);
        gpio_direction_output(IO_PORTA_07, 1);
        gpio_direction_output(IO_PORTA_08, 1);
        gpio_direction_output(IO_PORTA_09, 1);
        gpio_direction_output(IO_PORTA_10, 0);
        gpio_direction_output(IO_PORTC_06, 0);
        gpio_direction_output(IO_PORTC_10, 1);
    }
    else if(num == 4)
    {
        /*

             | |
              -
               |

         */
        gpio_direction_output(IO_PORTA_06, 0);
        gpio_direction_output(IO_PORTA_07, 1);
        gpio_direction_output(IO_PORTA_08, 1);
        gpio_direction_output(IO_PORTA_09, 0);
        gpio_direction_output(IO_PORTA_10, 0);
        gpio_direction_output(IO_PORTC_06, 1);
        gpio_direction_output(IO_PORTC_10, 1);
    }
    else if(num == 5)
    {
        /*
             -
            |
             -
              |
             -

        */
        gpio_direction_output(IO_PORTA_06, 1);
        gpio_direction_output(IO_PORTA_07, 0);
        gpio_direction_output(IO_PORTA_08, 1);
        gpio_direction_output(IO_PORTA_09, 1);
        gpio_direction_output(IO_PORTA_10, 0);
        gpio_direction_output(IO_PORTC_06, 1);
        gpio_direction_output(IO_PORTC_10, 1);
    }
    else if(num == 6)
    {
        /*
             -
            |
             -
            | |
             -

        */
        gpio_direction_output(IO_PORTA_06, 1);
        gpio_direction_output(IO_PORTA_07, 0);
        gpio_direction_output(IO_PORTA_08, 1);
        gpio_direction_output(IO_PORTA_09, 1);
        gpio_direction_output(IO_PORTA_10, 1);
        gpio_direction_output(IO_PORTC_06, 1);
        gpio_direction_output(IO_PORTC_10, 1);
    }
    else if(num == 7)
    {
        /*
             -
              |

              |


        */
        gpio_direction_output(IO_PORTA_06, 1);
        gpio_direction_output(IO_PORTA_07, 1);
        gpio_direction_output(IO_PORTA_08, 1);
        gpio_direction_output(IO_PORTA_09, 0);
        gpio_direction_output(IO_PORTA_10, 0);
        gpio_direction_output(IO_PORTC_06, 0);
        gpio_direction_output(IO_PORTC_10, 0);
    }
    else if(num == 8)
    {
        /*
             -
            | |
             -
            | |
             -

        */
        gpio_direction_output(IO_PORTA_06, 1);
        gpio_direction_output(IO_PORTA_07, 1);
        gpio_direction_output(IO_PORTA_08, 1);
        gpio_direction_output(IO_PORTA_09, 1);
        gpio_direction_output(IO_PORTA_10, 1);
        gpio_direction_output(IO_PORTC_06, 1);
        gpio_direction_output(IO_PORTC_10, 1);
    }
    else if(num == 9)
    {
        /*
             -
            | |
             -
              |
             -

        */
        gpio_direction_output(IO_PORTA_06, 1);
        gpio_direction_output(IO_PORTA_07, 1);
        gpio_direction_output(IO_PORTA_08, 1);
        gpio_direction_output(IO_PORTA_09, 1);
        gpio_direction_output(IO_PORTA_10, 0);
        gpio_direction_output(IO_PORTC_06, 1);
        gpio_direction_output(IO_PORTC_10, 1);
    }

}

void Inf_LED_CloseAllNums(void)
{
    gpio_direction_output(IO_PORTC_01, 1);
    gpio_direction_output(IO_PORTC_02, 1);
    gpio_direction_output(IO_PORTC_03, 1);
    gpio_direction_output(IO_PORTC_04, 1);
    gpio_direction_output(IO_PORTC_05, 1);

}


