#include "gui.h"
#include "Ada4_ST7735.h"
#include "matrix.h"
#include "kc_data.h"


//  Setup
//....................................................................................
void Gui::DrawSetup()
{
	//  menu
	if (mlevel == 1)
	{
		d->setClr(21,23,23);
		d->print(strMain[ym]);  d->setFont(0);

		DrawMenu(S_All,strSetup, C_Setup,RGB(18,24,22),RGB(4,6,6), 10);
		return;
	}
	char a[64];
	int16_t y = 32;


	//  title
	d->setClr(17,22,22);
	d->print(strSetup[yy]);
	d->setFont(0);
	d->setClr(21,26,26);


	int ii = ScanPages[yy];
	switch (yy)
	{

	//-----------------------------------------------------
	case S_Scan:
	{
		for (int i=0; i <= ii; ++i)
		{
			d->setCursor(2,y);
			int c = 0;//abs(i - ym2Scan);
			if (!c)
			{	d->setClr(10,30,30);
				d->fillRect(0, y-1, W-1, 10, RGB(3,6,6));
				d->print("\x10 ");  // >
			}else
				d->print("  ");

			FadeClr(C_Setup2, 4, c, 1);
			switch(i)
			{
			case 0:
				// sprintf(a,"Scan: %u Hz", F_BUS/par.scanFreq/1000);  break;
			case 1:
				sprintf(a,"Strobe delay: %d us", par.strobe_delay);  break;
			case 2:
				sprintf(a,"Debounce: %d ms", par.debounce);  break;
			}
			d->print(a);  y += 8+4;
		}

		d->setClr(22,23,23);
		d->setCursor(W-1-6*6,0);
		d->print("Fps");
		d->println(a);

	}	break;

	}
}
