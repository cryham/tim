#include "gui.h"
#include "matrix.h"
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
	// kRight= kr(1,dt) - kr(2,dt);
	kUp   = kr(5,dt) - kr(4,dt);
	// kPgUp = kr(5,dt) - kr(6,dt);
	// kEnd  = kr(7,dt) - kr(8,dt);

	kEnt = Key(3);
	kBack = Key(2);


	//  rot enc  (*)  scroll
	auto& kk = mlevel == 0 ? kUp : kRight;

	static int8_t old = KeyH(1);
	int8_t scr = KeyH(1);
	if (scr && !old)
		kk = KeyH(0) > 0 ? -1 : 1;
	else
		kk = 0; //Key(0);
	old = scr;/**/

	int d = kUp + kRight;

	int sp = 2;  // mul


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


	//  main menu
	if (mlevel == 0)
	{
		if (d)
		{	ym += d;
			if (ym >= M_All)  ym = 0;
			if (ym < 0)  ym = M_All-1;
		}
		if (kEnt > 0)
			mlevel = 1;  // enter>
		return;
	}


	//  <back  global
	if (kBack && mlevel > 0)
		--mlevel;


	//  Help  ---
	if (ym == M_Help && mlevel == 1)
	{
		if (d)
			hpage = RangeAdd(hpage, d, 0,HAll-1, 1);
		return;
	}


	//  sub menu
	if (mlevel == 1)
	{
		auto No2nd = [&](){  return  // no 2nd level
			ym == M_Display;  };

		if (kEnt > 0 && !No2nd())  // enter>
			mlevel = 2;

		if (d)
		{	ym1[ym] += d;  Chk_y1();  }
		return;
	}
}
