/*引脚说明*/
/*
			上


左		中		右


			下
	
衰减
复位

上 →  PF0
下 →	 PF3
左 →	 PF1
右 →	 PF2
中（确认） →	 PF5
衰减切换 → PF6
复位 →	 PF4

*/

#ifndef __KEY__H
#define __KEY__H

	#include "sys.h"
void Key_Init(void);
extern u8 pause;	
extern u8 moveFlag;
extern u8 attenuation;
#endif
