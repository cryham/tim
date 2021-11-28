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
	case ST_Map:   ym = M_Mapping;  break;
	case ST_Seqs:  ym = M_Sequences;  break;

	case ST_Test:  ym = M_Testing;  break;
	case ST_Setup: ym = M_Setup;  break;
	case ST_Info:  ym = M_Info;  break;

	case ST_Displ: ym = M_Display;  break;
	case ST_Help:  ym = M_Help;  break;
	}
	// level2
	if (s >= ST_Setup2 && s < ST_Setup2Max){  mlevel = 2;  ym = M_Setup;    ym1[ym] = s - ST_Setup2;  }  else
	if (s >= ST_Test2 && s < ST_Test2Max){    mlevel = 2;  ym = M_Testing;  ym1[ym] = s - ST_Test2;  }  else
	if (s >= ST_Info2 && s < ST_Info2Max){    mlevel = 2;  ym = M_Info;     ym1[ym] = s - ST_Info2;  }  else
	if (s >= ST_Clock && s < ST_ClockMax){    ym = M_Clock;  pgClock = s - ST_Clock;  }
}

const char* Gui::StrScreen(int8_t s)
{
	switch (s)
	{
	case ST_Main0:  return "Main ""\x13";
	case ST_Map:    return strMain[M_Mapping];
	case ST_Seqs:   return strMain[M_Sequences];

	case ST_Test:   return strMain[M_Testing];
	case ST_Setup:  return strMain[M_Setup];
	case ST_Info:   return strMain[M_Info];

	case ST_Displ:  return strMain[M_Display];
	case ST_Help:   return strMain[M_Help];
	}
	// level2
	if (s >= ST_Setup2 && s < ST_Setup2Max)	return strSetup[s - ST_Setup2];  else
	if (s >= ST_Test2 && s < ST_Test2Max)	return strTest[s - ST_Test2];  else
	if (s >= ST_Info2 && s < ST_Info2Max)	return strInfo[s - ST_Info2];  else
	if (s >= ST_Clock && s < ST_ClockMax)	return strClock[s - ST_Clock];
	return "";
}

