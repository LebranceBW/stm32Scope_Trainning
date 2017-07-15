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
	/*绘制div分线*/
	POINT_COLOR = EDGELINECOLOR;
	for(int i = 0;i<=VerDiv;i++)
		LCD_DrawDottedLine(XBase,YBase-i*DivLength,XBase + HoriDiv * DivLength, YBase-i*DivLength);
	for(int i = 0;i<=HoriDiv;i++)
		LCD_DrawDottedLine(XBase+i*DivLength,YBase,XBase+i*DivLength, YBase- VerDiv * DivLength);
	/*绘制坐标轴*/
	POINT_COLOR = APPARENTEDGELINECOLOR;
	LCD_DrawLine(XBase,YBase - 4 * DivLength,XBase + HoriDiv * DivLength,YBase - 4 * DivLength);
	LCD_DrawLine(XBase + 5*DivLength ,YBase,XBase + 5*DivLength,YBase - VerDiv * DivLength);
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


