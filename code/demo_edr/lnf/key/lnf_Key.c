#include "lnf_Key.h"

// 初始按键
void Inf_Key_Init(void)
{
    // 设置按键
    gpio_direction_input(IO_PORTB_00);
    // 上拉：value 1，上拉；0，不上拉
    gpio_set_pull_up(IO_PORTB_00,1);


    gpio_direction_input(IO_PORTC_00);
    gpio_set_pull_up(IO_PORTC_00,1);


    gpio_direction_input(IO_PORTC_07);
    gpio_set_pull_up(IO_PORTC_07,1);

    gpio_direction_input(IO_PORTB_01);
    gpio_set_pull_up(IO_PORTB_01,1);

    gpio_direction_input(IO_PORTA_04);
    gpio_set_pull_up(IO_PORTA_04,1);

    gpio_direction_input(IO_PORTA_01);
    gpio_set_pull_up(IO_PORTA_01,1);





}



// 扫描按键
My_Key Inf_Key_Scan(void)
{
    if(
       gpio_read(IO_PORTB_00) == 0 ||
       gpio_read(IO_PORTC_00) == 0 ||
       gpio_read(IO_PORTC_07) == 0 ||
       gpio_read(IO_PORTB_01) == 0 ||
       gpio_read(IO_PORTA_04) == 0 ||
       gpio_read(IO_PORTA_01) == 0

       ) {
           // 延时，消抖
           os_time_dly(20 / 10);

           if(gpio_read(IO_PORTB_00)  == 0)
           {
               while(gpio_read(IO_PORTB_00) == 0); // 循环等待按键被按下
               return KEY1; // 按下设置返回按键，自定义的枚举值
           }
           else if(gpio_read(IO_PORTC_00)  == 0)
           {
               while(gpio_read(IO_PORTC_00) == 0);
               return KEY2;
           }
            else if(gpio_read(IO_PORTC_07)  == 0)
           {
               while(gpio_read(IO_PORTC_07) == 0);
               return KEY3;
           }
            else if(gpio_read(IO_PORTB_01)  == 0)
           {
               while(gpio_read(IO_PORTB_01) == 0);
               return KEY4;
           }
            else if(gpio_read(IO_PORTA_04)  == 0)
           {
               while(gpio_read(IO_PORTA_04) == 0);
               return KEY5;
           }
            else if(gpio_read(IO_PORTA_01)  == 0)
           {
               while(gpio_read(IO_PORTA_01) == 0);
               return KEY6;
           }
       }

       return NOKEY;  // 没有按键按下

}
