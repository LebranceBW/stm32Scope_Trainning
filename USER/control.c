#include "control.h"
s8 Control_DAConverdB(u16 DAVol_Val)
{
	return 40*(2.222 - DAVol_Val/(double)1000)+10; 
}

double Control_DAConverRate(u16 DAVol_Val)
{
	 double g = 40*(2.222 - DAVol_Val/(double)1000)+
		 10;
	 return pow(10,g/10);
}
