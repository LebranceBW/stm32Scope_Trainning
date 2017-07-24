#ifndef DISPLAY_H__
#define DISPLAY_H__

#include "lcd.h"
#include "sys.h"
#include "delay.h"
#include "control.h"
#include "adc.h"
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
#define Parameter_XBase HoriEdge + 1
#define Parameter_YBase(x) 1 + x*13

#define Freq_XPos Parameter_XBase
#define Freq_YPos Parameter_YBase(0)

#define Gain_XPos Parameter_XBase
#define Gain_YPos Parameter_YBase(1)

#define Peak_XPos Parameter_XBase
#define Peak_YPos Parameter_YBase(2)

#define PeakToPeak_XPos Parameter_XBase
#define PeakToPeak_YPos Parameter_YBase(3)
/*刻度显示定义*/
#define Character_Width 8
#define XScale_XPos	XBase_Pos						//水平刻度显示位置
#define XScale_YPos VeriEdge + 2
#define YScale_XPos	(XScale_XPos + Character_Width*12)					//垂直刻度显示位置
#define YScale_YPos XScale_YPos

/*模式显示定义*/
#define Mode_XPos (YScale_XPos+Character_Width*12)
#define Mode_YPos (XScale_YPos)
enum ZoomType {Out,In};
enum LeftOrRight {Left,Right};
enum TopOrBottom {Top,Bottom};

typedef enum LeftOrRight LeftOrRightType;
typedef enum ZoomType Zoom_Type;
typedef enum TopOrBottom TopOrBottomType;
extern u16 buffer[4096];

void display_Init(void);
//void measureDisplay(float val);
void display_DrawAxis(void);
void display_ClearArea(void);
void display_DrawDotWithCoordinate(u8 coordinateX,u16 coordinateY); /*进行坐标变换后再绘点*/
void display_DrawWave(u16 *a,u16 length);
void display_XScale(void);
void display_YScale(void);
void display_XScale_Cmd(Zoom_Type m);
void display_XMove_Cmd(LeftOrRightType lr);
void display_YMove_Cmd(TopOrBottomType tb);
void display_Mode(void);
void display_Frequence(float val);
void display_Gain(s8);
void display_PeakValue(void);
void display_PeakToPeakValue(void);
void display_DrawWavePoint(void);
#endif
