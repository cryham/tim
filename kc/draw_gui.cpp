#include "gui.h"
#include "Ada4_ST7735.h"
#include "FreeSans9pt7b.h"


//  Draw  main
//....................................................................................
void Gui::Draw()
{
	yy = ym1[ym];

	//  Clear
	d->clear();

	d->setFont(&FreeSans9pt7b);
	d->setCursor(0,0);


	//  Main menu
	//------------------------------------------------------
	if (mlevel==0)
	{
		d->setClr(6,19,31);
		d->print("Main Menu");  d->setFont(0);

		DrawMenu(M_All,strMain, C_Main,RGB(20,25,29),RGB(5,7,9), 10, M_Next);
		return;
	}
	d->setClr(12,22,31);


	switch (ym)
	{

	//  Testing,Setup  kbd
	case M_Testing:   DrawTesting();  return;
	case M_Setup:     DrawSetup();  return;
	case M_Info:      DrawInfo();  return;

	//  Display, Help
	case M_Display: DrawDisplay();  return;
	case M_Clock:   DrawClock();  return;
	case M_Help:    DrawHelp();  return;
	}
}
