/* 根据输入电压的值调整放大缩小倍数  */

#ifndef CONTROL__H__
#define CONTROL__H__

#include "sys.h"
#include "arm_math.h"
#include "dac.h"
#include "display.h"

enum IsSuitable { OK = 0,Small = 1,Large = 2};
typedef enum IsSuitable IsSuitable_Type;

double Control_DAConverRate(void);
s8 Control_DAConverdB(void);
IsSuitable_Type Control_NeedToAdjust(u16 peakValue,u16 valleyValue);
void Control_Init(void);
void Control_DecInput(void);
void Control_IncInput(void);
#endif
