#include "gui.h"
#include "Ada4_ST7735.h"
#include "matrix.h"
#include "kc_data.h"


//const uint8_t Gui::InfoPages[I_All] = {0,1};

//  Info use,ver
//....................................................................................
void Gui::DrawInfo()
{
	//  menu
	if (mlevel == 1)
	{
		d->setClr(22,20,26);
		d->print(strMain[ym]);  d->setFont(0);

		DrawMenu(I_All,strInfo, C_Info,RGB(22,20,28),RGB(4,4,8), 10, -1);
		return;
	}
	char a[64];
	int16_t y = 32;


	//  title
	d->setClr(17,17,22);
	d->print(strInfo[yy]);
	d->setFont(0);
	d->setClr(21,21,26);


	//int ii = InfoPages[yy];
	switch (yy)
	{
	//-----------------------------------------------------
	case I_Use:  // use
	{
		y -= 4;
		d->setClr(15,23,30);
		d->setCursor(0, y);
		d->print("\x10 ");  // >

		d->setClr(16,20,24);
		sprintf(a,"Save counter: %d", par.verCounter);
		d->print(a);  y += 14;

		int i,l,k, s = 0, t = 0, si = 0;


		d->setClr(25,25,29);
		sprintf(a,"      Total:  %d B", kc.memSize);
		d->setCursor(0, y);  d->print(a);  y+=12;


	}	break;
	}
}
