#include "kc_data.h"
#include "matrix.h"
#include "gui.h"
#include "WProgram.h"

KC_Params par;


//  update layers  (always)
//------------------------------------------------------------------------
void KC_Main::UpdLay(uint32_t ms)
{
	//  brightness dac led  ~~~
	if (setDac)
	{	setDac = 0;
		int bri = par.brightness;
		const int minBri = 10;
		int val = bri == 0 ? minBri : bri * (4095 - minBri) / 100 + minBri;
		analogWrite(LCD_LED, val);
	}
}
