#include "display.h"
u16 stepsRange[] = {1,2,5,10,20,50,100,200,500};
u8 stepIndex = 0;
u16 xBase = 0; 
u8 moveFlag = 0;
u16 displayBuffer[Hori_Length];
u16 peakValue = 0;
u16 valleyValue = 0;

u16 pointCache;
void display_Init()
{
	LCD_Init();           //初始化LCD FSMC接口
	
	LCD_Clear(BACKGROUNDCOLOR);
	/*绘制边框线*/
	POINT_COLOR = LIGHTBLUE;
	LCD_DrawRectangle(0,0,HoriEdge,VeriEdge);
	LCD_DrawRectangle(HoriEdge,0,320,240);
	LCD_DrawRectangle(0,0,320,240);
	stepIndex = 0;
	display_DrawAxis();
	display_Mode();
	display_XScale();
	display_YScale();
}

void display_DrawWave(u16 *a,u16 length)
{
	peakValue = 0; //峰值
	valleyValue = a[0];
	
	display_ClearArea();
	display_DrawAxis();
	u16 step = stepsRange[stepIndex];
//	while(i<Hori_Length)
//	{
		for(int i = 0;(i<Hori_Length)&&(i*step+xBase<length);i++)
		{
			u16 temp = a[i*step+xBase];
			if(temp >= peakValue) 
					peakValue = temp;
			else if(temp <=valleyValue)
					valleyValue = temp;
			displayBuffer[i] = temp;
			display_DrawDotWithCoordinate(i,temp);
		}
//	}
	display_PeakValue();
	display_PeakToPeakValue();
	
}

