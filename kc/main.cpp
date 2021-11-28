#include "matrix.h"
#include "periodic.h"
#include "kc_data.h"
#include "gui.h"

#include "Ada4_ST7735.h"
#include "WProgram.h"


Gui gui;
KC_Main kc;
extern void ParInit();


//  kbd timer
//------------------------------------------------
void main_periodic()
{
	Matrix_scan(0);

	gui.KeyPress();

	kc.UpdLay(1);
}


//  main
//-------------------------------------------------------------------------
int main()
{
	ParInit();  // par defaults

	//  dac for tft led
	analogWriteRes(12);
	analogWriteDAC0(1200);  // dark


	Ada4_ST7735 tft;
	tft.begin();

	gui.Init(&tft);
	tft.clear();
	tft.display();  // black


	//  load set from ee
	kc.Load();
	//gui.SetScreen(ST_Main0);
	gui.SetScreen(ST_Clock + Cl_StatsExt);
	par.brightness = 100;


	//  kbd
	Matrix_setup();

	//  48 MHz/50 000 = 960 Hz   d: 52 fps
	Periodic_init( par.scanFreq * 1000 );
	Periodic_function( &main_periodic );

	while(1)
	{
		gui.Draw();

		gui.DrawEnd();

		//  temp get  --------
		#ifdef TEMP1  // 18B20  Temp'C
		gui.GetTemp();
		#endif
	}
}
