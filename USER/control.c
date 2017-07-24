#include "control.h"
u16 DAOut = 499;
s8 Control_DAConverdB()
{
//	return -22.88*DAOut/(double)1000 + 21.424;
		return 40*(1.01 - DAOut/(double)1000) + 10;
	
}

float Control_DAConverRate()
{
		float x = DAOut/100;
		float temp = 0.1049 * pow(2.718,0.4734*x);
		return temp;
}
 
IsSuitable_Type Control_NeedToAdjust(u16 peakValue,u16 valleyValue)
{
		if((peakValue >= 0xFFF * 0.8) || (valleyValue <= 0xFFF * 0.2))
			return Large;
		else if((peakValue <= 0xFFF * 0.65) || (valleyValue >= 0xFFF * 0.35))
			return Small;
		else
			return OK;
}

void Control_Init()
{
	Dac1_Init();
	Dac1_Set_Vol(DAOut);//设置DA输出值为2.2V初始化放大倍数为0
	display_Gain(Control_DAConverdB());
}

void Control_IncInput()
{
	if(DAOut > 0)
	{
		DAOut -= 10;
		Dac1_Set_Vol(DAOut);
		display_Gain(Control_DAConverdB());

	}
}
void Control_DecInput()
{
	if(DAOut < 2000)
	{
		DAOut += 10;
		Dac1_Set_Vol(DAOut);
		display_Gain(Control_DAConverdB());
	}
}
