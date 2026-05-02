#ifndef __INF_KEY_
#define __INF_KEY_

#include "device/gpio.h"

typedef enum
{
    NOKEY,
    KEY1,
    KEY2,
    KEY3,
    KEY4,
    KEY5,
    KEY6
}My_Key;


// ³õÊ¼°´¼ü
void Inf_Key_Init(void);

// É¨Ãè°´¼ü
My_Key Inf_Key_Scan(void);

#endif // __INF_KEY_
