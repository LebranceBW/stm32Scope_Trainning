/* ���������ѹ��ֵ�����Ŵ���С����  */

#ifndef CONTROL__H__
#define CONTROL__H__

#include "sys.h"
#include "math.h"
#include "dac.h"
#include "display.h"

enum IsSuitable { OK = 0,Small = 1,Large = 2};
typedef enum IsSuitable IsSuitable_Type;

double Control_DAConverRate(u16 DAReg_Val);
s8 Control_DAConverdB(u16 DAVol_Val);
IsSuitable_Type Control_NeedToAdjust(u16 peakValue,u16 valleyValue);
void Control_Init(void);
void Control_DecInput(void);
void Control_IncInput(void);
#endif