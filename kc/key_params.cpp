#include "gui.h"
#include "matrix.h"
#include "kc_params.h"
#include "kc_data.h"
#include "periodic.h"

const uint8_t Gui::DispPages[Di_All] = {1,3,1,3,0};


//  Display, Options
//....................................................................................
void Gui::KeysParDisplay(int sp)
{
	if (kUp)  // y
	{	ym2Disp = RangeAdd(ym2Disp, kUp, 0, DispPages[pgDisp], 1);  }
	else
	if (kEnt)  // pg
	{	pgDisp = RangeAdd(pgDisp, kEnt, 0, Di_All-1, 1);
		ym2Disp = RangeAdd(ym2Disp, 0, 0, DispPages[pgDisp], 1);
	}
	else
	if (kRight)  // adjust values
	switch (pgDisp)
	{
	case Di_Bright:
		switch (ym2Disp)
		{
		case 0:
			par.brightness = RangeAdd(par.brightness, kRight * sp, 0, 100);
			kc.setDac = 1;  break;
		case 1:
			par.startScreen = RangeAdd(par.startScreen, kRight, 0, ST_ALL-1);  break;
		}	break;

	case Di_Config:
		switch (ym2Disp)
		{
		case 0:
			par.verCounter = RangeAdd(par.verCounter, kRight * sp, 0, 255, 1);  break;
		case 1:
			Save();  break;
		case 2:
			Load(0);  break;
		case 3:
			Load(1);  break;
		}	break;

	case Di_Key:
		switch (ym2Disp)
		{
		case 0:
			par.krDelay = RangeAdd(par.krDelay, kRight, 0,255);  break;
		case 1:
			par.krRepeat = RangeAdd(par.krRepeat, kRight, 0,255);  break;
		}	break;

	case Di_Graph:
		switch (ym2Disp)
		{
		case 0:
			par.timeTemp = RangeAdd(par.timeTemp, kRight * sp/2, 0, gIntvMask, 1);  break;
		case 1:
			par.timeTgraph = RangeAdd(par.timeTgraph, kRight * sp/2, 0, gIntvMask, 1);  break;
		case 2:
			par.minTemp = RangeAdd(par.minTemp, kRight * sp/2, 0, 40, 1);  break;
		case 3:
			par.maxTemp = RangeAdd(par.maxTemp, kRight * sp/2, 0, 40, 1);  break;
		}	break;

	case Di_Debug:
		switch (ym2Disp)
		{
		case 0:
			par.tempOfs = RangeAdd(par.tempOfs, kRight * sp, -128, 127, 1);  break;
		}	break;
	}
	if (kBack)  --mlevel;
}
