#include "display.h"

void display_Init()
{
	LCD_Init();           //初始化LCD FSMC接口
	
	LCD_Clear(BACKGROUNDCOLOR);
	/*绘制边框线*/
	POINT_COLOR = LIGHTBLUE;
	LCD_DrawRectangle(0,0,HoriEdge,VeriEdge);
	LCD_DrawRectangle(HoriEdge,0,320,240);
	LCD_DrawRectangle(0,0,320,240);
	
	display_DrawAxis();
}

void measureDisplay(float val)
{
	POINT_COLOR = BLACK;
	u32 temp = val * 1000;
	u8 s[7];
	s[0] = temp / 1000 +'0';
	s[1] = '.';
	s[2] = ((temp = temp / 10),temp/100 +'0');
	s[3] = ((temp = temp / 10),temp/10 +'0');
	s[4] = temp % 10 +'0';
	s[5] = 'V';
	s[6] = 0;
	LCD_ShowxNum(Right_1st_x,Right_1st_y,val,4,16,0);
	LCD_ShowString(Right_1st_x,Right_1st_y,64,16,16,s);
}

void display_DrawWave(u16 *a,u16 length,u16 step)
{
	display_ClearArea();
	display_DrawAxis();
	for(int i = 0;(i<Hori_Length)&&(i*step<length);i++)
	{
		display_DrawDotWithCoordinate(i*step,a[i]);
	}
}

void display_DrawDotWithCoordinate(u8 coordinateX,u16 coordinateY) /*进行坐标变换后再绘点*/
{
	u16 XPose = coordinateX + XBase_Pos;
	u16 YPose = YBase_Pos - (u8)((int)coordinateY*Veri_Length/ 0xFFF);
	POINT_COLOR = WAVECOLOR;
	if((XPose <Hori_Length) &&(YPose <Veri_Length))
	LCD_DrawPoint(XPose,YPose);
}

void display_DrawAxis() /*绘制坐标轴与分割线*/
{
	/*绘制div分线*/
	POINT_COLOR = EDGELINECOLOR;
	for(int i = 0;i<=VeriDiv;i++)
		LCD_DrawDottedLine(XBase_Pos,YBase_Pos-i*DivLength,XBase_Pos+Hori_Length, YBase_Pos-i*DivLength);
	for(int i = 0;i<=HoriDiv;i++)
		LCD_DrawDottedLine(XBase_Pos+i*DivLength,YBase_Pos,XBase_Pos+i*DivLength, YBase_Pos- Veri_Length);
	/*绘制坐标轴*/
	POINT_COLOR = APPARENTEDGELINECOLOR;
	LCD_DrawLine(XBase_Pos,YBase_Pos - 4 * DivLength,XBase_Pos + Hori_Length,YBase_Pos - 4 * DivLength);
	LCD_DrawLine(XBase_Pos + 5*DivLength ,YBase_Pos,XBase_Pos + 5*DivLength,YBase_Pos - Veri_Length);
}
void display_ClearArea() /*清空绘图区再绘制坐标轴*/
{
	LCD_Fill(XBase_Pos,YBase_Pos - Veri_Length,XBase_Pos + Hori_Length,YBase_Pos,BACKGROUNDCOLOR);
}

