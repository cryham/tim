#include "gui.h"
#include "def.h"
// #include "kbd_layout.h"
#include "kc_data.h"


//  Main  ----
Gui::Gui() : d(0)
{
	Init(0);

#ifdef TEMP1
#ifdef GRAPHS
	// memset(grTemp, 0, sizeof(grTemp));
#endif
#endif
}

void Gui::Init(Ada4_ST7735* tft)
{
	d = tft;

	mlevel = 0;
	ym = 0;  yy = 0;
	for (int i=0; i < M_All; ++i)
		ym1[i]=0;


//	mlevel = 2;  //0
//	ym = M_Testing;
//	ym1[M_Testing] = T_Pressed;
//	SetScreen(ST_Main0);

	
	oldti=0;  oldti_kr=0;
	hpage = 0;

	ym2Disp=0; pgDisp=0;

	tInfo=0;  infType=0;
}

//  start screen  ---
void Gui::SetScreen(int8_t s)
{
	if (s == ST_Main0)
	{	mlevel = 0;  ym = 0;  return;  }
	else  mlevel = 1;

	switch (s)
	{
	case ST_Test:  ym = M_Testing;  break;

	case ST_Displ: ym = M_Display;  break;
	case ST_Help:  ym = M_Help;  break;
	}
	// level2
	if (s >= ST_Clock && s < ST_ClockMax){    ym = M_Clock;  pgClock = s - ST_Clock;  }
}

const char* Gui::StrScreen(int8_t s)
{
	switch (s)
	{
	case ST_Main0:  return "Main ""\x13";

	case ST_Test:   return strMain[M_Testing];

	case ST_Displ:  return strMain[M_Display];
	case ST_Help:   return strMain[M_Help];
	}
	// level2
	if (s >= ST_Clock && s < ST_ClockMax)	return strClock[s - ST_Clock];
	return "";
}

