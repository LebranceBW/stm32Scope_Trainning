#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "lcd.h"
#define XBase 5  //原点水平坐标
#define YBase  205 //原点竖直坐标
#define DivLength 25 //每个div的长度
#define HoriDiv 10 //水平10个div
#define VerDiv 8  //竖直8个div
#define HoriEdge (XBase + HoriDiv * DivLength+2)
#define VeriEdge YBase+2
int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168); 
	uart_init(9600);
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
  while(1) 
	{	
	 	
	}
}
