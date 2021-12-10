#include "gui.h"
#include "Ada4_ST7735.h"
#include "matrix.h"
#include "kc_data.h"


//  Testing
//....................................................................................
void Gui::DrawTesting()
{
	char a[64];

	//  title
	d->setClr(12,20,28);
	d->print("Keys"); //strMain[ym]);
	d->setFont(0);
	d->setClr(21,26,31);

	{
		d->setCursor(2,32);

		//  scan codes  - - -
		d->print("  Scan:");
		int c = 0;
		for (uint i = 0; i < ScanKeys; ++i)
		{
			const KeyState& k = Matrix_scanArray[i];
			if (k.state == KeyState_Hold)
			{
				sprintf(a," %d",i);  // scan code
				d->print(a);  ++c;
		}	}
		d->println("");  d->moveCursor(0,4);
	}

	//-----------------------------------------------------
	int16_t y = H/2;
	d->setClr(21,26,26);

	{
		for (int i=0; i <= 1; ++i)
		{
			d->setCursor(2,y);
			d->print("  ");

			FadeClr(C_Setup2, 4, i, 1);
			switch(i)
			{
			case 0:
				sprintf(a,"Strobe delay: %d us", par.strobe_delay);  break;
			case 1:
				sprintf(a,"Debounce: %d ms", par.debounce);  break;
			}
			d->print(a);  y += 8+4;
		}

		d->setClr(22,23,23);
		d->setCursor(W-1-6*6,0);
		// d->print("Fps");
		// d->println(a);

	}
}
