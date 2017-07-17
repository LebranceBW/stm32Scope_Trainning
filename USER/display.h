#ifndef DISPLAY_H__
#define DISPLAY_H__

#include "lcd.h"
/*颜色搭配*/
#define BACKGROUNDCOLOR 0x0000
#define EDGELINECOLOR  0X01CF
#define WAVECOLOR YELLOW
#define FONTCOLOR 0x7C49  
#define APPARENTEDGELINECOLOR CYAN 

/*绘图相关的定义*/
#define XBase_Pos 5  //原点水平坐标
#define YBase_Pos  205 //原点竖直坐标
#define DivLength 25 //每个div的长度


#define HoriDiv 10 //水平10个div
#define VeriDiv 8  //竖直8个div
#define HoriEdge (XBase_Pos + HoriDiv * DivLength+2)
#define VeriEdge (YBase_Pos+2)
#define Hori_Length (HoriDiv * DivLength) //横轴长
#define Veri_Length (VeriDiv* DivLength)	//纵轴长
/*参数显示相关的定义*/
#define Right_1st_x HoriEdge + 1
#define Right_1st_y 1
void display_Init(void);
void measureDisplay(float val);
void display_DrawAxis(void);
void display_ClearArea(void);
void display_DrawDotWithCoordinate(u8 coordinateX,u16 coordinateY); /*进行坐标变换后再绘点*/
void display_DrawWave(u16 *a,u16 length,u16 step);
#endif
