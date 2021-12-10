#include "gui.h"
#include "Ada4_ST7735.h"
#include "kc_params.h"


//  Help
//....................................................................................
void Gui::DrawHelp()
{
	char a[32];
	d->setClr(21,26,31);
	d->print(strMain[ym]);  d->setFont(0);

	//  page
	d->setClr(22,22,23);
	d->setCursor(W-1 -5*6, 0);
	sprintf(a, "%2d/%d", hpage+1, HAll);
	d->print(a);

	//  titles
	const static char* title[HAll] = {"Main", "Quick"};

	const int x = W/3+6;
	d->setClr(25,28,31);  d->setCursor(x, 2);  d->print(title[hpage]);
	//d->setClr(21,24,28);  d->setCursor(x,12);  d->print(title2[hpage]);

	//  text
	d->setCursor(0, 32);
	switch (hpage)
	{
	case 0:  //  main
		d->setClr(20,26,31);
		d->println("\x18,\x19 1,2   Move Cursor");  // ^,v \x10
		d->moveCursor(0,2);
		d->println("\x1B,\x1A ()    Dec,Inc Value");  // <,>

		d->moveCursor(0,6);
		d->println("3   Enter");
		d->moveCursor(0,2);
		d->println("4   Go Back");

		d->moveCursor(0,6);
		d->setClr(16,22,28);
		//d->println("F4   Save");
		break;

	case 1:  //  quick-
		d->setClr(16,22,28);
		d->println("F1  Clock /Graphs");
		d->println("F2  Display");
		d->println("F3  Test Keys");
		d->println("F4  Help");
		break;

	}
}
