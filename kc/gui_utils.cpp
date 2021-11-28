#include "gui.h"
#include "matrix.h"
#include "kc_data.h"

#include "Ada4_ST7735.h"
#include "FreeSans9pt7b.h"
// #include "core_pins.h"
#include "WProgram.h"


//  Draw End
//....................................................................................
void Gui::DrawEnd()
{
	// DrawOperInfo();

	char a[64];

	//  fps  ---------
	if (0)
	{
		uint32_t ti = millis();
		float fr = 1000.f / (ti - oldti);
		int ff = fr;
		oldti = ti;

		d->setClr(24,28,31);
		d->setCursor(W-14,0);
		sprintf(a,"%d", ff);
		d->print(a);
	}

	//if (!offDisp)
		d->display();  // 58 Fps, 15ms @144MHz
}


//  draw utils
//....................................................................................
void Gui::DrawMenu(int cnt, const char** str, EFadeClr ec, uint16_t curClr,
	uint16_t bckClr, int16_t yadd, int16_t nextCol, int16_t numGap)
{
	const int16_t my = mlevel==0 ? ym : yy;
	const int16_t xw = 70, y1 = 32;  // par

	int16_t x=0, y=y1, c;
	for (int i=0; i < cnt; ++i)
	{
		d->setCursor(x,y);
		d->setColor(curClr);
		if (i == my)
			d->fillRect(x, y-1, W/2-2, 10, bckClr);
		d->print(i == my ? " \x10 ":"   ");  // >

		c = 0;//abs(i - my);  // dist dim
		FadeClr(ec, 4, c, 1);
		d->print(str[i]);

		//  next, extras
		y += yadd;

		if (i == numGap)  y += 4;

		if (i+1 == nextCol)
		{	x += xw;  y = y1;  }
	}
}

void Gui::DrawDispCur(int i, int16_t y)
{
	d->setCursor(2, y);
	int c = 0;//abs(i - ym2Disp);  // dist dim
	if (!c)
	{	d->fillRect(0, y-1, W-1, 10, RGB(8,8,4));
		d->setClr(31,22,6);
		d->print("\x10 ");  // >
	}else
		d->print("  ");

	FadeClr(C_Disp, 4, c, 1);
}

//  time
void Gui::PrintInterval(uint32_t t)
{
	char a[32];
	int ms = t/100%10;
	int s = t/1000;  t=s;  s%=60;
	int m = t/60;  t=m;  m%=60;
	int h = t/60;
	if (h)
		sprintf(a,"%dh%02dm", h, m);
	else if (m)
		sprintf(a,"%dm%02ds", m, s);
	else //if (s)
		sprintf(a,"%d.%ds", s, ms);
	d->print(a);
}

void Gui::FadeClr(EFadeClr ec, const uint8_t mi, const uint8_t mul, const uint8_t div)
{
	const uint8_t* clr = &Mclr[ec][0][0];
	const uint8_t* cmu = &Mclr[ec][1][0];

	d->setClr(
		max(mi, clr[0] - cmu[0] * mul / div),
		max(mi, clr[1] - cmu[1] * mul / div),
		max(mi, clr[2] - cmu[2] * mul / div) );
}


//  key utils
//....................................................................................
void Gui::Chk_y1()
{
	if (ym1[ym] >= YM1[ym])  ym1[ym] = 0;
	if (ym1[ym] < 0)  ym1[ym] = YM1[ym]-1;
}


//  key auto repeat,  row, col, ms
int8_t Gui::kr(uint8_t sc, uint16_t dt)
{
	KeyPosition st = Matrix_scanArray[sc].state;
	int16_t& m = Matrix_scanArray[sc].autoRepeat;

	if (st == KeyState_Press)
	{
		m = -1;  // start delay
		return 1;
	}
	else if (st == KeyState_Hold)
	{
		if (m < 0)
		{	m -= dt;
			if (m < -par.krDelay*5)  // delay ms
			{	m = 0;  return 1;  }
		}else
		{	m += dt;
			if (m > par.krRepeat*5)  // repeat freq
			{	m = 0;  return 1;  }
		}
	}
	return 0;
}

//  value add, range
int16_t Gui::RangeAdd(int16_t val, int16_t add, int16_t vmin, int16_t vmax, int8_t cycle)
{
	int16_t v = val;
	if (cycle)
	{	int16_t r = vmax - vmin + 1;
		v = (v + add + r) % r;
	}else
	{	v += add;
		v = min(vmax, max(vmin, v));
	}
	return v;
}

//  save
void Gui::Save()
{
	kc.Save();  infType = 2;  tInfo = -1;
}
//  load
void Gui::Load(int8_t reset)
{
	kc.Load();  infType = 1;  tInfo = -1;
}
