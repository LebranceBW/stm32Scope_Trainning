/* 根据输入电压的值调整放大缩小倍数  */

#ifndef CONTROL__H__
#define CONTROL__H__

#include "sys.h"
#include "math.h"
double Control_DAConverRate(u16 DAReg_Val);
s8 Control_DAConverdB(u16 DAVol_Val);

#endif