void display_DrawDotWithCoordinate(u8 coordinateX,u16 coordinateY) /*进行坐标变换后再绘点*/
{
	u16 XPose = coordinateX + XBase_Pos;
	u16 YPose = YBase_Pos - (u8)((int)coordinateY*Veri_Length/ 0xFFF);
	POINT_COLOR = WAVECOLOR;
	if(coordinateX == 0)
		LCD_DrawPoint(XPose,YPose);
	else if((XPose <Hori_Length) &&(YPose <Veri_Length))
		LCD_DrawLine(XPose - 1,pointCache,XPose,YPose);
	pointCache = YPose;
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

void display_XScale() //显示x刻度
{
	POINT_COLOR = WHITE;
	BACK_COLOR = BACKGROUNDCOLOR;
	u16 step = stepsRange[stepIndex];
	u8 s[12] = {(u8)'X',(u8)':',(u8)'0',(u8)'0',(u8)'0',(u8)'u',(u8)'s',(u8)'/',(u8)'d',(u8)'i',(u8)'v',(u8)'\0'};
	if(step>1000) 
	{
		s[5] = 'm';
		step = step / 1000;
	}
	if(step/100 == 0)
		s[2] = (u8)' ';
	else 
		s[2] = step/100 +'0';

	if(step/10 == 0)
		s[3] = (u8)' ';
	else 
		s[3] = (step/10)%10 +'0' ;	 
	s[4] = (u8)(step % 10 + '0');	
	LCD_ShowString(XScale_XPos,XScale_YPos,88,16,16,s);
}

void display_YScale()
{
	POINT_COLOR = WHITE;
	BACK_COLOR = BACKGROUNDCOLOR;
	u8 s[12] = {(u8)'Y',(u8)':',(u8)'0',(u8)'0',(u8)'0',(u8)'u',(u8)'V',(u8)'/',(u8)'d',(u8)'i',(u8)'v',(u8)'\0'};
//	if(step>1000) 
//	{
//		s[5] = 'm';
//		step = step / 1000;
//	}
//	if(step/10 == 0)
//		s[2] = (u8)' ';
//	s[3] = (u8)(step % 10 + '0');	
	LCD_ShowString(YScale_XPos,YScale_YPos,88,16,16,s);
}

void display_Mode()
{
	POINT_COLOR = APPARENTEDGELINECOLOR;
	BACK_COLOR = BACKGROUNDCOLOR;
	if(moveFlag == 0)
			LCD_ShowString(Mode_XPos,Mode_YPos,64,16,16,(u8*)"Scaling");
	else if(moveFlag == 1)
			LCD_ShowString(Mode_XPos,Mode_YPos,64,16,16,(u8*)"Moving ");
}

void display_XScale_Cmd(Zoom_Type m) //步长变换
{
	if(m == Out)
	{
		if(stepIndex < 8)
		stepIndex++;
	}
	else if(m == In)
	{
		if(stepIndex > 0)
		stepIndex--;
	}
	display_XScale();
	display_DrawWave(buffer,2048);
}

void display_XMove_Cmd(LeftOrRightType lr)
{
	if(lr == Left)
	{
		if(xBase >0)
			xBase -= DivLength;	
	}
	else if(lr == Right)
	{
		xBase += DivLength;
		if(xBase >2048) xBase = 2048;
	}
	display_Mode();
	display_DrawWave(buffer,2048);
}

void display_Frequence(float val)
{
	POINT_COLOR = WHITE;	
	if(val < 100)
	{
		u8 s[11] = {(u8)'f',(u8)':',(u8)'0',(u8)'0',(u8)'.',(u8)'0',(u8)'0',(u8)'K',(u8)'H',(u8)'z',(u8)'\0'};
		u32 temp = val * 100;
		s[2] = (temp/1000==0)?' ':temp/1000+'0';
		temp %=1000;
		s[3] = temp/100+'0';
		temp %=100;	
		s[5] = temp / 10 +'0';
		s[6] = temp % 10 +'0';	
		LCD_ShowString(Freq_XPos,Freq_YPos,66,12,12,s);
	}
	else if(val > 100)
	{
		u8 s[11] = {(u8)'f',(u8)':',(u8)'0',(u8)'0',(u8)'0',(u8)'.',(u8)'0',(u8)'K',(u8)'H',(u8)'z',(u8)'\0'};
		u32 temp = val * 10;
		s[2] = (temp/1000==0)?' ':temp/1000+'0';
		temp %=1000;
		s[3] = temp/100+'0';
		temp %=100;	
		s[4] = temp / 10 +'0';
		s[6] = temp % 10 +'0';	
		LCD_ShowString(Freq_XPos,Freq_YPos,66,12,12,s);
	}
}

void display_Gain(s8 g)
{
	POINT_COLOR = WHITE;
	u8 s[11] = {(u8)'G',(u8)':',(u8)' ',(u8)'0',(u8)'0',(u8)'0',(u8)'d',(u8)'B',(u8)'\0'};
	if(g<0)
	{
		g = -g;
		s[2] = '-';
	}
	s[3] = g/100>0?g/100+'0':' ';
	g %= 100;
	s[4] = g/10>0?g/10+'0':' ';
	s[5] = g%10 + '0';
	LCD_ShowString(Gain_XPos,Gain_YPos,66,12,12,s);
}

void display_PeakValue()
{
	POINT_COLOR = WHITE;
	u32 temp = peakValue*32.4 /4096 ;
	u8 s[9] = {(u8)'V',(u8)'p',(u8)':',(u8)'0',(u8)'0',(u8)'.',(u8)'0',(u8)'V',(u8)'\0'};
	s[3] = (temp/100==0)?' ':temp/100+'0';
	temp %=100;
	s[4] = temp/10+'0';
	s[6] = temp%10 + '0';
	LCD_ShowString(Peak_XPos,Peak_YPos,66,12,12,s);
}

void display_PeakToPeakValue()
{
	POINT_COLOR = WHITE;
	u32 temp = (peakValue-valleyValue)*32.4 /4096 ;
	u8 s[11] = {(u8)'V',(u8)'p',(u8)'-',(u8)'p',(u8)':',(u8)'0',(u8)'0',(u8)'.',(u8)'0',(u8)'V',(u8)'\0'};
	s[5] = (temp/100==0)?' ':temp/100+'0';
	temp %=100;
	s[6] = temp/10+'0';
	s[8] = temp%10 + '0';
	LCD_ShowString(PeakToPeak_XPos,PeakToPeak_YPos,66,12,12,s);
}
