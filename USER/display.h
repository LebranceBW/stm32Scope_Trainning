#ifndef DISPLAY_H__
#define DISPLAY_H__

#include "lcd.h"
/*颜色搭配*/
#define BACKGROUNDCOLOR 0x0000
#define EDGELINECOLOR  0X01CF
#define WAVECOLOR 0xFFFF
#define FONTCOLOR 0x7C49  
#define APPARENTEDGELINECOLOR CYAN 

/*绘图相关的定义*/
#define XBase 5  //原点水平坐标
#define YBase  205 //原点竖直坐标
#define DivLength 25 //每个div的长度
#define HoriDiv 10 //水平10个div
#define VerDiv 8  //竖直8个div
#define HoriEdge (XBase + HoriDiv * DivLength+2)
#define VeriEdge YBase+2

/*参数显示相关的定义*/
#define Right_1st_x HoriEdge + 1
#define Right_1st_y 1
void display_Init(void);
void measureDisplay(float val);

#endif
