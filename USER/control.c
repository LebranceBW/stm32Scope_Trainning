#include "control.h"
u16 DAOut = 499;
s8 Control_DAConverdB()
{
//	return 40*(2.222 - DAVol_Val/(double)1000)+10;
		return -22.88*(DAOut/(double)1000)+21.42;
}

double Control_DAConverRate()
{
	 double g = (-22.88*(DAOut/(double)1000)+21.42)/10;
	 double temp = pow(10,g);
	 return temp;
}
 
IsSuitable_Type Control_NeedToAdjust(u16 peakValue,u16 valleyValue)
{
		if((peakValue >= 0xFFF * 0.85) || (valleyValue <= 0xFFF * 0.15))
			return Large;
		else if((peakValue <= 0xFFF * 0.6) || (valleyValue >= 0xFFF * 0.4))
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
	if(DAOut > 100)
	{
		DAOut -= 10;
		Dac1_Set_Vol(DAOut);
		display_Gain(Control_DAConverdB());

	}
}
void Control_DecInput()
{
	if(DAOut < 2500)
	{
		DAOut += 10;
		Dac1_Set_Vol(DAOut);
		display_Gain(Control_DAConverdB());
	}
}
