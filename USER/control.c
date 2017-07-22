#include "control.h"
u16 DAOut = 499;
s8 Control_DAConverdB()
{
	return -22.88*DAOut/(double)1000 + 21.424;
//		return 40*(0.97 - DAOut/(double)1000) + 10;
	
}

float Control_DAConverRate()
{
	 float x = (DAOut/(float)1000);
//	 float g = 4 * (0.97 - x) + 1;
		float g =  -2.288*x + 2.1424;
	 float temp = 30.267*pow(2.178,-4.386*x);

//	 float temp = pow(10,g);
	 return temp;
}
 
IsSuitable_Type Control_NeedToAdjust(u16 peakValue,u16 valleyValue)
{
		if((peakValue >= 0xFFF * 0.85) || (valleyValue <= 0xFFF * 0.15))
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
