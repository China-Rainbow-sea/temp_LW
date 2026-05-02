#ifndef __INF_LED_H
#define __INF_LED_H

#include "asm/gpio.h"
#include "stdint.h"

void Inf_LED_ShowNum(uint8_t group, uint8_t num);
void Inf_LED_CloseAllNums(void);

#endif // __INF_LED_H
