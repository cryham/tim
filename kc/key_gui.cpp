#include "gui.h"
#include "matrix.h"
// #include "kbd_layout.h"
#include "kc_params.h"
#include "kc_data.h"
#include "periodic.h"
#include "core_pins.h"



//  Key press
//....................................................................................
void Gui::KeyPress()
{
	uint32_t ti = millis();
	uint16_t dt = ti - oldti_kr;
	oldti_kr = ti;

	//  update keys press  _k_
	kRight= kr(1,dt) - kr(2,dt);
	kUp   = kr(3,dt) - kr(4,dt);
	kPgUp = kr(5,dt) - kr(6,dt);
	kEnd  = kr(7,dt) - kr(8,dt);

	//kEnt = Key(gEnt);  kSave = Key(gSave);


	int sp = 2;  // mul


	//  Setup
	if (ym == M_Setup && mlevel == 2)
	{
		KeysParSetup(sp);
	}

	//  Info
	if (ym == M_Info && mlevel == 2)
	{
		KeysParInfo(sp);
	}

	//  Display
	if (ym == M_Display && mlevel == 1)
	{
		KeysParDisplay(sp);  return;
	}

	//  Clock
	if (ym == M_Clock && mlevel == 1)
	{
		KeysClock();  return;
	}


	if (mlevel == 0)  //  main menu
	{
		if (kUp){  ym += kUp;  if (ym >= M_All)  ym = 0;  if (ym < 0)  ym = M_All-1;  }
		 if (kRight > 0 || kEnt)  mlevel = 1;  // enter>
		return;
	}


	//  back global
	if (kBack && mlevel > 0)  --mlevel;


	//  Help
	if (ym == M_Help && mlevel == 1)
	{
		if (kUp || kPgUp)
			hpage = RangeAdd(hpage, kUp+kPgUp, 0,HAll-1, 1);
		if (kRight < 0 || kBack)
			mlevel = 0;  // <back
		return;
	}


	if (mlevel == 1)  //  sub menu
	{
		//  navigate
		if (kRight < 0)  mlevel = 0;  // <back
		if (kRight > 0 || kEnt)
			if (ym != M_Display)  mlevel = 2;  // enter>

		if (kUp){  ym1[ym] += kUp;  Chk_y1();  }
		return;
	}
}
