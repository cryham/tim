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
	d->print(strTest[yy]);
	d->setFont(0);
	d->setClr(21,26,31);

	{
		d->setCursor(0,32);

		//  scan codes  - - -
		d->print("Scan:");
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
}
