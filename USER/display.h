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

/*刻度显示定义*/
#define Character_Width 8
#define XScale_XPos	XBase_Pos						//水平刻度显示位置
#define XScale_YPos VeriEdge + 2
#define YScale_XPos	(XScale_XPos + Character_Width*12)					//垂直刻度显示位置
#define YScale_YPos XScale_YPos

/*模式显示定义*/
#define Mode_XPos (YScale_XPos+Character_Width*12)
#define Mode_YPos (XScale_YPos)
enum RaisingOrFalling {Raising,Falling};
enum LeftOrRight {Left,Right};

typedef enum LeftOrRight LeftOrRightType;
typedef enum RaisingOrFalling RaisingOrFallingType;

extern u16 buffer[2048];

void display_Init(void);
void measureDisplay(float val);
void display_DrawAxis(void);
void display_ClearArea(void);
void display_DrawDotWithCoordinate(u8 coordinateX,u16 coordinateY); /*进行坐标变换后再绘点*/
void display_DrawWave(u16 *a,u16 length);
void display_XScale(void);
void display_YScale(void);
void display_XScale_Cmd(RaisingOrFallingType m);
void display_XMove_Cmd(LeftOrRightType lr);
void display_Mode(void);
#endif
